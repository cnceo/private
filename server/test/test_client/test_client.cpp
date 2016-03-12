// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

using namespace keye;

int main(int argc, char* argv[]) {
	//	auto f=freopen("log.txt","w+",stdout);
	unsigned short port = 8899;
	const char* host="127.0.0.1";
	myclient(host, port, 4, 4);

	printf("press any key to continue ...\n");
	getch();

	return 0;
}
