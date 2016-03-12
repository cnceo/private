// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: player.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <algorithm>
#include "game_fwd.h"

using namespace keye;
ObjectMap::ObjectMap(){}

void ObjectMap::_insert(Object* o){
	if(o){
		auto t=o->type();
		auto sid=o->sid();
		auto i=_om.find(t);
		decltype(i->second)* m=nullptr;
		if(i==_om.end()){
			decltype(i->second) newm;
			auto& j=_om.insert(std::make_pair(t,newm));
			m=&j.first->second;
		}else
			m=&i->second;
		auto ii=m->find(sid);
		if(ii==m->end())
			m->insert(std::make_pair(sid,o));
	}
}

void ObjectMap::_remove(Object* o){
	if(o){
		auto t=o->type();
		auto i=_om.find(t);
		if(i!=_om.end()){
			auto& m=i->second;
			auto sid=o->sid();
			m.erase(sid);
		}
	}
}

size_t ObjectMap::_genSid(){
	size_t id=0;
	if(!_lid.empty()){
		id=_lid.back();
		_lid.pop_back();
	}
	return id;
}

void ObjectMap::_regenSid(size_t id){
	_lid.push_back(id);
//	std::sort(_lid.begin(),_lid.end());
}
