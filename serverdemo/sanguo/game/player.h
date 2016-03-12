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

class GoType;

class Player{
public:
	enum sock_type	{ST_SOCKET,ST_WEBSOCKET};
                    Player(std::weak_ptr<void>);
    //send raw data
    void			send(const void* buf,size_t len);
					~Player();
	void			release();
//	virtual void	handle(svc_handler&,const keye::packet_t& p);
	//close socket
	void			close();
	//send packet
    void			Send(const void* buf,size_t len);
	//牌库操作
	void			writeCards();
	char*			getCardsBuffer();
	int				getCardsBuffer_Size();
	void			updateCards(short cid,short count);
	int				GetThisCardCount(short cid);
	void			clearCards();
	//behaviors
	void			login(int);
	void			enter();
	void			update();
	static int		getCardPrice(short cid);

	std::shared_ptr<userData>	spData;
	
	void			update_Timer();
	void			update_db();
	void			ChangeAward_Count(int);
	int				GetAward_Count();
	void			logOut();

	time_t			time_login,time_signal;
private:
	void			_readCards();

	sock_type		_sock_type;
	size_t			_client_id;
	std::shared_ptr<std::vector<char>>	_cacheCards;	//全牌表
	bool			AllCardChange;		// 全牌表有变动
	int				Award_Count;		// 补充包数量
	int				Award_Count_Add;	// 补充包 增加数
	int				Award_Count_Del;	// 补充包 减少数
	
#ifdef CARD_NEW
public:
	short	CardsAll[HeroCount][MAX_CARD];	//牌组信息
	bool	CardsAllSign[HeroCount];		//DB写库标记
	int		CardsAllActive[HeroCount];		//是否使用标记
#endif

    std::weak_ptr<void>             _wsppsh;

    unsigned long long guid;

	friend class	ObjectMap;
};

class Players{
public:
	void		add(size_t,Player*);
	Player*		find(size_t);
	void		remove(size_t);
	std::map<size_t,Player*>&	all(){return _players;}
	void		update();
private:
	std::map<size_t,Player*>	_players;
};

class Task
{
public:
	static void Update(size_t client_id);
	static int  Task_Win(size_t client_id);
};



class ContinueWin
{
public:
	static void SwitchOp(size_t client_id,int mode);
	static void Win(size_t client_id,int mode,int& Num, int& Score ,int& bagNum);
	static void Lost(size_t client_id,int mode,int& Num, int& Score ,int& bagNum);
	static char IsContinue(int mode,char Src){ return(eGame_Pay==mode)?0:Src;};
};

#endif
