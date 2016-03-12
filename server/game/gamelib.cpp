// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: game.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-3-7
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"
#include "gamelib.h"

using namespace keye;
using namespace std;

Game game;
// --------------------------------------------------------
class gamelib_impl{
public:
	int		run(int argc,char* argv[]);
	void	stop();
	bool	stopped();
private:
	std::shared_ptr<SessionHandler>	_hx;
	std::shared_ptr<Service>		_sx;
};

int gamelib_impl::run(int argc,char* argv[]){
	size_t io_thread=4,wk_thread=1;
	size_t rb_size=1460;

	game.initialize();

	const char* host=game.config().value("server");
	auto port=(unsigned short)(int)game.config().value("port");
	auto& a=game.alloc();
	_hx.reset(new SessionHandler(a));
	_sx.reset(new Service(*_hx,a,io_thread,wk_thread,rb_size));
	_sx->svc.run(port);

	return 0;
}

void gamelib_impl::stop(){
	if(_sx)_sx->svc.close();
}

bool gamelib_impl::stopped(){
	return _sx?_sx->svc.closed():true;
}
// --------------------------------------------------------
int GameLib::run(int argc,char* argv[]){
	_impl.reset(new gamelib_impl);
	return _impl?_impl->run(argc,argv):0;
}

void GameLib::stop(){
	if(_impl)_impl->stop();
}

bool GameLib::stopped(){
	return _impl?_impl->stopped():true;
}
