#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void PlayerSystem::onLogin(const proto3::PlayerInfo& pi,ClientSession* ss){
	if(ss){
		ss->player.CopyFrom(pi);
		sessions.insert(std::make_pair(pi.uid(),ss));

		//broadcast to all
		Server::instance->clientService.handler.BroadcastPlayer(*ss->sh);
		//sync all to me
		Server::instance->clientService.handler.SyncPlayers(*ss->sh);

		//touch other systems
		Server::instance->teams.broadcast(ss->sh->id());
	}
}

void PlayerSystem::onLogout(const char* uid){
	MsgZCExit msg;
	msg.set_mid(eMsg::MSG_ZC_EXIE);
	msg.mutable_playerinfo()->set_uid(uid);
	Server::instance->clientService.handler.BroadcastMessage(msg);

	if(uid)sessions.erase(uid);
}
