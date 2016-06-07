// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GatewayServerFwd.h"
#include <keye/htio/htio_demo.h>

#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

using namespace keye;
Server* Server::instance=nullptr;

int main(int argc, char* argv[]) {
	Server server;
	PandaNet::instance().initialize("gateway.ini");
	DBProxy::instance().open(&server.pandaDB);

	auto gatewayPort=(int)PandaNet::instance().config.value("GatewayCPort");
	auto zonePort=(int)PandaNet::instance().config.value("GatewayZPort");
	PDLOG<<"gateway started, client port="<<gatewayPort<<", zone port="<<zonePort<<"\npress any key to continue ..."<<endf;

	server.clientService.run((unsigned short)gatewayPort);
	server.zoneService.run((unsigned short)zonePort);

	getch();
	return 0;
}
