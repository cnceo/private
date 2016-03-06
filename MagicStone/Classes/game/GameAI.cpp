//
//  GameAI.cpp
//  popworld
//
//  Created by Leo Keye on 13-8-8.
//
//

#include "AppFwd.h"
#include <math.h>

enum{
    OBJ_BUBBLE=100,	//size=64
    OBJ_SKIPPER,	//size=32
	OBJ_BULLET,		//size=16
};

GameAI::GameAI()
:_player(nullptr)
,_scalar(.5f)
,_touched(false)
,_moved(false){
}

void GameAI::update(float time){
}
