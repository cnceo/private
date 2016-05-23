// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: WorldServer.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _WorldServer_h_
#define _WorldServer_h_

#include <WorldServerFwd.h>
// --------------------------------------------------------
// Server
// --------------------------------------------------------
class Server{
public:
	Server(){ instance=this; }
	static Server* instance;
	PandaService<ZoneSession,ZoneHandler>	worldService;
	PandaDBProxy	pandaDB;
};

// --------------------------------------------------------
#endif // _WorldServer_h_
