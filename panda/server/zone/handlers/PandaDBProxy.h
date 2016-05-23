// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: PandaDBProxy.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _PandaDBProxy_h_
#define _PandaDBProxy_h_

enum eQid{
	GET_PLAYER,
	CREATE_PLAYER,
	UPDATE_PLAYER,
	REMOVE_PLAYER,

	UPDATE_NAME,
};
// --------------------------------------------------------
class PandaDBProxy:public IDBHandler{
public:
	virtual void	handle(int qid,DBResult* res=nullptr,void* privdata=nullptr);
					PandaDBProxy();
	void			GetPlayer(const char*,size_t);
	void			CreatePlayer(const proto3::PlayerInfo&,size_t);
	void			UpdatePlayer(const proto3::PlayerInfo&,size_t);
	void			RemovePlayer(int,const char*,size_t);

	void			UpdateUserName(const char*,const char*);
private:
	void			parsePlayerInfo(proto3::PlayerInfo&,const std::vector<DBResult>&);
	std::string		_db;
};

// --------------------------------------------------------
#endif // _PandaDBProxy_h_
