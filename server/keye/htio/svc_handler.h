// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: svc_handler.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-1
 */
// --------------------------------------------------------
#ifndef _svc_handler_h_
#define _svc_handler_h_

namespace keye{
// --------------------------------------------------------
/* service handler:object for handle socket operations
	svc_handler is created by service and pass to work_handler,
	svc_handler is only the interface,htio encapse the implements */
// --------------------------------------------------------
class KEYE_API svc_handler{
public:
	virtual					~svc_handler(){}
	virtual void			close()=0;
	virtual size_t			id()const=0;
	//clone
	virtual std::shared_ptr<svc_handler>
							operator()()const=0;
	//io method
	//send,post_event:buf must without length data
	virtual void			send(void* buf,size_t length)=0;
	virtual void			post_event(void* buf,size_t length)=0;
	virtual void			set_timer(size_t id,size_t milliseconds)=0;
	virtual void			unset_timer(size_t id)=0;
	//address and port
	virtual std::string		address()const=0;
	virtual unsigned short	port()const=0;
	//the interface expsure
	virtual std::shared_ptr<void>&
							sptr()=0;
};
// --------------------------------------------------------
#pragma warning(disable:4200)
//a common protocal: each packet has the packet_t head,it provide clean cut packet.
struct KEYE_API packet_t{
	unsigned short	length;
	unsigned char	data[0];
};

//packet_t could inclue head size or not
inline const size_t  KEYE_API get_packet_length(const packet_t& p){
	return p.length;//+sizeof(packet_t)
}

/*a packet_t unpacker
	_Hx-the real handler with on_read and send function
	_Ax-the allocator */
template<typename _Hx,typename _Ax=std::allocator<char>>
class packet_helper{
	typedef typename _Ax::value_type alloc_value_type;
public:
					packet_helper(_Hx& hx,_Ax& ax):_hx(hx),_ax(ax){
						memset(&_unfin_packet,0,sizeof(_unfin_packet));
					}
	virtual			~packet_helper(){
						if(packet_t* p=_unfin_packet.packet)
							_ax.deallocate((alloc_value_type*)p,1);
					};
	virtual void	on_read(void* buf,size_t trans){
						const size_t sz_head=sizeof(packet_t);
						char* data=(char*)buf;
						// process old packet first
						do if(_unfin_packet.fin){
							//need head size at least
							if(_unfin_packet.fin<sz_head){
								const size_t sz_head_need=sz_head-_unfin_packet.fin;
								if(trans>=sz_head_need){
									_append(data,sz_head_need);
									trans-=sz_head_need;
									data+=sz_head_need;
								}else
									break;
							}
							//copy data
							std::size_t total=get_packet_length(*_unfin_packet.packet);
							std::size_t rest=total-_unfin_packet.fin;
							bool complete=trans>=rest;
							_append(data,complete?rest:trans);
							if(complete){
								//complete
								_hx.handle(*_unfin_packet.packet);
								trans-=rest;
								data+=rest;
								//reset _unfin_packet
								_unfin_packet.fin=0;
							}else{
								//update packet and do nothing
								return;
							}
						}while(false);
						//process the rest
						while(trans>=sz_head){
							const packet_t* p=(packet_t*)data;
							std::size_t total=get_packet_length(*p);
							if(total==(std::size_t)0||total>(std::size_t)0x40000000){
								//wrong packet!
								//reset _unfin_packet
								_unfin_packet.fin=0;
								break;
							}else if(trans>=total){
								//has complete packet
								_hx.handle(*p);
								trans-=total;
								data+=total;
							}else{
								//only imcomplete,copy to read buffer
								_prepare(total);
								_append(data,trans);
								trans=0;
								break;
							}
						}
						//residue
						if(trans)_append(data,trans);
					}
protected:
	void*			_prepare(size_t len){
						//need reallocate
						if(!_unfin_packet.packet||_unfin_packet.cap-_unfin_packet.fin<len){
							auto old=_unfin_packet.packet;
							//allocate
							_unfin_packet.cap=_unfin_packet.fin+len;
							//we donot like fragment
							if(_unfin_packet.cap<=sizeof(packet_t))
								_unfin_packet.cap=_default_length;
							_unfin_packet.packet=(packet_t*)_ax.allocate(_unfin_packet.cap);
							if(old){
								//cp old
								memcpy(_unfin_packet.packet,old,_unfin_packet.fin);
								//deallocate
								_ax.deallocate((alloc_value_type*)old,1);
							}else
								_unfin_packet.fin=0;
						}
						return _unfin_packet.packet;
					}
	void			_append(const void* buf,size_t len){
						if(_prepare(len)){
							char* ptr=(char*)_unfin_packet.packet+_unfin_packet.fin;
							memcpy(ptr,buf,len);
							_unfin_packet.fin+=len;
						}
					}
	struct upacket_t{
		size_t		cap,fin;	//buffer capacity,packet fin
		packet_t*	packet;
	};
	_Hx&			_hx;
	_Ax&			_ax;
	upacket_t		_unfin_packet;
	static size_t	_default_length;
};
template<typename _Hx,typename _Ax> size_t packet_helper<_Hx,_Ax>::_default_length=2020;
// --------------------------------------------------------
};
#endif // _svc_handler_h_