// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "Networking/NetworkingFwd.h"
#include "PandaUtils.h"
#include "PandaGameInstance.h"

#ifndef UNREAL_SOCKET
using namespace proto3;

// Client connection to Arena
void ClientAHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CA_BEGIN||mid>=eMsg::MSG_CA_END)return;
	switch(mid){
	case eMsg::MSG_AC_ENTER:{
		enterArena();
		break;
	}
	default:
		break;
	}
}

bool ClientAHandler::enterArena() {
	FString error;
	if(!GGameInstance||!GEngine)
		error="invalid GameInstance or Engine";
	else if(EnterArena.level().empty())
		//need MsgACEnter
		error="need connect to Arena server";
	else{
		auto& imsg=EnterArena;
		FString host=ANSI_TO_TCHAR(imsg.host().c_str());
		FString level=ANSI_TO_TCHAR(imsg.level().c_str());
		auto port=imsg.port();

		FURL url;
		url.Host=host;
		url.Port=port;
		url.Map=level;
		auto UserId = FPlatformMisc::GetUniqueDeviceId();
		if(UserId.Len()>0){
			UserId=TEXT("udid=")+UserId;
			url.AddOption(*UserId);
		}
		auto idx=level.Find(TEXT("?"));
		if(level.IsValidIndex(idx)){
			url.Map=level.Mid(0,idx);
			auto Options=level.Mid(idx);
			FString Pair;
			while(UGameplayStatics::GrabOption(Options,Pair))
				url.AddOption(*Pair);
		}
		auto ctx=GGameInstance->GetWorldContext();
		if(EBrowseReturnVal::Failure!=GEngine->Browse(*ctx,url,error)){
			UE_LOG(LogTemp,Warning,TEXT("entered Arena(%s:%d)"),*host,port);
			return true;
		}
	}
	UE_LOG(LogTemp,Error,TEXT("enter Arena failed: %s"),*error);
	return false;
}

void ClientAHandler::connect(){
	//need connect to Arena
	auto arenaHost		=(const char*)PandaNet::instance().config.value("ArenaHost");
	auto arenaPort		=(int)PandaNet::instance().config.value("ArenaPort");
	UE_LOG(LogTemp,Warning,TEXT("connect to Arena(%s:%d)"),ANSI_TO_TCHAR(arenaHost),arenaPort);
	GGameInstance->pandanet->clientAConnection.connect(arenaHost,arenaPort);
}

void ClientAHandler::login(){
	//MsgGCLogin& imsg=GGameInstance->pandanet->clientGConnection.handler.msgGCLogin;	MsgZCEnterArena
	auto key="panda";//imsg.key();

	MsgCAEnter omsg;
	omsg.set_mid(eMsg::MSG_CA_ENTER);
	omsg.set_key(key);
	PBHelper::Send(*shClient,omsg);
}


#endif //UNREAL_SOCKET