//
//  GamePlayer.h
//  popworld
//
//  Created by Leo Keye on 13-8-9.
//
//

#ifndef __popworld__GamePlayer__
#define __popworld__GamePlayer__

#include "cocos2d.h"

class GamePlayer : public GameUnit{
public:
						GamePlayer(cocos2d::Sprite*);
    
    static GamePlayer*	create(cocos2d::Sprite*);
private:
};


#endif /* defined(__popworld__GamePlayer__) */
