// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: session.cpp
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
SessionHandler::SessionHandler(Alloc& ax):_MyBase(ax),_auto_client(true){}

void SessionHandler::on_open(svc_handler& sh){
	_MyBase::on_open(sh);
	if(_auto_client){
/*
		Service* svc=(Service*)_MyBase::_s;
		char cidx[32];
		sprintf(cidx,"test%d",svc->index++);
		auto id=sh.id();
		auto r=(Session*)sh.sptr().get();
		r->_name=cidx;
		svc->add(id,r);
		r->login();
*/
	}
}

void SessionHandler::on_close(svc_handler& sh){
	_MyBase::on_close(sh);
	LOG("Closed\n");
}

bool SessionHandler::on_timer(svc_handler& sh,size_t id,size_t milliseconds){
	bool ret=_MyBase::on_timer(sh,id,milliseconds);
	if(WRITE_TIMER==id){
/*
		if(_auto_client){
			if(auto r=(Session*)sh.sptr().get())
				r->action();
		}else if(_MyBase::_s->send){
			auto& p=*(packet_t*)_buf;
			auto& cp=*(packet_crc_t*)_buf;
			_buf[_MyBase::_s->pack-1]='\0';
			cp.length=_MyBase::_s->pack-sizeof(packet_t);
			cp.crc=CMSG_ROBOT;//crc(cp.data,_s->pack-sizeof(packet_crc_t),16);

			sh.send(p.data,p.length);
		}
*/
	}
	return ret;
}
// --------------------------------------------------------
