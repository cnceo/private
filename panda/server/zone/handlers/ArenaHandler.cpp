#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void ArenaHandler::on_close(keye::svc_handler& sh){
	//PDLOG<<"arena logged out("<<sh.address()<<")\n";
}

void ArenaHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_ZA_BEGIN||mid>=eMsg::MSG_ZA_END)return;
	switch(mid){
	case eMsg::MSG_AZ_CONNECT:{
		MsgZAConnect msg;
		msg.set_mid(eMsg::MSG_ZA_CONNECT);
		msg.set_zid(100);
		PBHelper::Send(sh,msg);
		PDLOG<<"arena logged in("<<sh.address()<<")\n";
		break;
	}
	case eMsg::MSG_AZ_UPDATE_PLAYER:{
		MsgCZUpdatePlayer iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayer msg;
			msg.set_mid(eMsg::MSG_ZA_UPDATE_PLAYER);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case eMsg::MSG_AZ_UPDATE_PLAYER_EXTRA:{
		MsgCZUpdatePlayerExtra iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayerExtra msg;
			msg.set_mid(eMsg::MSG_ZA_UPDATE_PLAYER_EXTRA);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	default:
		break;
	}
}

