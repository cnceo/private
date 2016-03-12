// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: walk.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _walk_h_
#define _walk_h_

class Walk:public Behavior<>{
public:
					Walk(Player* p,joint_scheduler& sx)
						:Behavior(sx)
						,_player(p){}
	//derived from joint_observer,do real action
	virtual void	update(joint*){if(_player)_player->walk();};
private:
	Player*			_player;
};

#endif