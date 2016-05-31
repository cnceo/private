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
