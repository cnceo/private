// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: service.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-31
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "wsio_fwd.h"
#include "impl_decl.hpp"

#if 0
#ifdef _WEBSOCKETPP_
typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using websocketpp::lib::thread;
using websocketpp::lib::mutex;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;
#endif

/* on_open insert connection_hdl into channel
 * on_close remove connection_hdl from channel
 * on_message queue send to all channels
 */

class websocket_service_impl {
public:
    websocket_service_impl() {
        // Set logging settings
        m_server.clear_access_channels(websocketpp::log::alevel::all);
        m_server.set_access_channels(websocketpp::log::alevel::access_core);
        // Initialize Asio Transport
        m_server.init_asio();
        
        // Register handler callbacks
        m_server.set_open_handler(bind(&websocket_service_impl::on_open,this,::_1));
        m_server.set_close_handler(bind(&websocket_service_impl::on_close,this,::_1));
        m_server.set_message_handler(bind(&websocket_service_impl::on_message,this,::_1,::_2));
        m_server.set_http_handler(bind(&websocket_service_impl::on_http,this,::_1));
        m_server.set_fail_handler(bind(&websocket_service_impl::on_fail,this,::_1));
    }
    
    void run(uint16_t port) {
        // listen on specified port
        m_server.listen(port);
        
        // Start the server accept loop
        m_server.start_accept();
        
        m_server.set_timer(FRAME_INTERVAL*1000,std::bind(&websocket_service_impl::on_timer,this,FRAME_TIMER_ID,FRAME_INTERVAL*1000));
        m_server.set_timer(MINUTE_INTERVAL*1000,std::bind(&websocket_service_impl::on_timer,this,MINUTE_TIMER_ID,MINUTE_INTERVAL*1000));
        // Start the ASIO io_service run loop
        try {
            spthread.reset(new thread(bind(&server::run,&m_server)));
        } catch (const std::exception & e) {
            std::cout << e.what() << std::endl;
        }
    }
    void on_timer(int id,int interval){
        Game::instance()->on_timer(id);
        m_server.set_timer(interval,std::bind(&websocket_service_impl::on_timer,this,id,interval));
    }
    
    void on_open(connection_hdl hdl) {
        //        auto& _ax=Game::instance()->alloc();
        new Player(hdl);
    }
    
    void on_close(connection_hdl hdl) {
        auto cid=(size_t)hdl.lock().get();
        client_close(cid);//no dtor,no remove from connects
        Game::instance()->connects().remove(cid);
    }
    
    void on_message(connection_hdl hdl, server::message_ptr msg) {
        //        std::cout << "on_message" << std::endl;
        auto m=msg.get();
        auto& pl=m->get_payload();
        //        std::cout<<"payload="<<pl<<",len="<<pl.length()<<std::endl;
        
        //m_server.send(hdl,pl,msg->get_opcode());
        //m_server.send(hdl,(const void*)ptr,(size_t)len,msg->get_opcode());
        /*
         //from server
         struct packet_server_t{
         short	length;		//within this short
         char	data[0];	//signal+data
         };
         
         //from client
         struct packet_client_t{
         short	length;		//within this short
         int		crc32;		//crc for server
         char	data[0];	//signal+data
         };
         */
        auto data=(char*)pl.data();
        if(data){
            auto pk=(packet_client_t*)data;
            auto pkdata=(char*)pk->data;
            auto sig=*(short*)pkdata;
            LOG_INFO<<"recv "<<sig<<Endl;
            
            auto cid=(size_t)hdl.lock().get();
            if(-1==client_onData(cid,data,pk->length,Game::instance()->getMysqlConn())){
                if(auto player=Game::instance()->connects().find(cid))
                    player->close();
            }
        }
    }
    
    void on_http(connection_hdl hdl) {
        server::connection_ptr con = m_server.get_con_from_hdl(hdl);
        
        std::string res = con->get_request_body();
        
        std::stringstream ss;
        ss << "got HTTP request with " << res.size() << " bytes of body data.";
        
        con->set_body(ss.str());
        con->set_status(websocketpp::http::status_code::ok);
    }
    
    void on_fail(connection_hdl hdl) {
        server::connection_ptr con = m_server.get_con_from_hdl(hdl);
        
        std::cout << "Fail handler: " << con->get_ec() << " " << con->get_ec().message()  << std::endl;
    }
    
    void send(size_t,const void* buf,size_t len){
        //size_t cid=0;
        //m_server.send(cid,buf,len);
    }
private:
    typedef std::set<connection_hdl,std::owner_less<connection_hdl> > con_list;
    
    server m_server;
    con_list m_connections;
    std::shared_ptr<thread> spthread;
};

// --------------------------------------------------------
// Service_impl
// --------------------------------------------------------
NS_KEYE_WS_BEGIN
class Service_impl{
public:
			Service_impl(Work_handler& w,wsio_alloc& a,size_t ios,size_t works,size_t rb_size);
	void	run(unsigned short port,const char* address=nullptr);
	void	connect(const char* address,unsigned short port,unsigned short conns=1);
	void	close();
	bool	closed()const;

	void	on_open(struct libwebsocket *wsi);
	void	on_close(struct libwebsocket *wsi);
	void	on_read(struct libwebsocket *wsi,void *in, size_t len);
private:
	// the service loop
	void	_svc();

	Work_handler&	_w;
	wsio_alloc&		_a;
	size_t			_ios,_works,_rb_size;
	bool			_started;
    
#ifdef _WEBSOCKETPP_
    void on_open(connection_hdl hdl) {
        //        auto& _ax=Game::instance()->alloc();
        new Player(hdl);
    }
    
    void on_close(connection_hdl hdl) {
        auto cid=(size_t)hdl.lock().get();
        client_close(cid);//no dtor,no remove from connects
        Game::instance()->connects().remove(cid);
    }
    
    void on_message(connection_hdl hdl, server::message_ptr msg) {
        //        std::cout << "on_message" << std::endl;
        auto m=msg.get();
        auto& pl=m->get_payload();
        //        std::cout<<"payload="<<pl<<",len="<<pl.length()<<std::endl;
        
        //m_server.send(hdl,pl,msg->get_opcode());
        //m_server.send(hdl,(const void*)ptr,(size_t)len,msg->get_opcode());
        /*
         //from server
         struct packet_server_t{
         short	length;		//within this short
         char	data[0];	//signal+data
         };
         
         //from client
         struct packet_client_t{
         short	length;		//within this short
         int		crc32;		//crc for server
         char	data[0];	//signal+data
         };
         */
        auto data=(char*)pl.data();
        if(data){
            auto pk=(packet_client_t*)data;
            auto pkdata=(char*)pk->data;
            auto sig=*(short*)pkdata;
            LOG_INFO<<"recv "<<sig<<Endl;
            
            auto cid=(size_t)hdl.lock().get();
            if(-1==client_onData(cid,data,pk->length,Game::instance()->getMysqlConn())){
                if(auto player=Game::instance()->connects().find(cid))
                    player->close();
            }
        }
    }
    
    void on_http(connection_hdl hdl) {
        server::connection_ptr con = m_server.get_con_from_hdl(hdl);
        
        std::string res = con->get_request_body();
        
        std::stringstream ss;
        ss << "got HTTP request with " << res.size() << " bytes of body data.";
        
        con->set_body(ss.str());
        con->set_status(websocketpp::http::status_code::ok);
    }
    
    void on_fail(connection_hdl hdl) {
        server::connection_ptr con = m_server.get_con_from_hdl(hdl);
        
        std::cout << "Fail handler: " << con->get_ec() << " " << con->get_ec().message()  << std::endl;
    }
#else
    // the context
	struct libwebsocket_context*			_context;
	struct libwebsocket_protocols			_protocols[2];
#endif
	// threads pool
	typedef std::shared_ptr<std::thread>	thread_ptr;
	std::vector<thread_ptr>	_threads;
	// svc_handler pool
	std::map<int,Svc_handler_impl*>			_shs;
};
NS_KEYE_WS_END
// --------------------------------------------------------
USING_NS_KEYE_WS

static int callback_http(struct libwebsocket_context *context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
		void *in, size_t len);

Service_impl::Service_impl(Work_handler& w,wsio_alloc& a,size_t ios,size_t works,size_t rb_size)
		:_w(w),_a(a),_ios(ios),_works(works),_rb_size(rb_size),_started(false),_context(nullptr){
#ifdef _WEBSOCKETPP_
    // Set logging settings
    m_server.clear_access_channels(websocketpp::log::alevel::all);
    m_server.set_access_channels(websocketpp::log::alevel::access_core);
    // Initialize Asio Transport
    m_server.init_asio();
    
    // Register handler callbacks
    m_server.set_open_handler(bind(&websocket_service_impl::on_open,this,::_1));
    m_server.set_close_handler(bind(&websocket_service_impl::on_close,this,::_1));
    m_server.set_message_handler(bind(&websocket_service_impl::on_message,this,::_1,::_2));
    m_server.set_http_handler(bind(&websocket_service_impl::on_http,this,::_1));
    m_server.set_fail_handler(bind(&websocket_service_impl::on_fail,this,::_1));
#else
    memset(_protocols,0,sizeof(_protocols));
    _protocols[0].name=protocol_name;
    _protocols[0].callback=callback_http;
#endif
}

void Service_impl::run(unsigned short port,const char* address){
    if(_started)return;

	//io threads
	if(port){
		//we do not open accept while port was 0
		if(address&&0<strlen(address))
			//auto address
		{}

#ifdef _WEBSOCKETPP_
        // listen on specified port
        m_server.listen(port);
        
        // Start the server accept loop
        m_server.start_accept();
        
        m_server.set_timer(FRAME_INTERVAL*1000,std::bind(&websocket_service_impl::on_timer,this,FRAME_TIMER_ID,FRAME_INTERVAL*1000));
        m_server.set_timer(MINUTE_INTERVAL*1000,std::bind(&websocket_service_impl::on_timer,this,MINUTE_TIMER_ID,MINUTE_INTERVAL*1000));
        // Start the ASIO io_service run loop
        try {
            spthread.reset(new thread(bind(&server::run,&m_server)));
        } catch (const std::exception & e) {
            std::cout << e.what() << std::endl;
        }
#else
		_context = libwebsocket_create_context(port,nullptr,
			_protocols,libwebsocket_internal_extensions,
			nullptr, nullptr, nullptr, -1, -1, 0, this);
		if (_context == nullptr) {
			LOG("libwebsocket init failed\n");
		}else{
			// must set started first
			_started=true;
			// Create a thread to run the io_service.
#ifdef LWS_NO_FORK
			_threads.push_back(thread_ptr(new std::thread(std::bind(&Service_impl::_svc,this))));
#else
			if(0>libwebsockets_fork_service_loop(_context)){
				fprintf(stderr, "Unable to fork service loop %d\n", n);
				return;
			}
#endif
			LOG("Websocket %s started on %d, with %d io and %d work threads.\n",protocol_name,port,_ios,_works);
		}
#endif
	}
}

void Service_impl::connect(const char* address,unsigned short port,unsigned short conns){
	if(!address||!port||_started)return;

	_context = libwebsocket_create_context(CONTEXT_PORT_NO_LISTEN,nullptr, 
		_protocols,libwebsocket_internal_extensions,
		nullptr, nullptr, nullptr, -1, -1, 0, this);
	if (_context == nullptr) {
		LOG("libwebsocket init failed\n");
	}else{
		auto wsi = libwebsocket_client_connect(_context, address, port,0,
			"/",nullptr,nullptr,_protocols[0].name,-1);
		if (wsi == NULL) {
			LOG("libwebsocket %s connect failed\n",protocol_name);
		}else{
			// Create a thread to run the io_service.
#ifdef LWS_NO_FORK
			_threads.push_back(thread_ptr(new std::thread(std::bind(&Service_impl::_svc,this))));
#else
			if(0>libwebsockets_fork_service_loop(_context)){
				fprintf(stderr, "Unable to fork service loop %d\n", n);
				return;
			}
#endif
			_started=true;
			LOG("Websocket %s connect to %s:%d.\n",protocol_name,address,port);
		}
	}
}

void Service_impl::on_open(struct libwebsocket *wsi){
	auto fd=libwebsocket_get_socket_fd(wsi);
//	LOG("-------> on_open fd=%d\n",fd);
	auto sh=(Svc_handler_impl*)_a.allocate(sizeof(Svc_handler_impl));
	new(sh) Svc_handler_impl(*_context,*wsi,_w,_a);
	_shs.insert(std::make_pair(fd,sh));
	_w.on_open(sh_type(*sh));
}

void Service_impl::on_close(struct libwebsocket *wsi){
	auto fd=libwebsocket_get_socket_fd(wsi);
//	LOG("-------> on_close fd=%d\n",fd);
	auto i=_shs.find(fd);
	if(i!=_shs.end()){
		auto sh=i->second;
		_w.on_close(sh_type(*sh));
		_shs.erase(i);
		_a.deallocate(sh,sizeof(Svc_handler_impl));;
	}
}

void Service_impl::on_read(struct libwebsocket *wsi,void *in, size_t len){
	auto fd=libwebsocket_get_socket_fd(wsi);
//	LOG("-------> on_read fd=%d\n",fd);
	auto i=_shs.find(fd);
	if(i!=_shs.end())
		_w.on_read(sh_type(*i->second),in,len);
}

void Service_impl::close(){
	if(_started){
		_started=false;
		//waiting for threads
		for(auto i=_threads.begin(),ii=_threads.end();i!=ii;++i){
			auto t=*i;
			t->join();
		}
		_threads.clear();
		//destroy context
		if(_context){
			libwebsocket_context_destroy(_context);
			_context=nullptr;
		}
	}
}
bool Service_impl::closed()const{
	return !_started;
}

void Service_impl::_svc(){
	if(_context)while(_started&&libwebsocket_service(_context, 50)>=0);
}
// --------------------------------------------------------
int callback_http(struct libwebsocket_context *context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
		void *in, size_t len){
	auto ptr=libwebsocket_context_user(context);
	if(!ptr)return -1;
	Service_impl& s=*static_cast<Service_impl*>(ptr);
	switch (reason){
	case LWS_CALLBACK_ESTABLISHED:
		s.on_open(wsi);
		break;
	case LWS_CALLBACK_CLOSED:
		s.on_close(wsi);
		break;
	case LWS_CALLBACK_RECEIVE:
		s.on_read(wsi,in,len);
		break;
	default:
		break;
	}

	return 0;
}
// --------------------------------------------------------
// service
// --------------------------------------------------------
Service::Service(Work_handler& w,wsio_alloc& a,size_t ios,size_t works,size_t rb_size){
	_svc.reset(new Service_impl(w,a,ios,works,rb_size));}
void Service::connect(const char* address,unsigned short port,unsigned short conns){if(_svc)_svc->connect(address,port,conns);}
void Service::run(unsigned short port,const char* address)	{if(_svc)_svc->run(port,address);}
void Service::close()										{if(_svc)_svc->close();}
bool Service::closed()const									{return _svc?_svc->closed():true;}
#endif
