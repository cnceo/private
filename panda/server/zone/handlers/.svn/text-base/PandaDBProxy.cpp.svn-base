// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace keye;
using namespace proto3;
using namespace std;

PandaDBProxy::PandaDBProxy(){
	_db="panda";
}

void PandaDBProxy::handle(int qid,DBResult* res,void* privdata){
	PDLOG<<"query result qid="<<qid<<"\n";

	switch((eQid)qid){
	case GET_PLAYER:{
		auto param=(std::map<size_t,const void*>*)privdata;
		auto shid=param->begin()->first;
		auto uid=(const char*)param->begin()->second;
		auto ss=Server::instance->clientService.find(shid);
		if(ss){
			MsgZCEnter msg;

			auto result=res->type;
			if(result==DBResult::Type::REPLY_ARRAY&&res->arr.size()>0){
				//found players
				auto& data=res->arr;
				auto pi=msg.mutable_playerinfo()->Add();
				parsePlayerInfo(*pi,data);
				msg.set_activeplayer(0);

				//store player info
				Server::instance->players.onLogin(*pi,ss);
				PDLOG<<"retrieved player: "<<pi->uid()<<"\n";
			} else// if(result==DBResult::Type::REPLY_NIL)
			{
				//no players
				//test
				proto3::PlayerInfo pi;
				pi.set_uid(uid);
				pi.set_name("kongfu");
				CreatePlayer(pi,shid);
			}

			//reply: found or no players
			msg.set_mid(eMsg::MSG_ZC_ENTER);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(*ss->sh,msg);

			PDLOG<<"client entered("<<ss->sh->address()<<")\n";
		}
		break;
	}
	case CREATE_PLAYER:{
		auto param=(std::map<size_t,const PlayerInfo*>*)privdata;
		auto shid=param->begin()->first;
		auto pi=param->begin()->second;
		auto ss=Server::instance->clientService.find(shid);
		if(ss){
			auto result=res->type;
			if(result==DBResult::Type::REPLY_ERROR){

			} else{
				//store player info
				Server::instance->players.onLogin(*pi,ss);
				PDLOG<<"created player: "<<pi->uid()<<"\n";
			}
			MsgZCCreatePlayer msg;
			msg.set_mid(eMsg::MSG_ZC_CREATE_PLAYER);
			msg.mutable_playerinfo()->CopyFrom(*pi);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(*ss->sh,msg);
		}
		break;
	}
	case UPDATE_PLAYER:{
		auto result=res->type;
		break;
	}
	case REMOVE_PLAYER:{
		auto result=res->type;
		break;
	}
	case UPDATE_NAME:{
		auto result=res->type;
		break;
	}
	default:break;
	}
}

void PandaDBProxy::GetPlayer(const char* uid,size_t shid){
	auto qid=eQid::GET_PLAYER;
	auto table="player";
	char cmdR[256];
	char cmdM[256];
	//query client version to decide user exists
	sprintf(cmdR,"HGETALL %s",DBProxy::key(_db.c_str(),table,uid,"0").c_str());
	sprintf(cmdM,"SELECT * FROM %s WHERE account='%s';",table,uid);

	std::map<size_t,const void*> privdata;
	privdata[shid]=uid;
	DBProxy::instance().exec(cmdR,cmdM,qid,(void*)&privdata);
}

void PandaDBProxy::CreatePlayer(const proto3::PlayerInfo& pi,size_t shid){
	auto ss=Server::instance->clientService.find(shid);
	if(ss){
		auto uid=pi.uid().c_str();
		auto qid=eQid::CREATE_PLAYER;
		auto table="player";
		char cmdR[256];
		char cmdM[256];
		char id[2];
		sprintf(id,"%d",pi.id());
		sprintf(cmdR,"HMSET %s uid %s level %d exp %d",DBProxy::key(_db.c_str(),table,uid,id).c_str(),uid,pi.level(),pi.exp());
		if(!pi.name().empty())sprintf(cmdR,"%s name %s",cmdR,pi.name().c_str());
		sprintf(cmdM,"INSERT INTO %s(account,pid,name,level,exp) VALUES('%s',%d,'%s',%d,%d);",
			table,uid,pi.id(),pi.name().c_str(),pi.level(),pi.exp());

		std::map<size_t,const PlayerInfo*> privdata;
		privdata[shid]=&pi;
		DBProxy::instance().exec(cmdR,cmdM,qid,(void*)&privdata);
	}
}

void PandaDBProxy::UpdatePlayer(const proto3::PlayerInfo& pi,size_t shid){
	auto ss=Server::instance->clientService.find(shid);
	if(ss){
		auto uid=pi.uid().c_str();
		auto qid=eQid::UPDATE_PLAYER;
		auto table="player";
		char cmdR[256];
		char cmdM[256];
		char id[2];
		sprintf(id,"%d",pi.id());
		sprintf(cmdR,"HMSET %s level %d exp %d",DBProxy::key(_db.c_str(),table,uid,id).c_str(),pi.level(),pi.exp());
		if(true)sprintf(cmdR,"%s zid %d px %d py %d pz %d orientation %d",cmdR,pi.lastplace().zid(),(int)pi.lastplace().x(),(int)pi.lastplace().y(),(int)pi.lastplace().z(),pi.lastplace().orientation());
		if(!pi.name().empty())sprintf(cmdR,"%s name %s",cmdR,pi.name().c_str());
		sprintf(cmdM,"UPDATE %s SET name='%s' level=%d exp=%d",table,pi.name().c_str(),pi.level(),pi.exp());
		sprintf(cmdM,"%s zid=%d px=%d py=%d pz=%d orientation=%d",cmdM,pi.lastplace().zid(),(int)pi.lastplace().x(),(int)pi.lastplace().y(),(int)pi.lastplace().z(),pi.lastplace().orientation());
		sprintf(cmdM,"%s WHERE account='%s' AND id=%d;",cmdM,uid,pi.id());

		std::map<size_t,const PlayerInfo*> privdata;
		privdata[shid]=&pi;
		DBProxy::instance().exec(cmdR,cmdM,qid,(void*)&privdata);
	}
}
void PandaDBProxy::RemovePlayer(int pid,const char* uid,size_t shid){
	auto qid=eQid::REMOVE_PLAYER;
	auto table="player";
	char cmdR[256];
	char cmdM[256];
	char id[2];
	sprintf(id,"%d",pid);
	sprintf(cmdR,"DEL %s",DBProxy::key(_db.c_str(),table,uid,id).c_str());
	sprintf(cmdM,"DELETE FROM '%s' WHERE account='%s' AND id=%d;",table,uid,pid);

	std::map<size_t,int> privdata;
	privdata[shid]=pid;
	DBProxy::instance().exec(cmdR,cmdM,qid,(void*)&privdata);
}

void PandaDBProxy::UpdateUserName(const char* uid,const char* name){
	auto qid=eQid::UPDATE_NAME;
	string _table("account");
	char cmdR[256];
	char cmdM[256];
	//query client version to decide user exists
	sprintf(cmdR,"HSET %s name %s",DBProxy::key(_db.c_str(),_table.c_str(),uid).c_str(),name);
	sprintf(cmdM,"UPDATE %s SET name='%s' WHERE id='%s';",_table.c_str(),name,uid);
	DBProxy::instance().exec(cmdR,cmdM,qid,nullptr);
}

void PandaDBProxy::parsePlayerInfo(proto3::PlayerInfo& pi,const std::vector<DBResult>& res){
	for(size_t i=0,ii=res.size();i<ii;){
		auto& k=res[i].str;
		auto v=res[i+1].str.c_str();
		if(k=="id"){
			pi.set_id(atoi(v));
		} else if(k=="uid"){
			pi.set_uid(v);
		} else if(k=="name"){
			pi.set_name(v);
		} else if(k=="level"){
			pi.set_level(atoi(v));
		} else if(k=="exp"){
			pi.set_exp(atoi(v));
		} else if(k=="zid"){
			pi.mutable_lastplace()->set_zid(atoi(v));
		} else if(k=="px"){
			pi.mutable_lastplace()->set_x((float)atoi(v));
		} else if(k=="py"){
			pi.mutable_lastplace()->set_y((float)atoi(v));
		} else if(k=="pz"){
			pi.mutable_lastplace()->set_z((float)atoi(v));
		} else if(k=="orientation"){
			pi.mutable_lastplace()->set_orientation(atoi(v));
		}
		i+=2;
	}
}
