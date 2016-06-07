#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void PlayerSystem::onLogin(const proto3::PlayerInfo& pi,ClientSession* ss){
	if(ss){
		ss->player.CopyFrom(pi);
		sessions.insert(std::make_pair(pi.uid(),ss));

		//touch other systems
		Server::instance->levels.onPlayerEnter(*ss);
		Server::instance->teams.broadcast(ss->sh->id());

		//加载角色道具并同步给客户端
		PDLOG << pi.id()<<": start player item!\n";
		Server::instance->pandaItems.loadPlayerItem(pi.id());
		PDLOG << pi.id()<< "load player item complete!\n";

		PDLOG << pi.id()<< "start syn player item!\n";
		Server::instance->pandaItems.synItemInfo(*ss->sh);
		PDLOG << pi.id()<<"syn item info to client complete!\n";
	}
}

void PlayerSystem::onLogout(const char* uid){
	auto i=sessions.find(uid);
	if(i==sessions.end()){
		return;
	}

	auto it = sessions.find(uid);
	//删除该角色道具相关信息
	if (it != sessions.end())
	{
		size_t playerId = it->second->player.id();
		Server::instance->pandaItems.removePlayerAllItem(playerId);
	}

	//touch other systems
	auto& pi = i->second->player;
	Server::instance->levels.onPlayerLeave(pi);
	if (uid)sessions.erase(uid);

	PDLOG<<"Player("<<(int)sessions.size()<<") logout player: "<<uid<<keye::endl;
}
