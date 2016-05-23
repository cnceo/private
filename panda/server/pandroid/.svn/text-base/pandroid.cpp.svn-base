// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PandroidFwd.h"
#include <keye/htio/htio_demo.h>

#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

using namespace keye;

// --------------------------------------------------------
// Pandroid
// --------------------------------------------------------
int main(int argc, char* argv[]) {
	PandaNet::instance().initialize("pandroid.ini");

	auto gatewayHost=(const char*)PandaNet::instance().config.value("GatewayHost");
	auto gatewayPort=(int)PandaNet::instance().config.value("GatewayCPort");

	PandaService<ClientSession,PandroidHandler>	pandroid;
	pandroid.connect(gatewayHost,gatewayPort);

	PDLOG<<"press any key to continue ...\n";
	_getch();

	return 0;
}
