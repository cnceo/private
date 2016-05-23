#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void GatewayHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_ZG_BEGIN||mid>=eMsg::MSG_ZG_END)return;
	switch(mid){
	case MSG_GZ_CONNECT:
	{
		PDLOG<<"connected to Gateway("<<sh.address()<<":"<<sh.port()<<")\n";
	}
	break;
	default:
		break;
	}
}

void GatewayHandler::connect(){
	auto gatewayHost=(const char*)PandaNet::instance().config.value("GatewayHost");
	auto gatewayPort=(int)PandaNet::instance().config.value("GatewayZPort");
	Server::instance->gatewayConnection.connect(gatewayHost,(unsigned short)gatewayPort);
	PDLOG<<"connect to gateway("<<gatewayHost<<":"<<gatewayPort<<")"<<keye::endf;
}

void GatewayHandler::login(){
	MsgZGConnect msg;
	msg.set_mid(eMsg::MSG_ZG_CONNECT);
	msg.set_zid(100);
	PBHelper::Send(*shClient,msg);
}
