//
//  GameUnit.cpp
//  popworld
//
//  Created by Leo Keye on 13-8-8.
//
//

#include "AppFwd.h"

USING_NS_CC;

GameUnit::GameUnit(Sprite* s)
:sprite(s)
,direction(4.f,2.f)
,speed(3.f)
,life_time(FLT_MAX)
,updated_(false){
    direction.normalize();
}

GameUnit* GameUnit::create(cocos2d::Sprite* s){
    GameUnit* u=new GameUnit(s);
    if(u&&u->init()){
        u->autorelease();
    }else{
        delete u;
        u=nullptr;
    }
    return u;
}

// on "init" you need to initialize your instance
bool GameUnit::init(){
    // 1. super init first
    if ( !CCNode::init())
        return false;
//    this->addChild(sprite);
    this->scheduleUpdateWithPriority(0);
    return true;
}

void GameUnit::update(float time){
	if(_alive(time)){
		Point p=this->getPosition();
		p=p+direction*speed;
	}
}

void GameUnit::removeSelf(){
	if(sprite){
		sprite->removeFromParent();
		sprite=nullptr;
	}
	removeFromParent();
}

bool GameUnit::_alive(float time){
	bool alive=life_time>0.f&&life_time-time>0.f;
	
	if(!alive){
		removeSelf();
		return false;
	}else
		life_time-=time;
	return true;
}

