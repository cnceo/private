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
	ClientSession*		findSession(const char*);
	proto3::PlayerInfo*	findPlayer(const char*);
	void				onPlayerEnter(const ClientSession&);
	void				onPlayerLeave(const char*);

	void				BroadcastMessage(::google::protobuf::MessageLite&,std::vector<std::string>* uids=nullptr,const char* =nullptr);
	void				BroadcastPlayer(const char*);
	void				SyncPlayers(const char*);

	unsigned			id;
	std::string			name;
	//dungeons
	std::map<std::string,ClientSession*>		sessions;
	std::map<std::string,proto3::PlayerInfo>	monsters,npcs;
};
// --------------------------------------------------------
#endif // _Level_h_
