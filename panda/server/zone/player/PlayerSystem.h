// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: PlayerSystem.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _PlayerSystem_h_
#define _PlayerSystem_h_

/* PlayerSystem maintains map: uid->session
		session maintains shid,uid( PlayerInfo )
	service mainstais map: shid->session */
class PlayerSystem{
public:
	void		onLogin(const proto3::PlayerInfo&,ClientSession*);
	void		onLogout(const char*);
	//[uid,session]
	std::map<std::string,ClientSession*> sessions;
};
// --------------------------------------------------------
#endif // _PlayerSystem_h_
