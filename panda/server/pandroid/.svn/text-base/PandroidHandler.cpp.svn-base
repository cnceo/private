#include "stdafx.h"
#include "PandroidFwd.h"

using namespace proto3;

void PandroidHandler::on_open(keye::svc_handler& sh){
	PDLOG<<"connected to "<<sh.address()<<":"<<sh.port()<<keye::endf;
	MsgCGLogin msg;
	msg.set_mid(eMsg::MSG_CG_LOGIN);
	msg.set_name("test0001");
	PBHelper::Send(sh,msg);
}

void PandroidHandler::on_close(keye::svc_handler& sh){
}

void PandroidHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CG_BEGIN||mid>=eMsg::MSG_CG_END)return;
	switch(mid){
	case MSG_GC_LOGIN:
	{
		PDLOG<<"logged in gateway \n";
		MsgGCLogin msg;
		if(pb.Parse(msg)){
			PDLOG<<"--------gateway login successful!\n";
		}
	}
	break;
	default:
		break;
	}
}
