#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void LevelSystem::init(const char* cfg){

}

Level* LevelSystem::findLevel(unsigned id){
	auto i=levels.find(id);
	if(i!=levels.end()) return &i->second;
	else return nullptr;
}

Level* LevelSystem::findLevelBySh(size_t shid){
	if(auto pi=Server::instance->findClient(shid))
		return findLevel(pi->lastplace().nmapid());
	return nullptr;
}


void LevelSystem::onPlayerEnter(const ClientSession& ss){
	auto& pi=ss.player;
	auto lid=pi.lastplace().nmapid();
	auto level=Server::instance->levels.findLevel(lid);
	if(!level){
		//TODO: init levels from config
		Server::instance->levels.levels.insert(std::make_pair(lid,Level()));
		level=Server::instance->levels.findLevel(lid);
	}
	level->onPlayerEnter(ss);
}

void LevelSystem::onPlayerLeave(const proto3::PlayerInfo& pi){
	auto lid=pi.lastplace().nmapid();
	if(auto level=Server::instance->levels.findLevel(lid))
		level->onPlayerLeave(pi.uid().c_str());

}
