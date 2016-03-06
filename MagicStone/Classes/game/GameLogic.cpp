// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: GameLogic
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------

#include "AppFwd.h"

USING_NS_CC;
// --------------------------------------------------------
INSTANCE_IMP(GameLogic)
GameLogic::GameLogic():_mySeat(0){
}

GameLogic::~GameLogic(){
}

game_t& GameLogic::gameInfo(){
	if(!_game)_game.reset(new game_t);
	return *_game;
}

short GameLogic::mySeat()const{
	return _mySeat;
}

void GameLogic::onUpdate(game_t& u){
	memcpy(&gameInfo(),&u,sizeof(u));

	switch(u.GameState){
	case GSTATE_CHANGE:
		//deal
		for(int i=0;i<MAX_PLAYER;++i)
			if(u.m_PlayerData[i].user_id==SceneMan::instance()->userInfo().user_id){
				_mySeat=i;
				break;
		}
		CEventDispatch(onDeal,nullptr);
		break;
	}
}
// --------------------------------------------------------
