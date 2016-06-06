#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

proto3::TeamInfo* TeamSystem::create(size_t shid,proto3::TeamInfo& ti,proto3::eResult& res){
	auto sess=Server::instance->clientService.find(shid);
	auto& uid=sess->player.uid();
	proto3::TeamInfo* t=find(uid.c_str());
	if(t){
		res=eResult::ERR_DUPLICATED;
		return t;
	}

	if(!ti.title().empty()){
		teams.insert(std::make_pair(uid,ti));
		t=&teams[uid.c_str()];
		t->CopyFrom(ti);
		t->set_uid(uid);	//uid as team id
		if(t->capacity()<=0)t->set_capacity(4);
		if(t->capacity()>4)t->set_capacity(4);
		auto m=t->add_members();
		m->CopyFrom(sess->player);

		broadcast();
		res=eResult::SUCCEESS;
	}else
		res=eResult::ERR_PARAM;
	return t;
}

proto3::TeamInfo* TeamSystem::update(proto3::TeamInfo& ti){
	auto t=find(ti.uid().c_str());
	if(t)t->CopyFrom(ti);
	return t;
}

proto3::TeamInfo* TeamSystem::find(const char* id){
	auto i=teams.find(id);
	return (i==teams.end()?nullptr:&i->second);
}

void TeamSystem::remove(const char* id){
	teams.erase(id);
}

int TeamSystem::check(const proto3::TeamInfo& ti,const proto3::PlayerInfo& pi){
	for(int i=0;i<ti.members_size();++i)
		if(ti.members().Get(i).uid()==pi.uid())
			return i;

	return -1;
}

bool TeamSystem::dismiss(size_t shid,const proto3::TeamInfo& ti){
	auto sess=Server::instance->clientService.find(shid);
	if(sess->player.uid()==ti.uid()){
		remove(ti.uid().c_str());
		return true;
	} else
		return false;
}

bool TeamSystem::joinable(const proto3::TeamInfo& ti,const proto3::PlayerInfo& pi){
	bool ret=pi.level()>=ti.levellimit()&&ti.capacity()>(unsigned)ti.members_size();
	return ret;
}

proto3::TeamInfo* TeamSystem::join(const proto3::TeamInfo& ti,const proto3::PlayerInfo& pi){
	if(auto t=find(ti.uid().c_str())){
		if(joinable(*t,pi)){
			auto p=t->mutable_members()->Add();
			p->CopyFrom(pi);
			return t;
		}
	}
	return nullptr;
}

proto3::TeamInfo* TeamSystem::apply(size_t shid,const proto3::PlayerInfo& pi,bool ok){
	auto& leader=Server::instance->clientService.find(shid)->player;
	if(auto team=find(leader.uid().c_str()))
		return ok?join(*team,pi):team;

	return nullptr;
}

proto3::TeamInfo* TeamSystem::leave(size_t shid,const proto3::TeamInfo& ti,proto3::eResult& res){
	if(auto t=find(ti.uid().c_str())){
		auto sess=Server::instance->clientService.find(shid);
		auto idx=check(*t,sess->player);
		if(idx>=0){
			res=proto3::eResult::SUCCEESS;
			t->mutable_members()->DeleteSubrange(idx,1);
			if(t->members_size()>0){
				//change leader
				if(idx==0){
					auto leaerId=t->members().Get(0).uid();
					t->set_uid(leaerId);
					teams[leaerId]=TeamInfo();
					teams[leaerId].CopyFrom(*t);
					teams.erase(ti.uid());
					t=&teams[leaerId];
				}
				return t;
			} else{
				remove(ti.uid().c_str());
				return nullptr;
			}
		}
	}
	res=proto3::eResult::FAILED;
	return nullptr;
}

void TeamSystem::broadcast(size_t shid){
	MsgZCTeamBroadcast msg;
	msg.set_mid(eMsg::MSG_ZC_TEAM_BROADCAST);
	for(auto& team:teams){
		auto ptr=msg.add_team();
		ptr->CopyFrom(team.second);
	}
	if(shid==0){
		auto& sessions=Server::instance->players.sessions;
		for(auto& ss:sessions){
			PBHelper::Send(*ss.second->sh,msg);
		}
	} else{
		if(auto ss=Server::instance->clientService.find(shid))
			PBHelper::Send(*ss->sh,msg);
	}
}
