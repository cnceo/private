#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

proto3::PlayerInfo* Level::findPlayer(size_t sid){
	auto i=players.find(sid);
	return (i==players.end()?nullptr:i->second);
}

void Level::onPlayerEnter(size_t sid){
	auto& mp=Server::instance->clientService._sessions;
	for(auto i:mp){
		auto id=i.first;
		if(id==sid)continue;
		auto sh=i.second->sh;
		//sync
	}

	auto i=mp.find(sid);
	if(i!=mp.end()){
		auto& pi=i->second->player;
		players.insert(std::make_pair(sid,&pi));
	}

	//PlayerSystem

	//TeamSystem
}

void Level::onPlayerLeave(size_t sid){
	auto& mp=Server::instance->clientService._sessions;

	//PlayerSystem

	//TeamSystem

	for(auto i:mp){
		auto id=i.first;
		if(id==sid)continue;
		auto sh=i.second->sh;
		//sync
	}
	auto i=mp.find(sid);
	if(i!=mp.end()){
		auto& pi=i->second->player;
		Server::instance->players.onLogout(pi.uid().c_str());
		players.erase(sid);
	}
}
