// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: player_behavior.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"

using namespace keye;

GameBehavior::GameBehavior():Behavior(game.scheduler()){}

void PlayerAuth::update(joint*){
	if(_player)game.proxy().authorize(_player->session(),_name.c_str(),_pswd.c_str());
}

void PlayerLogin::update(joint*){
}

void PlayerEnter::update(joint*){
}
