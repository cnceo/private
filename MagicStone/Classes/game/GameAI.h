//
//  GameAI.h
//  popworld
//
//  Created by Leo Keye on 13-8-8.
//
//

#ifndef __popworld__GameAI__
#define __popworld__GameAI__

#include "cocos2d.h"

class GameUnit;
class GamePlayer;
class GameAI : public cocos2d::Layer{
public:
                    GameAI();
	void			update(float time);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameAI);
private:
	GamePlayer*		_player;

    cocos2d::Point  _touchPoint;
    bool            _touched,_moved;
    float			_scalar;
};


#endif /* defined(__popworld__GameAI__) */
