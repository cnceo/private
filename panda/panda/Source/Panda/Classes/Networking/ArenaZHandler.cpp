// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "Networking/NetworkingFwd.h"
#include "PandaGameInstance.h"

#ifndef UNREAL_SOCKET
using namespace proto3;

// Arena connection to Zone
void ArenaZHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_ZA_BEGIN||mid>=eMsg::MSG_ZA_END)return;
	switch(mid){
	case eMsg::MSG_ZA_CONNECT:
		UE_LOG(LogTemp,Warning,TEXT("--------connected to zone(%s:%d)"),ANSI_TO_TCHAR(sh.address().c_str()),sh.port());
		break;
	default:
		break;
	}
}

void ArenaZHandler::connect(){
	//Arena listen, connect to Zone
	auto zoneHost		=(const char*)PandaNet::instance().config.value("ZoneHost");
	auto zoneAPort		=(int)PandaNet::instance().config.value("ZoneAPort");
	GGameInstance->pandanet->arenaZConnection.connect(zoneHost,zoneAPort);
	UE_LOG(LogTemp,Warning,TEXT("Connect to Zone(%s:%d)"),ANSI_TO_TCHAR(zoneHost),zoneAPort);
}

void ArenaZHandler::login(){
	MsgAZConnect msg;
	msg.set_mid(eMsg::MSG_AZ_CONNECT);
	PBHelper::Send(*GGameInstance->pandanet->arenaZConnection.handler.shClient,msg);
}

#endif //UNREAL_SOCKET