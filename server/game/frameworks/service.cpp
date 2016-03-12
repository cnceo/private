// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: service.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"

using namespace keye;
// --------------------------------------------------------
Service::Service(SessionHandler& w,Alloc& a,size_t ios,size_t works,size_t rb_size)
	:svc(w,a,ios,works,rb_size){}

void Service::add(size_t id,Session* r){
	if(!find(id)){
		_sessions.insert(std::make_pair(id,r));
	}
}

void Service::remove(size_t id){
	_sessions.erase(id);
}

Session* Service::find(size_t id){
	auto i=_sessions.find(id);
	return i==_sessions.end()?nullptr:i->second;
}
