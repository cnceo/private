// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "Networking/NetworkingFwd.h"

#ifndef UNREAL_SOCKET
using namespace proto3;

// Arena service for Client
void ArenaCHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CA_BEGIN||mid>=eMsg::MSG_CA_END)return;
	switch(mid){
	case eMsg::MSG_CA_ENTER:
	{
		MsgACEnter msgEnter;
		msgEnter.set_mid(eMsg::MSG_AC_ENTER);
		msgEnter.set_result(eResult::SUCCEESS);
		PBHelper::Send(sh,msgEnter);
		UE_LOG(LogTemp,Warning,TEXT("--------client(%s) entered"),ANSI_TO_TCHAR(sh.address().c_str()));
		break;
	}
	default:
		break;
	}
}
#endif //UNREAL_SOCKET