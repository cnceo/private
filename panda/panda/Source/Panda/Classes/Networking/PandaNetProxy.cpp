// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "Networking/NetworkingFwd.h"
#include "Gameplay/PandaGameInstance.h"

#ifndef UNREAL_SOCKET

void PandaNetProxy::start(){
	if(GIsServer){
		//Arena listen, connect to Zone
		auto arenaPort		=(int)PandaNet::instance().config.value("ArenaPort");
		arenaCService.run(arenaPort);
		GGameInstance->pandanet->arenaZConnection.handler.connect();
		UE_LOG(LogTemp,Warning,TEXT("Arena started on %d"));

		GGameInstance->SetupPerfCounter();
	}
}

void PandaNetProxy::close(){
}

#else

// Sets default values
UArenaProxy::UArenaProxy():socket(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}


// Called every frame
void UArenaProxy::Tick(float DeltaTime){
	typedef TSharedPtr<FArrayReader,ESPMode::ThreadSafe> FArrayReaderPtr;
	uint32 DataSize = 0;
	if(socket)while(socket->HasPendingData(DataSize)){
		FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true));
		Datagram->SetNumUninitialized(FMath::Min(DataSize,65507u));

		int32 BytesRead = 0;
		if(socket->Recv(Datagram->GetData(),Datagram->Num(),BytesRead)){
			keye::PackHelper<UClientProxy> packer;
			auto buf=Datagram->GetData();
			auto sz=Datagram->Num();
			std::vector<std::shared_ptr<void>> packets;
			packer.on_read(packets,buf,sz);
			for(auto i=packets.begin();i!=packets.end();++i){
				auto data=i->get();
				auto mid=(eMsg)*(unsigned short*)data;
				UE_LOG(LogTemp,Warning,TEXT("--------received message: %d"),(int)mid);
				switch(mid){
				case MSG_RAW:
					break;
				case MSG_CG_LOGIN:
					break;
				case MSG_GC_LOGIN:
				{
					auto& msgLogin=*(MsgGCLogin*)data;
					auto result=msgLogin.result;
					UE_LOG(LogTemp,Warning,TEXT("--------MSG_GC_LOGIN result=%d"),(int)result);
				}
				break;
				default:
					break;
				}
			}

		}
	}
}

TStatId UArenaProxy::GetStatId() const{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UArenaProxy,STATGROUP_Tickables);
}

void UArenaProxy::Init(){
	if(!bListen){
		/*
		if(!socket)
			socket=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("ArenaSocket"),false);
		auto addr=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		bool isValid=true;
		const char* url="127.0.0.1";
		uint16 port=8898;
		addr->SetIp(ANSI_TO_TCHAR(url),isValid);
		addr->SetPort(port);

		tcpListener.reset(new FTcpListener(*socket));
		*/
		FIPv4Endpoint endpoint;
		FIPv4Endpoint::Parse(TEXT("127.0.0.1:8898"),endpoint);
		tcpListener.reset(new FTcpListener(endpoint));
		tcpListener->OnConnectionAccepted().BindRaw(this,&UArenaProxy::OnAccept);

		bListen=true;
	}
}

bool UArenaProxy::OnAccept(FSocket* socket,const FIPv4Endpoint&){
	this->socket=socket;
	return true;
}

// Sets default values
UClientProxy::UClientProxy()
{
}
UClientProxy::~UClientProxy()
{
	socket=nullptr;
}

// Called every frame
void UClientProxy::Tick(float DeltaTime){
	typedef TSharedPtr<FArrayReader,ESPMode::ThreadSafe> FArrayReaderPtr;
	uint32 DataSize = 0;
	if(socket)while(socket->HasPendingData(DataSize)){
		FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true));
		Datagram->SetNumUninitialized(FMath::Min(DataSize,65507u));

		int32 BytesRead = 0;
		if(socket->Recv(Datagram->GetData(),Datagram->Num(),BytesRead)){
			keye::PackHelper<UClientProxy> packer;
			auto buf=Datagram->GetData();
			auto sz=Datagram->Num();
			std::vector<std::shared_ptr<void>> packets;
			packer.on_read(packets,buf,sz);
			for(auto i=packets.begin();i!=packets.end();++i){
				auto data=i->get();
				auto mid=(eMsg)*(unsigned short*)data;
				UE_LOG(LogTemp,Warning,TEXT("--------received message: %d"),(int)mid);
				switch(mid){
				case MSG_RAW:
					break;
				case MSG_CG_LOGIN:
					break;
				case MSG_GC_LOGIN:
				{
					auto& msgLogin=*(MsgGCLogin*)data;
					auto result=msgLogin.result;
					UE_LOG(LogTemp,Warning,TEXT("--------MSG_GC_LOGIN result=%d"),(int)result);
				}
				break;
				default:
					break;
				}
			}

		}
	}
}

void UClientProxy::Login(const char* url,unsigned short port){
	if(!bLogin){
		if(!socket)
			socket=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("ClientSocket"),false);
		auto addr=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		/*
		FIPv4Address ip;
		FString address=TEXT("localhost");
		FIPv4Address::Parse(address,ip);
		addr->SetIp(ip.GetValue());
		*/
		bool isValid=true;
		addr->SetIp(ANSI_TO_TCHAR(url),isValid);
		addr->SetPort(port);

		if(socket->Connect(*addr)){
			MsgCGLogin msg;
			msg.mid=eMsg::MSG_CG_LOGIN;
			sprintf(msg.name,"test0001");

			keye::PacketWrapper pw(&msg,sizeof(msg));
			keye::HeadPacker packer;
			packer<<pw;
			packer>>pw;
			this->send(pw.data,pw.length);
		} else
			socket=nullptr;
	}
}

void UClientProxy::send(void* buf,size_t len){
	int sent=0;
	if(socket){
		socket->Send((uint8*)buf,len,sent);
	}
}

TStatId UClientProxy::GetStatId() const{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UClientProxy,STATGROUP_Tickables);
}

void PandaNetProxy::start(){
	//setup urls
	const char* arenaHost="127.0.0.1",
		*zoneHost="127.0.0.1",
		*clientHost="127.0.0.1";
	const uint16 arenaPort=8898,
		zonePort=8899;
	return;

	if(GIsServer){
		//Arena
	} else{
		//Client
	}
}

void PandaNetProxy::close(){

}

#endif //UNREAL_SOCKET