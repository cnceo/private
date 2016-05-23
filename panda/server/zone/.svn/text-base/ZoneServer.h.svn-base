// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: ZoneServer.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _ZoneServer_h_
#define _ZoneServer_h_

#include <ZoneServerFwd.h>
// --------------------------------------------------------
// Server
// --------------------------------------------------------
class Server{
public:
	Server(){ instance=this; }
	static Server* instance;

	PandaService<ArenaSession,ArenaHandler>		arenaService;
	PandaService<ClientSession,ClientHandler>	clientService;
	PandaService<ZoneSession,GatewayHandler>	gatewayConnection;
	PandaService<ClientSession,WorldHandler>	worldConnection;
	PandaDBProxy	pandaDB;
	DataProvider	dp;
};

// --------------------------------------------------------
#endif // _ZoneServer_h_
