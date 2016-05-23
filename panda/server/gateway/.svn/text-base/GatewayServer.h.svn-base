// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
*
*File		: GatewayServer.h
*Desc		:
*Version	: 1.0
*Program	: Vic
*Date		: 2016-4-25
*/
// --------------------------------------------------------
#ifndef _GatewayServer_h_
#define _GatewayServer_h_

#include <GatewayServerFwd.h>
// --------------------------------------------------------
// Server
// --------------------------------------------------------
class Server{
public:
	Server(){ instance=this; }
	static Server* instance;
	PandaService<ClientSession,ClientHandler>	clientService;
	PandaService<ZoneSession,ZoneHandler>	zoneService;
	PandaDBProxy	pandaDB;
};

// --------------------------------------------------------
#endif // _GatewayServer_h_
