// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "Networking/NetworkingFwd.h"

#ifndef UNREAL_SOCKET
using namespace proto3;

// Client connection to Zone
void ClientZHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	UE_LOG(LogTemp,Warning,TEXT("--------Zone on_message %d(%s:%d)"),(int)mid,ANSI_TO_TCHAR(sh.address().c_str()),sh.port());
	if(mid<=eMsg::MSG_CZ_BEGIN||mid>=eMsg::MSG_CZ_END)return;
	switch(mid){
	case MSG_ZC_ENTER:
	{
		// 同意进入创建角色场景
		proto3::MsgZCEnter imsg;
		pb.Parse(imsg);
		bLogin = true;
		imsg.clear_mid();
		
		APlayerCharacter* pMainPlayer = Cast<APlayerCharacter>(GGameInstance->GetFirstLocalPlayerController()->GetPawn());
		if (pMainPlayer)
		{
			auto SelectPC = Cast<ASelectCharPC>(pMainPlayer->GetController());
			if (SelectPC)
			{
				SelectPC->NetLogin(imsg);
			}
		}

		UE_LOG(LogTemp,Warning,TEXT("--------entered Zone(%s:%d)"),ANSI_TO_TCHAR(sh.address().c_str()),sh.port());
/*
		MsgCZCreatePlayer omsg;
		omsg.set_mid(eMsg::MSG_CZ_CREATE_PLAYER);
		omsg.mutable_playerinfo()->set_name("PlayerName");
		PBHelper::Send(sh,omsg);
		*/
		break;
	}
	case MSG_ZC_ENTER_ARENA:{
		if(GGameInstance&&GGameInstance->pandanet){
			auto& h=GGameInstance->pandanet->clientAConnection.handler;
			auto& imsg=h.EnterArena;
			if(pb.Parse(imsg)){
				UE_LOG(LogTemp,Warning,TEXT("--------Retrieved Arena: aid=%d, host=%s, port=%d, key=%s, level=%s"),
					imsg.aid(),ANSI_TO_TCHAR(imsg.host().c_str()),imsg.port(),ANSI_TO_TCHAR(imsg.key().c_str()),ANSI_TO_TCHAR(imsg.level().c_str()));

				preEnterArena(imsg);
			}
		}
		break;
	}
	default:
		break;
	}
}

void ClientZHandler::preEnterArena(proto3::MsgZCEnterArena& imsg){
	auto& h=GGameInstance->pandanet->clientAConnection.handler;
	if(h.shClient)	h.login();
	else			h.connect();
}

void ClientZHandler::connect(){
	//need connect to Zone
	auto zoneHost		=(const char*)PandaNet::instance().config.value("ZoneHost");
	auto zoneCPort		=(int)PandaNet::instance().config.value("ZoneCPort");
	GGameInstance->pandanet->clientZConnection.connect(zoneHost,zoneCPort);
	UE_LOG(LogTemp,Warning,TEXT("connect to Zone(%s:%d)"),ANSI_TO_TCHAR(zoneHost),zoneCPort);
}

void ClientZHandler::login(){
	auto udid = TCHAR_TO_ANSI(*FPlatformMisc::GetUniqueDeviceId());
	MsgGCLogin& imsg=GGameInstance->pandanet->clientGConnection.handler.msgGCLogin;
	auto& zone=imsg.zoneinfo(0);
	MsgCZEnter msg;
	msg.set_mid(eMsg::MSG_CZ_ENTER);
	msg.set_sid(imsg.sid());
	msg.set_uid(udid);
	PBHelper::Send(*shClient,msg);
	UE_LOG(LogTemp,Warning,TEXT("--------entering Zone(%s:%d)"),ANSI_TO_TCHAR(zone.ip().c_str()),zone.port());
}

#endif //UNREAL_SOCKET