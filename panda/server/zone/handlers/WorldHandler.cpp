#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;
using namespace keye;

void WorldHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_ZW_BEGIN||mid>=eMsg::MSG_ZW_END)return;
	switch(mid){
	case MSG_WZ_CONNECT:
	{
		PDLOG<<"connected to World("<<sh.address()<<":"<<sh.port()<<")\n";
	}
	break;
	default:
		break;
	}
}

void WorldHandler::connect(){
	//Arena listen, connect to Zone
	auto worldHost=(const char*)PandaNet::instance().config.value("WorldHost");
	auto worldPort=(int)PandaNet::instance().config.value("WorldZPort");
	Server::instance->worldConnection.connect(worldHost,(unsigned short)worldPort);
	PDLOG<<"connect to world("<<worldHost<<":"<<worldPort<<")"<<endf;
}

void WorldHandler::login(){
	MsgZWConnect msg;
	msg.set_mid(eMsg::MSG_ZW_CONNECT);
	msg.set_zid(100);
	PBHelper::Send(*shClient,msg);
}

