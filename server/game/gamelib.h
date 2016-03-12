// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: gamelib.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-3-7
 */
// --------------------------------------------------------
#ifndef _gamelib_h_
#define _gamelib_h_

#ifndef GAME_API
#if(defined(_WIN32)||defined(_WIN64))&&_WINDLL
	#if GAME_EXPORT
		#define GAME_API __declspec(dllexport)
	#else
		#define GAME_API __declspec(dllimport)
	#endif
#else
	#define GAME_API
#endif
#endif //GAME_API

class gamelib_impl;
class GAME_API GameLib{
public:
	int		run(int argc,char* argv[]);
	void	stop();
	bool	stopped();
private:
	std::shared_ptr<gamelib_impl>	_impl;
};

#endif
