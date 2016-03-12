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
#include "game_fwd.h"

using namespace keye;

void Player::login(){
}

void Player::enter(){
}

Session* Player::session(){
	return _session;
}

void Player::session(Session* s){
	_session=s;
}
