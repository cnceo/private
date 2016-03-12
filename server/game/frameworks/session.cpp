// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: session.cpp
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
Session::Session(keye::svc_handler& sh,Alloc& ax)
:SessionBase(sh,ax),_player(nullptr){
}

Session::~Session(){
	game.objectMap().destroy(_player);
}

OpcodeHandler handlers[NUM_MSG_TYPES];
void Session::_handle(Packet& p){
	if(p.opcode>=0&&p.opcode<NUM_MSG_TYPES)
		if(auto h=handlers[p.opcode].handler)
			(this->*h)(p);
	return;
}

Player* Session::player(){
	return _player;
}

void Session::handleAuth(Packet& pack){
	buffer_wrapper bw(pack.data,pack.length);
	std::string name,pswd;
	bw>>name,bw>>pswd;

	_player=game.objectMap().create<Player>();
	_player->session(this);
	s_ptr<behavior> auth(new PlayerAuth(_player,name,pswd));
	bh_signal sig(&auth);
/*
	game.proxy().authorize(this,name.c_str(),pswd.c_str());
*/
}
// --------------------------------------------------------
