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

#define GAME_GLOBLE(T,N) \
	public: \
		T&	N(){ \
		if(!_##N)_##N.reset(new T); \
			return *_##N; \
		} \
	private: \
		std::shared_ptr<T>	_##N;

class Game{
public:
						~Game();
	void				initialize();
	//globles
	GAME_GLOBLE(ini_file,			config)
	GAME_GLOBLE(Alloc,				alloc)
	GAME_GLOBLE(joint_scheduler,	scheduler)
#ifndef NO_MYSQL
	GAME_GLOBLE(Proxy,				proxy)
#endif
//	GAME_GLOBLE(ProxyHandler,		proxy_handler)
	//logic
	GAME_GLOBLE(ObjectMap,			objectMap)
};

extern Game game;

#endif
