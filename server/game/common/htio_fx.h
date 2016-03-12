// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: htio_fx.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-1
 */
// --------------------------------------------------------
#ifndef _htio_demo_h_
#define _htio_demo_h_

#include <assert.h>
// --------------------------------------------------------
// forward declaration
// --------------------------------------------------------
namespace keye{
int KEYE_API myclient(const char* host,unsigned short port,size_t ios=1,size_t works=1);
int KEYE_API myserver(unsigned short port,size_t ios=1,size_t works=1);
};
// --------------------------------------------------------
// implementation
// --------------------------------------------------------
#define FLOW_TIMER 999
#define WRITE_TIMER 998
#define WRITE_MIN 64
#define WRITE_MAX 4096
#define WRITE_FREQ 250

using namespace keye;
#pragma warning(disable:4200)

typedef std::allocator<char>			std_ax_t;
typedef keye::keye_allocator<std_ax_t>	keye_ax_t;
// --------------------------------------------------------
class myalloc:public htio_alloc{
public:
					myalloc():_kax(64<<20,_sax){}
	virtual void*	allocate(size_t _Count){return _sax.allocate(_Count);}
	virtual void	deallocate(void* _Ptr, size_t){_sax.deallocate((char*)_Ptr,0);}
private:
	std_ax_t		_sax;
	keye_ax_t		_kax;
};
// --------------------------------------------------------
class ServiceBase{
public:
			ServiceBase(work_handler& w,htio_alloc& a,size_t ios=1,size_t works=1,size_t rb_size=1460)
				:svc(w,a,ios,works,rb_size)
				,client(false)
				,show_status(true)
				,response(false)
				,send(false)
				,echo(false)
				,crc(true)
				,interval(WRITE_FREQ)
				,pack(WRITE_MIN)
				,conns(0){}
	service svc;
	bool	client,show_status,response,send,echo,crc;
	size_t	conns,interval,pack;
};
// --------------------------------------------------------
// Raw
// --------------------------------------------------------
class s_handler:public work_handler{
public:
					s_handler():_s(nullptr){}
	virtual void	on_open(svc_handler&){
		_metric.on_open();}
	virtual void	on_close(svc_handler&){
		_metric.on_close();}
	virtual void	on_read(svc_handler& sh,void* buf,size_t sz){
		_metric.on_read(sz);

		if(_s){
			if(_s->crc){
//				auto sc=crc(cp.data,p.length-sizeof(packet_crc_t),16);
			}
			if(_s->echo)
				LOG("read %d:%s\n",sz,buf);
			if(_s->response)
				sh.send(buf,sz);
		}
	}
	virtual void	on_write(svc_handler&,void*,size_t sz){
		_metric.on_write(sz);}
	virtual bool	on_timer(svc_handler&,size_t id,size_t milliseconds){
		if(FLOW_TIMER==id){
			_metric.on_timer(milliseconds);
			if(_s&&_s->show_status)
				LOG("connects:%d, rb:%dk/s, wb:%dk/s, rc:%d/s, wc:%d/s\n",_metric.connects,
					_metric.metric.read_bytes>>10,_metric.metric.write_bytes>>10,_metric.metric.read_count,_metric.metric.write_count);
		}
		return true;
	}

	void		set_svc(ServiceBase& s){_s=&s;}
private:
	ServiceBase*	_s;
	flow_metric	_metric;
};
// --------------------------------------------------------
class c_handler:public work_handler{
public:
	c_handler():_s(nullptr){
		memset(_buf,'*',WRITE_MAX);
		_buf[WRITE_MAX-1]='\0';
	}
	virtual void	on_open(svc_handler& sh){
		sh.set_timer(WRITE_TIMER,WRITE_FREQ);
	}
	virtual void	on_read(svc_handler& sh,void* buf,size_t sz){
		if(_s&&_s->echo)
			LOG("read %d:%s\n",sz,buf);
	}
	virtual bool	on_timer(svc_handler& sh,size_t id,size_t milliseconds){
		bool ret=true;
		if(WRITE_TIMER==id&&_s){
			if(_s->interval!=milliseconds){
				sh.set_timer(WRITE_TIMER,_s->interval);
				ret=false;
			}
			if(_s->send){
				_buf[_s->pack-1]='\0';
				sh.send(_buf,_s->pack);
			}
		}
		return ret;
	}

	void		set_svc(ServiceBase& s){_s=&s;}
private:
	ServiceBase*	_s;
	char _buf[WRITE_MAX];
};
// --------------------------------------------------------
// SessionBase and packet
// --------------------------------------------------------
template<typename _Ax=std_ax_t>
class SessionBase{
	typedef packet_reader	helper_t;
public:
					SessionBase(keye::svc_handler& sh,_Ax& ax):_helper(*this,ax){
						_sh=sh();
					}
	virtual			~SessionBase(){}
	virtual void	handle(const packet_t& p)=0;
	virtual void	send(const packet_t& p){
		if(_sh)_sh->send((void*)&p,p.length+sizeof(packet_t));
	}
protected:
	void	handle_raw(void* buf,size_t len){
		_helper.on_read(buf,len);
	}

	template<typename,typename> friend class SessionHandlerBase;
	//packet helper
	helper_t	_helper;
	//svc_handler
	std::shared_ptr<keye::svc_handler>	_sh;
};

template<typename _Sx,typename _Ax=std_ax_t>
class SessionHandlerBase:public work_handler{
public:
					SessionHandlerBase(_Ax& ax):_ax(ax){}
	virtual			~SessionHandlerBase(){}
	virtual void	on_open(svc_handler& sh){
		auto id=sh.id();
		//ctor _Sx
		auto sx=new _Sx(sh,_ax);
		sh.sptr().reset((void*)sx);
	}
	virtual void	on_read(svc_handler& sh,void* buf,size_t len){
		auto sx=(_Sx*)sh.sptr().get();
		sx->handle_raw(buf,len);
	}
	virtual void	on_close(svc_handler& sh){
		if(auto sx=(_Sx*)sh.sptr().get()){
			//dtor _Sx
			sx->~_Sx();
		}
	}
/*
	virtual bool	on_timer(svc_handler& sh,size_t id,size_t milliseconds){
		bool ret=true;
		if(WRITE_TIMER==id&&_s){
			if(_s->interval!=milliseconds){
				//reset timer interval
				sh.set_timer(WRITE_TIMER,_s->interval);
				ret=false;
			}
		}
		return ret;
	}
*/
//	void		set_svc(ServiceBase& s){_s=&s;}
protected:
//	ServiceBase*	_s;
	_Ax&		_ax;
};
// --------------------------------------------------------
// helpers
// --------------------------------------------------------
void wait_for(ServiceBase& s);
static std::string _host;
static unsigned _port=0;
namespace keye{
inline int myclient(const char* host,unsigned short port,size_t ios,size_t works){
	c_handler w;
	myalloc a;
	size_t rb_size=1460;
	ServiceBase s(w,a,ios,works,rb_size);
	w.set_svc(s);
	s.client=true;
	_host=host;
	_port=port;
	wait_for(s);
	return 0;
}

inline int myserver(unsigned short port,size_t ios,size_t works){
	s_handler w;
	myalloc a;
	size_t rb_size=1460;
	ServiceBase s(w,a,ios,works,rb_size);
	w.set_svc(s);
	_port=port;
	s.svc.run(port);
	s.svc.set_timer(FLOW_TIMER,5000);
	wait_for(s);
	return 0;
}};

inline void prompt(){
	LOG("\ncommand list:\n \
	?:\t\tshow this\n \
	e:\t\techo messages\n \
	h[ip:port]:\tset host ip and port\n \
	i[ms]:\t\tsend interval\n \
	l[n]:\t\tsend packet length\n \
	n[n]:\t\tincreament connects\n \
	p:\t\tprint status\n \
	r:\t\tresponse messages\n \
	s:\t\tsend messages\n \
	t:\t\tshow status\n \
	x:\t\tclose\n \
");
}

inline void wait_for(ServiceBase& s){
	prompt();
	bool exit=false;
	while(!exit||!s.svc.closed())
	switch(std::getchar()){
	case 'e':
		s.echo=!s.echo;
		break;
	case 'h':
		if(s.client){
			char host[32];
			scanf("%s",&host);
			std::string str(host),s;
			size_t n=str.find(':');
			_host=str.substr(0,n);
			if(_host.length()<=2)_host="127.0.0.1";
			s=str.substr(n+1);
			_port=atoi(s.c_str());
			printf("set host %s:%d\n",_host.c_str(),_port);
		}
		break;
	case '?':
		prompt();
		break;
	case 'i':
		if(s.client){
			int interval=WRITE_FREQ;
			scanf("%d",&interval);
			s.interval=interval;
		}
		break;
	case 'l':
		if(s.client){
			int pack=WRITE_MIN;
			scanf("%d",&pack);
			s.pack=pack;
		}
		break;
	case 'n':
		if(s.client){
			int conns=1;
			scanf("%d",&conns);
			s.svc.connect(_host.c_str(),_port,conns);
		}
		break;
	case 'p':
		LOG("\ncommand list:\n \
echo:\t\t%s\n \
response:\t%s\n \
send:\t\t%s\n \
status:\t%s\n \
interval:\t%d\n \
length:\t%d\n \
host:\t\t%s:%d\n \
conns:\t\t%d\n \
",s.echo?"on":"off",s.response?"on":"off",s.send?"on":"off",s.show_status?"on":"off"
,s.interval,s.pack,_host.c_str(),_port,s.conns);
		break;
	case 'r':
		s.response=!s.response;
		break;
	case 's':
		s.send=!s.send;
		break;
	case 't':
		s.show_status=!s.show_status;
		break;
	case 'w':
		s.crc=!s.crc;
		break;
	case 'x':
		{
		s.svc.close();
		exit=true;
		break;
		}
	}
}
// --------------------------------------------------------
#endif