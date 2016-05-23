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
	/*
	ObjectPool<int> pool;
	auto p=pool.create();
	pool.destroy(p);
	p=pool.create();
	auto p1=pool.create();
	auto p2=pool.create();
	auto p3=pool.create();
	pool.destroy(p1);
	pool.destroy(p2);
	pool.destroy(p3);
	return 0;
	*/
	Server server;
	PandaNet::instance().initialize("gateway.ini");
	DBProxy::instance().open(&server.pandaDB);

	auto gatewayPort=(int)PandaNet::instance().config.value("GatewayCPort");
	auto zonePort=(int)PandaNet::instance().config.value("GatewayZPort");
	PDLOG<<"gateway started, client port="<<gatewayPort<<", zone port="<<zonePort<<"\npress any key to continue ..."<<endf;

	server.clientService.run((unsigned short)gatewayPort);
	server.zoneService.run((unsigned short)zonePort);

	//Server::instance->pandaDB.QueryUser(10000);

	getch();
	return 0;
}
