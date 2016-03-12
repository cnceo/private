// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: game_fwd.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#ifndef _game_fwd_h_
#define _game_fwd_h_

#define _USE_WEBSOCKETPP_

#include "utils/utilfwd.h"
#include "game/game_fwd.h"

#ifndef LOGGER
	#define LOGGER Game::instance()->log()
#endif
#ifndef LOG_INFO
	#define LOG_INFO LOGGER<<Begl
#endif

#endif
