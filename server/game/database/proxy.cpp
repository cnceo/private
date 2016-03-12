// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: alloc.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"

using namespace keye;
// --------------------------------------------------------
Proxy::Proxy():mysql_proxy(2){
	reg_stmt();
}

void Proxy::authorize(Session* session,const char* name,const char* pswd){
	if(name&&pswd){
		mysql_parameter param0(0,STMT_AUTH);
		char str[128];
		sprintf(str,stmts[STMT_AUTH].sql,name,pswd);
		mysql_statement st_find(str);
		//this may cause mem leak
		if(auto p=game.alloc().allocate(sizeof(ProxyHandler))){
			new(p)ProxyHandler(session);
			execute(st_find,&param0,(ProxyHandler*)p);
		}
	}
}
// --------------------------------------------------------
ProxyHandler::ProxyHandler(Session* s):session(s){}

void ProxyHandler::handle(mysql_resultset& resultset){
	if(auto h=stmts[resultset.id].handler){
		(this->*h)(resultset);
		game.alloc().deallocate(this);
	}
}

void ProxyHandler::handleAuth(mysql_resultset& resultset){
	if(resultset.length>0){
		//succeeded
		if(session){
			char str[32];
			unsigned char AUTH_OK=2,flag=0;
			unsigned short opcode=SMSG_AUTH_RESPONSE;
			const char* ip=game.config().value("server");
			size_t ip_len=strlen(ip)+1;
			auto port=(unsigned short)(int)game.config().value("port");
			std::string str_ip(ip);
			size_t sz=sizeof(unsigned char)*2+sizeof(size_t)*2+ip_len+sizeof(unsigned short);
			auto& packet=*(packet_t*)str;
			packet.length=sz;
			buffer_wrapper bw(packet.data,sz);
			bw<<AUTH_OK;
			bw<<flag;
			bw<<ip_len;
			bw<<str_ip;
			bw<<port;
			session->send(packet);
			LOG("Authorize succeeded!\n");
		}
	}else{
	}
}
