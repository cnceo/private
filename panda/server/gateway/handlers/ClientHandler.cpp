#include "stdafx.h"
#include "GatewayServerFwd.h"

using namespace proto3;

void ClientHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CG_BEGIN||mid>=eMsg::MSG_CG_END)return;
	switch(mid){
	case MSG_CG_LOGIN:
	{
		MsgCGLogin imsg;
		if(pb.Parse(imsg)){
			Server::instance->pandaDB.QueryUser(imsg,sh.id());
			PDLOG<<"client logging("<<sh.address()<<")\n";
		}
	}
	break;
	default:
		break;
	}
}

