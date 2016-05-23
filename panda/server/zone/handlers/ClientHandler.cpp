#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void ClientHandler::on_close(keye::svc_handler& sh){
	//PDLOG<<"client logged out("<<sh.address()<<")\n";
}

void ClientHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CZ_BEGIN||mid>=eMsg::MSG_CZ_END)return;
	switch(mid){
	case MSG_CZ_ENTER:{
		MsgCZEnter loginMsg;
		if(pb.Parse(loginMsg)){
			/*
			query player info:
				if found, login and broadcast and sync other players
				else return success
			*/
			Server::instance->pandaDB.GetPlayer(loginMsg.uid().c_str(),sh.id());
		}
		break;
	}
	case MSG_CZ_CREATE_PLAYER:{
		//TODO: broadcast
		MsgCZCreatePlayer iMsg;
		if(pb.Parse(iMsg))
			Server::instance->pandaDB.CreatePlayer(iMsg.playerinfo(),sh.id());
		break;
	}
	case MSG_CZ_UPDATE_PLAYER:{
		//TODO: broadcast
		MsgCZUpdatePlayer iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayer msg;
			msg.set_mid(eMsg::MSG_ZC_UPDATE_PLAYER);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_GET_PLAYER_EXTRA:{
		MsgCZGetPlayerExtra iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayerExtra msg;
			msg.set_mid(eMsg::MSG_ZC_UPDATE_PLAYER_EXTRA);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_UPDATE_PLAYER_EXTRA:{
		MsgCZUpdatePlayerExtra iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayerExtra msg;
			msg.set_mid(eMsg::MSG_ZC_UPDATE_PLAYER_EXTRA);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_MOVE:{
		MsgCZMove iMsg;
		if(pb.Parse(iMsg)){
			MsgZCMove msg;
			msg.set_mid(eMsg::MSG_ZC_MOVE);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";

			SyncPlayers(sh);
		}
		break;
	}
	case MSG_CZ_ENTER_ARENA:{
		MsgCZEnterArena iMsg;
		if(pb.Parse(iMsg)){
			MsgZCEnterArena msg;
			msg.set_mid(eMsg::MSG_ZC_ENTER_ARENA);
			msg.set_aid(iMsg.aid());
			msg.set_host("192.168.0.107");
			msg.set_port(7777);
			msg.set_key(keye::MD5::HashAnsiString("panda"));
			msg.set_level("Scene_MainMap");
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_UPDATE_NAME:{
		MsgCZUpdateName imsg;
		if(pb.Parse(imsg)){
			Server::instance->pandaDB.UpdateUserName(imsg.uid().c_str(),imsg.name().c_str());
			MsgZCUpdateName msg;
			msg.set_mid(eMsg::MSG_ZC_MOVE);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client update name("<<sh.address()<<")\n";
		}
		break;
	}
	default:
		break;
	}
}

void ClientHandler::SyncPlayers(keye::svc_handler& sh){
	auto& mp=Server::instance->clientService._sessions;
	if(mp.size()>1){
		auto id=sh.id();
		MsgZCSyncPlayers msg;
		msg.set_mid(eMsg::MSG_ZC_SYNC_PLAYERS);
		for(auto& i:mp){
			if(id==i.first)continue;
			auto& shi=*i.second->sh;
			PBHelper::Send(shi,msg);
		}
	}
}
