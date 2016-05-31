// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: Level.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _Level_h_
#define _Level_h_

class Level{
public:
	proto3::PlayerInfo*	findPlayer(size_t sid);
	void				onPlayerEnter(size_t sid);
	void				onPlayerLeave(size_t sid);

	unsigned			id;
	std::string			name;
	//dungeons
	std::map<size_t,proto3::PlayerInfo*>	players;
	std::map<size_t,proto3::PlayerInfo>		monsters,npcs;
};
// --------------------------------------------------------
#endif // _Level_h_
