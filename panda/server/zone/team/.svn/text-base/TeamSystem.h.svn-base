// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: TeamSystem.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _TeamSystem_h_
#define _TeamSystem_h_

class TeamSystem{
public:
	proto3::TeamInfo*		create(size_t,proto3::TeamInfo&,proto3::eResult&);
	proto3::TeamInfo*		update(proto3::TeamInfo&);
	proto3::TeamInfo*		find(const char*);
	void					remove(const char*);

	int						check(const proto3::TeamInfo&,const proto3::PlayerInfo&);
	bool					dismiss(size_t,const proto3::TeamInfo&);
	//proto3::TeamInfo*		kick(size_t,const proto3::TeamInfo&,const proto3::PlayerInfo&);

	bool					joinable(const proto3::TeamInfo&,const proto3::PlayerInfo&);
	proto3::TeamInfo*		join(const proto3::TeamInfo&,const proto3::PlayerInfo&);
	proto3::TeamInfo*		apply(size_t,const proto3::PlayerInfo&,bool ok);
	proto3::TeamInfo*		leave(size_t,const proto3::TeamInfo&,proto3::eResult&);

	void					broadcast(size_t=0);
private:
	std::map<std::string,proto3::TeamInfo>	teams;
};
// --------------------------------------------------------
#endif // _TeamSystem_h_
