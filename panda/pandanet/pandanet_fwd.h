// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: pandanet_fwd.h
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-10-30
 */
// --------------------------------------------------------
#ifndef _pandanet_fwd_h_
#define _pandanet_fwd_h_
// --------------------------------------------------------
#ifndef PANDA_API
#if(defined(_WIN32)||defined(_WIN64))&&_WINDLL
#if PANDA_EXPORT
#define PANDA_API __declspec(dllexport)
#else
#define PANDA_API __declspec(dllimport)
#endif
#else
#define PANDA_API
#endif
#endif //PANDA_API

#include <keye/keye_fwd.h>

#if(defined(_WIN32)||defined(_WIN64))
#include <hiredis/hiredis_win32.h>
#else
#include <hiredis/hiredis.h>
#endif

#include "protocol/game_protocol.h"
#include "protocol/game_protocol.pb.h"

#include "utils/Utils.h"
#include "utils/ObjectPool.h"
#include "settings/DataProvider.h"
#include "session/PandaService.h"
#include "session/BaseSession.h"
#include "session/ClientSession.h"
#include "session/ZoneSession.h"
#include "session/ArenaSession.h"
#include "PandaNet.h"
// --------------------------------------------------------
#endif // _pandanet_fwd_h_
