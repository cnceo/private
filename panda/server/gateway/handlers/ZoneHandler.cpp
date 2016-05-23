#include "stdafx.h"
#include "GatewayServerFwd.h"

using namespace proto3;

void ZoneHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_ZG_BEGIN||mid>=eMsg::MSG_ZG_END)return;
	switch(mid){
	case eMsg::MSG_ZG_CONNECT:
	{
		MsgGZConnect msg;
		msg.set_mid(eMsg::MSG_GZ_CONNECT);
		msg.set_result(eResult::SUCCEESS);
		PBHelper::Send(sh,msg);
		PDLOG<<"zone logged in("<<sh.address()<<")\n";
		break;
	}
	default:
		break;
	}
}

