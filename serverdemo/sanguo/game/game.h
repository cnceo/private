// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: game.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-3-7
 */
// --------------------------------------------------------
#ifndef _game_h_
#define _game_h_

typedef vl::logger		Logger;
// --------------------------------------------------------
#define GAME_GLOBLE(T,N) \
	public: \
		T&	N(){ \
		if(!_##N)_##N.reset(new T); \
			return *_##N; \
		} \
	private: \
		std::shared_ptr<T>	_##N;

class Game{
	INSTANCE_DECL(Game)
public:
						~Game();
	int					run(int argc,char* argv[]);
	void				stop();
	bool				stopped();
	//globles
	GAME_GLOBLE(vl::ini_file,		config)
//	GAME_GLOBLE(Alloc,				alloc)
//	GAME_GLOBLE(joint_scheduler,	scheduler)

	GAME_GLOBLE(Players,			players)
	GAME_GLOBLE(Players,			connects)
public:
	Logger&							log();
	MYSQL*							getMysqlConn();
	MYSQL*							getMysqlLogin();

    void                            on_timer(size_t id);
	void							updateStats(time_t,bool=false);
	void							updateConcurrent(time_t);
	void							updatePaying(time_t);

	bool							Overkill;
	int								pcu;
private:
	std::shared_ptr<Logger>			_log;
	MYSQL							_mysql,_mysql_login;
    bool                            _running;
};

vl::logger& Begl(vl::logger& l);
vl::logger& Endl(vl::logger& l);

extern Game game;

#endif
