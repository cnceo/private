// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaUtils.h"
#include "Engine.h"
#include "BaseCharacter.h"
#include <Engine/GameEngine.h>
#include "Networking/NetworkingFwd.h"

#ifndef UNREAL_SOCKET
using namespace proto3;

// Client connection to Gateway
void ClientGHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CG_BEGIN||mid>=eMsg::MSG_CG_END)return;
	switch(mid){
	case eMsg::MSG_GC_LOGIN:{
		if(pb.Parse(msgGCLogin)){
			GGameInstance->pandanet->clientZConnection.handler.testName=msgGCLogin.name();

			if(msgGCLogin.zoneinfo_size()>0){
				UE_LOG(LogTemp,Warning,TEXT("--------logged into Gateway(%s:%d)"),ANSI_TO_TCHAR(sh.address().c_str()),sh.port());
				if(msgGCLogin.zoneinfo_size()<=0){
					UE_LOG(LogTemp,Warning,TEXT("--------no Zone info"));
				}else if(GGameInstance&&GGameInstance->pandanet){
					//close gateway
					//sh.close();
					bLogin=true;

					auto& h=GGameInstance->pandanet->clientZConnection.handler;
					if(h.shClient)
						h.login();
					else
						h.connect();
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

void ClientGHandler::connect(){
	auto gatewayHost	=(const char*)PandaNet::instance().config.value("GatewayHost");
	auto gatewayPort	=(int)PandaNet::instance().config.value("GatewayCPort");
	GGameInstance->pandanet->clientGConnection.connect(gatewayHost,gatewayPort);
	UE_LOG(LogTemp,Warning,TEXT("connect to Gateway(%s:%d)"),ANSI_TO_TCHAR(gatewayHost),gatewayPort);
}

void ClientGHandler::login(){
	auto udid = TCHAR_TO_ANSI(*FPlatformMisc::GetUniqueDeviceId());

	MsgCGLogin msg;
	msg.set_mid(eMsg::MSG_CG_LOGIN);
	msg.set_id(udid);
	msg.set_account(udid);
	msg.set_udid(udid);
	msg.set_name("test_name");
	msg.set_clientversion(100);		//00.10.00
	msg.set_type(AccountType::PC);
	PBHelper::Send(*shClient,msg);
}
#endif //UNREAL_SOCKET