// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: player.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _player_h_
#define _player_h_

class Session;
class Player:public Creature{
public:
	//behaviors
	void			login();
	void			enter();
	void			walk(){
		printf("I'm walking.\n");
	}
	//
	Session*		session();
	void			session(Session*);
private:
	unsigned long long guid;

	friend class	ObjectMap;
					Player(){_type=PLAYER;}
					~Player(){}
	Session*		_session;
};

#endif