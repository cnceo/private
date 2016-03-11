#ifndef _GAME_FWD_H_
#define _GAME_FWD_H_                            1

#include <mysql/mysql.h>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <memory>
#include <stdlib.h>

#include "GameDefine.h"
#include "crc32.h"
#include "game_protocol.h"
#include "game_user.h"
#include "websocket_service.h"
#include "player.h"
#include "game.h"
#include "mysql+.h"

#ifndef KEYE_API
#if(defined(_WIN32)||defined(_WIN64))&&_WINDLL
	#if KEYE_EXPORT
		#define KEYE_API __declspec(dllexport)
	#else
		#define KEYE_API __declspec(dllimport)
	#endif
#else
	#define KEYE_API
#endif
#endif //KEYE_API

#define _LOG
#ifdef _LOG
#	define LOG printf
#else
#	define LOG
#endif

#endif
