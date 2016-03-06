//
//  GamePlayer.cpp
//  popworld
//
//  Created by Leo Keye on 13-8-9.
//
//

#include "AppFwd.h"

USING_NS_CC;

GamePlayer::GamePlayer(Sprite* s)
:GameUnit(s){
}

GamePlayer* GamePlayer::create(cocos2d::Sprite* s){
    GamePlayer* u=new GamePlayer(s);
    if(u&&u->init()){
        u->autorelease();
    }else{
        delete u;
        u=nullptr;
    }
    return u;
}
