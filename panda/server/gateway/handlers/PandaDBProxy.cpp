// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GatewayServerFwd.h"

using namespace keye;
using namespace proto3;

void PandaDBProxy::handle(int qid,DBResult* res,void* privdata){
	PDLOG<<"query result qid="<<qid<<"\n";
	switch((eQid)qid){
	case CREATE_ACCOUNT:{
		auto param=(std::map<size_t,const MsgCGLogin*>*)privdata;
		auto shid=param->begin()->first;
		auto& info=*param->begin()->second;

		auto result=eResult::SUCCEESS;
		if(res->type==DBResult::REPLY_NONE||res->type==DBResult::REPLY_ERROR)
			result=eResult::FAILED;

		replyClientLogin(info,shid,result);
		break;
	}
	case GET_ACCOUNT:{
		auto param=(std::map<size_t,const MsgCGLogin*>*)privdata;
		auto shid=param->begin()->first;
		auto& info=*param->begin()->second;
/*
		int version=0;
		if(res->type==DBResult::REPLY_INTEGER)
			version=(int)res->value;
		else if(res->type==DBResult::REPLY_STRING)
			version=atoi(res->str.c_str());

		if(version>0)
			//find user
			replyClientLogin(info,shid);
		else
			//new user
			CreateUser(info,shid);
*/
		std::string version;
		if(res->type==DBResult::REPLY_STRING)
			version=res->str;

		if(!version.empty()){
			//find user
			((MsgCGLogin*)&info)->set_name(version);
			replyClientLogin(info,shid);
		} else
			//new user
			CreateUser(info,shid);
		break;
	}
	default:break;
	}
}

void PandaDBProxy::replyClientLogin(const MsgCGLogin& info,size_t shid,eResult result){
	if(auto sess=Server::instance->clientService.find(shid)){
		MsgGCLogin msg;
		msg.set_mid(eMsg::MSG_GC_LOGIN);
		if(result!=eResult::SUCCEESS)
			msg.set_result(result);
		else{
			msg.set_result(eResult::SUCCEESS);
			msg.set_sid(shid);
			msg.set_version(100);
			msg.set_name(info.name());
			auto zi=msg.add_zoneinfo();
			zi->set_id(100);
			zi->set_version(100);
			zi->set_ip("192.168.0.107");
			zi->set_port(8820);
			zi->set_occupied(0);
			zi->set_capacity(2000);
		}
		PBHelper::Send(*sess->sh,msg);
		PDLOG<<"get account "<<info.id()<<":"<<info.udid()<<endl;
	}
}

void PandaDBProxy::CreateUser(const MsgCGLogin& info,size_t shid){
	auto qid=eQid::CREATE_ACCOUNT;
	auto db="panda",
		table="account",
		field="id";
	char cmdR[256];
	char cmdM[256];
	auto uid=info.id().c_str();
	//query client version to decide user exists
	sprintf(cmdR,"HMSET %s id %s type %d client_version %d",DBProxy::key(db,table,uid).c_str(),uid,info.type(),info.clientversion());
	if(!info.account().empty())sprintf(cmdR,"%s account %s",cmdR,info.account().c_str());
	if(!info.udid().empty())sprintf(cmdR,"%s udid %s",cmdR,info.udid().c_str());
	if(!info.name().empty()&&info.name().find(' ')==std::string::npos)sprintf(cmdR,"%s name %s",cmdR,info.name().c_str());

	sprintf(cmdM,"INSERT INTO %s(id,type,udid,account,name,client_version) VALUES('%s',%d,'%s','%s','%s',%d);",table,
		uid,info.type(),info.udid().c_str(),info.account().c_str(),info.name().c_str(),info.clientversion());

	std::map<size_t,const MsgCGLogin*> privdata;
	privdata[shid]=&info;
	DBProxy::instance().exec(cmdR,cmdM,qid,(void*)&privdata);
}

void PandaDBProxy::QueryUser(const MsgCGLogin& info,size_t shid){
	auto qid=eQid::GET_ACCOUNT;
	auto db="panda",
		table="account",
		verField="name";
	char cmdR[128];
	char cmdM[128];
	auto uid=info.id().c_str();
	//query client version to decide user exists
	sprintf(cmdR,"HGET %s %s",DBProxy::key(db,table,uid).c_str(),verField);
	sprintf(cmdM,"SELECT %s FROM %s WHERE id='%s';",verField,table,uid);

	std::map<size_t,const MsgCGLogin*> privdata;
	privdata[shid]=&info;
	DBProxy::instance().exec(cmdR,cmdM,qid,(void*)&privdata);
}