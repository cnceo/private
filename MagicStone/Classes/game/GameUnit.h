//
//  GameUnit.h
//  popworld
//
//  Created by Leo Keye on 13-8-8.
//
//

#ifndef __popworld__GameUnit__
#define __popworld__GameUnit__

#include "cocos2d.h"

class GameUnit : public cocos2d::Node{
public:
                        GameUnit(cocos2d::Sprite*);
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool        init();
    virtual void        update(float);
    
	void				removeSelf();

    cocos2d::Sprite*	sprite;
    cocos2d::Point		direction;
    float               speed;
	float				life_time;
	bool				updated_;

    static GameUnit*    create(cocos2d::Sprite*);
protected:
	bool				_alive(float);
};


#endif /* defined(__popworld__GameUnit__) */
