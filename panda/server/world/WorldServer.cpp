// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WorldServerFwd.h"
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
	PandaNet::instance().initialize("world.ini");
	DBProxy::instance().open(&server.pandaDB);

	auto worldPort=(int)PandaNet::instance().config.value("WorldZPort");
	PDLOG<<"world started, port="<<worldPort<<"\npress any key to continue ..."<<endf;

	server.worldService.run((unsigned short)worldPort);

	_getch();

	return 0;
}
