#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

ClientSession* Level::findSession(const char* uid){
	auto i=sessions.find(uid);
	return (i==sessions.end()?nullptr:i->second);
}

proto3::PlayerInfo* Level::findPlayer(const char* uid){
	auto ss=findSession(uid);
	return ss?&ss->player:nullptr;
}

void Level::onPlayerEnter(const ClientSession& ss){
	auto& pi=ss.player;
	auto uid=pi.uid().c_str();
	if(nullptr==findPlayer(uid)){
		sessions.insert(std::make_pair(uid,(ClientSession*)&ss));

		//broadcast to all
		BroadcastPlayer(uid);
		//sync all to me
		SyncPlayers(uid);
		PDLOG<<"----enter Level "<<uid<<keye::endl;
	}
	else
		PDLOG<<"----duplicated enter Level "<<uid<<keye::endl;
}

void Level::onPlayerLeave(const char* uid){
	auto pi=findPlayer(uid);
	if(pi){
		MsgZCExit msg;
		msg.set_mid(eMsg::MSG_ZC_EXIT);
		msg.mutable_player()->set_uid(uid);
		BroadcastMessage(msg,nullptr,uid);

		PDLOG<<"----leave Level "<<uid<<keye::endl;
		sessions.erase(uid);
	}
	else
		PDLOG<<"----error leave Level "<<uid<<keye::endl;
}

void Level::SyncPlayers(const char* uid){
	//sync all players to one
	if(sessions.size()>1){
		MsgZCSyncPlayers msg;
		msg.set_mid(eMsg::MSG_ZC_SYNC_PLAYERS);
		for(auto& i:sessions){
			if(i.first==uid)continue;
			auto p=msg.add_players();
			p->CopyFrom(i.second->player);
		}

		auto ss=findSession(uid);
		if(ss)PBHelper::Send(*ss->sh,msg);
	}
}

void Level::BroadcastPlayer(const char* uid){
	//broadcast player to others
	if(sessions.size()>1){
		MsgZCBroadcastPlayer msg;
		msg.set_mid(eMsg::MSG_ZC_BROADCAST_PLAYER);
		if(auto me=findPlayer(uid)){
			msg.mutable_player()->CopyFrom(*me);
			BroadcastMessage(msg,nullptr,uid);
		}
	}
}

void Level::BroadcastMessage(::google::protobuf::MessageLite& msg,std::vector<std::string>* uids,const char* uid){
	auto& allplayers=Server::instance->players.sessions;
	if(uids)for(auto& i:*uids){
		//to range
		if(uid&&i==uid)continue;
		auto ss=findSession(i.c_str());
		if(ss)PBHelper::Send(*ss->sh,msg);
	} else{
		//to all
		for(auto& i:sessions){
			if(uid&&i.first==uid)continue;
			auto ss=findSession(i.first.c_str());
			if(ss)PBHelper::Send(*ss->sh,msg);
		}
	}
}
