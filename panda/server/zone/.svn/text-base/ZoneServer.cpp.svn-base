// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZoneServerFwd.h"
#include <keye/htio/htio_demo.h>

#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace keye;
Server* Server::instance=nullptr;

int main(int argc, char* argv[]) {
	Server server;
	PandaNet::instance().initialize("zone.ini");
	DBProxy::instance().open(&server.pandaDB);
	server.dp.initialize();

	auto zoneAPort=(int)PandaNet::instance().config.value("ZoneAPort");
	auto zoneCPort=(int)PandaNet::instance().config.value("ZoneCPort");
	PDLOG<<"zone started, client port="<<zoneCPort<<", arena port="<<zoneAPort<<endf;

	server.clientService.run((unsigned short)zoneCPort);
	server.arenaService.run((unsigned short)zoneAPort);
	server.gatewayConnection.handler.connect();
	server.worldConnection.handler.connect();

	while(true)
	_getch();

	return 0;
}

proto3::PlayerInfo* Server::findClient(size_t sid){
	auto i=Server::instance->clientService._sessions.find(sid);
	return (i==Server::instance->clientService._sessions.end()?nullptr:&i->second->player);
}
