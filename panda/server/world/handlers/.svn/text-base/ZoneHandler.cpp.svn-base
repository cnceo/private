#include "stdafx.h"
#include "WorldServerFwd.h"

using namespace proto3;

void ZoneHandler::on_close(keye::svc_handler& sh){
	//PDLOG<<"zone logged out("<<sh.address()<<")\n";
}

void ZoneHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_ZW_BEGIN||mid>=eMsg::MSG_ZW_END)return;
	switch(mid){
	case eMsg::MSG_ZW_CONNECT:
	{
		MsgWZConnect msg;
		msg.set_mid(eMsg::MSG_WZ_CONNECT);
		msg.set_result(eResult::SUCCEESS);
		PBHelper::Send(sh,msg);
		PDLOG<<"zone logged in("<<sh.address()<<")\n";
		break;
	}
	default:
		break;
	}
}

