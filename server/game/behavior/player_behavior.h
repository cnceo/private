// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: player_behavior.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _player_behavior_h_
#define _player_behavior_h_

class GameBehavior:public Behavior<>{
public:
					GameBehavior();
	virtual			~GameBehavior(){}
};

class PlayerBehavior:public GameBehavior{
public:
					PlayerBehavior(Player* p):_player(p){}
	virtual			~PlayerBehavior(){}
protected:
	Player*			_player;
};
// --------------------------------------------------------
class PlayerAuth:public PlayerBehavior{
public:
					PlayerAuth(Player* p,const std::string& name,const std::string& pswd)
						:PlayerBehavior(p),_name(name),_pswd(pswd){}
	virtual void	update(joint*);
	std::string		_name,_pswd;
};
// --------------------------------------------------------
class PlayerLogin:public PlayerBehavior{
public:
					PlayerLogin(Player* p):PlayerBehavior(p){}
	virtual void	update(joint*);
};
// --------------------------------------------------------
class PlayerEnter:public PlayerBehavior{
public:
					PlayerEnter(Player* p):PlayerBehavior(p){}
	virtual void	update(joint*);
};
// --------------------------------------------------------
#endif