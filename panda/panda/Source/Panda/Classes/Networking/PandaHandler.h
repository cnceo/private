// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tickable.h"
#include <memory>

#ifndef UNREAL_SOCKET

class PANDA_API ArenaCHandler:public BaseHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);
	void connect(){}
	void login(){}
};

// Client: communicates with Gateway
class PANDA_API ClientGHandler:public BaseHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);

	void connect();
	void login();

	proto3::MsgGCLogin msgGCLogin;
};

// Arena: communicates with Zone
class PANDA_API ClientAHandler:public BaseHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);

	void connect();
	void login();

	proto3::MsgZCEnterArena	EnterArena;
private:
	bool enterArena();
};

// Client: communicates with Zone
class PANDA_API ClientZHandler:public BaseHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);

	void connect();
	void login();

	void preEnterArena(proto3::MsgZCEnterArena&);
	std::string testName;
private:
};

// Client: communicates with Arena
class PANDA_API ArenaZHandler:public BaseHandler{
public:
	void on_message(keye::svc_handler&,keye::PacketWrapper&);

	void connect();
	void login();
};
#endif // UNREAL_SOCKET

