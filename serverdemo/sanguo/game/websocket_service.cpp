//
//  websocket_service.cpp
//  sanguo
//
//  Created by Vic Liu on 8/20/15.
//  Copyright (c) 2015 Vic Liu. All rights reserved.
//

#include "stdafx.h"
#include "game/fwd.h"
#include "websocket_service.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <set>

/*#include <boost/thread.hpp>
 #include <boost/thread/mutex.hpp>
 #include <boost/thread/condition_variable.hpp>*/
#include <websocketpp/common/thread.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using websocketpp::lib::thread;
using websocketpp::lib::mutex;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;

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

void websocket_service::run(unsigned short port,std::function<void(size_t,const void*,size_t)>){
    try {
        _impl.reset(new websocket_service_impl);
        
        // Run the asio loop with the main thread
        _impl->run(port);
        
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}

void websocket_service::send(size_t cid,const void* buf,size_t len){
    _impl->send(cid,buf,len);
}
