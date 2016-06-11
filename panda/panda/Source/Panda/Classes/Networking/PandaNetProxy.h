// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tickable.h"
#include <memory>

#ifndef UNREAL_SOCKET

class PANDA_API PandaNetProxy{
public:
	void start();
	void close();
	PandaService<ClientSession,ArenaCHandler>	arenaCService;		// Arena service for Client
	PandaService<ArenaSession,ArenaZHandler>	arenaZConnection;	// Arena connection to Zone
	PandaService<ClientSession,ClientGHandler>	clientGConnection;	// Client connection to Gateway
	PandaService<ClientSession,ClientZHandler>	clientZConnection;	// Client connection to Zone
	PandaService<ClientSession,ClientAHandler>	clientAConnection;	// Client connection to Arena
};

#else

class FSocket;
class FTcpListener;
struct FIPv4Endpoint;

class PANDA_API UClientProxy: public FTickableGameObject
{
public:
	// Sets default values for this actor's properties
	UClientProxy();
	~UClientProxy();

	void connect(const char*,uint16);
	virtual bool IsTickable() const{ return true; }

	/** return the stat id to use for this tickable **/
	virtual TStatId GetStatId() const;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void Login(const char* url,unsigned short port);

	void send(void* buf,size_t length);
private:
	bool		bLogin;
	FSocket*	socket;
};

class PANDA_API UArenaProxy : public FTickableGameObject
{
public:	
	// Sets default values for this actor's properties
	UArenaProxy();

	virtual bool IsTickable() const{ return true; }

	/** return the stat id to use for this tickable **/
	virtual TStatId GetStatId() const;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Init();
private:
	bool OnAccept(FSocket*,const FIPv4Endpoint&);
	bool		bListen;
	FSocket*	socket;
	std::shared_ptr<FTcpListener> tcpListener;
};

class PANDA_API PandaNetProxy{
public:
	void start();
	void close();
};
#endif // UNREAL_SOCKET

