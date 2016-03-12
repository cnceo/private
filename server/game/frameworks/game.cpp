// --------------------------------------------------------
/*Copyright Keye Knew.All rights reserved.
 *
 *File		: game.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: Keye Knew
 *Date		: 2012-3-7
 */
// --------------------------------------------------------
#include "stdafx.h"
#include "game_fwd.h"

using namespace keye;
using namespace std;
// --------------------------------------------------------
Game::~Game(){
}

void Game::initialize(){
	config().load("server.ini");

	init_protocal();
	//connect to mysql
	const char
		*host=_config->value("mysql_host"),
		*user=_config->value("mysql_user"),
		*pswd=_config->value("mysql_pswd"),
		*db=_config->value("mysql_db");
	auto port=(unsigned short)(int)_config->value("mysql_port");
	proxy().connect(host,port,user,pswd,db);
}
