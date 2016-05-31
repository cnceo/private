#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void ClientHandler::on_open(keye::svc_handler& sh){
	auto& mp=Server::instance->clientService._sessions;
	auto sid=sh.id();
	auto i=mp.find(sid);
	if(i!=mp.end()){
		auto& pi=i->second->player;
		auto lid=pi.lastplace().nmapid();
		auto level=Server::instance->levels.findLevel(lid);
		if(!level){
			//TODO: init levels from config
			Server::instance->levels.levels.insert(std::make_pair(lid,Level()));
			level=Server::instance->levels.findLevel(lid);
		}
		level->onPlayerEnter(sid);
	}
}

void ClientHandler::on_close(keye::svc_handler& sh){
	auto& mp=Server::instance->clientService._sessions;
	auto sid=sh.id();
	auto i=mp.find(sid);
	if(i!=mp.end()){
		auto& pi=i->second->player;
		auto lid=pi.lastplace().nmapid();
		if(auto level=Server::instance->levels.findLevel(lid))
			level->onPlayerLeave(sid);
	}
}

void ClientHandler::on_message(keye::svc_handler& sh,keye::PacketWrapper& pw){
	PBHelper pb(pw);
	auto mid=pb.Id();
	if(mid<=eMsg::MSG_CZ_BEGIN||mid>=eMsg::MSG_CZ_END)return;
	if(mid==eMsg::MSG_CZ_TEAM_DISMISS)mid=eMsg::MSG_CZ_TEAM_LEAVE;// disable dismiss
	switch(mid){
	case MSG_CZ_ENTER:{
		MsgCZEnter loginMsg;
		if(pb.Parse(loginMsg)){
			/*
			query player info:
				if found, login and broadcast and sync other players
				else return success
			*/
			Server::instance->pandaDB.GetPlayer(loginMsg.uid().c_str(),sh.id());
		}
		break;
	}
	case MSG_CZ_CREATE_PLAYER:{
		//TODO: broadcast
		MsgCZCreatePlayer iMsg;
		if(pb.Parse(iMsg))
			Server::instance->pandaDB.CreatePlayer(iMsg.playerinfo(),sh.id());
		break;
	}
	case MSG_CZ_UPDATE_PLAYER:{
		//TODO: broadcast
		MsgCZUpdatePlayer iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayer msg;
			msg.set_mid(eMsg::MSG_ZC_UPDATE_PLAYER);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);

			Server::instance->clientService.handler.BroadcastPlayer(sh);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_GET_PLAYER_EXTRA:{
		MsgCZGetPlayerExtra iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayerExtra msg;
			msg.set_mid(eMsg::MSG_ZC_UPDATE_PLAYER_EXTRA);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_UPDATE_PLAYER_EXTRA:{
		MsgCZUpdatePlayerExtra iMsg;
		if(pb.Parse(iMsg)){
			MsgZCUpdatePlayerExtra msg;
			msg.set_mid(eMsg::MSG_ZC_UPDATE_PLAYER_EXTRA);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_MOVE:{
		MsgCZMove iMsg;
		if(pb.Parse(iMsg)){
			if(iMsg.to_size()<=0)break;
			//update
			if(auto p=Server::instance->findClient(sh.id())){
				auto& to=*iMsg.to().rbegin();
				p->mutable_lastplace()->set_x(to.x());
				p->mutable_lastplace()->set_y(to.y());
				p->mutable_lastplace()->set_z(to.z());
				p->mutable_lastplace()->set_orientation(to.orientation());

				//TODO:optimize
				Server::instance->pandaDB.UpdatePlayer(*p,sh.id());
			}
			//reply
			MsgZCMove msg;
			msg.set_mid(eMsg::MSG_ZC_MOVE);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";

			BroadcastPlayer(sh);
		}
		break;
	}
	case MSG_CZ_ENTER_ARENA:{
		MsgCZEnterArena iMsg;
		if(pb.Parse(iMsg)){
			//configured Arena address
			auto ArenaHost=(const char*)PandaNet::instance().config.value("ArenaHost");
			auto ArenaPort=(int)PandaNet::instance().config.value("ArenaPort");

			MsgZCEnterArena msg;
			msg.set_mid(eMsg::MSG_ZC_ENTER_ARENA);
			msg.set_aid(iMsg.aid());
			msg.set_host(ArenaHost);
			msg.set_port(ArenaPort);
			msg.set_key(keye::MD5::HashAnsiString("panda"));
			msg.set_level("Scene_MainMap");
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_UPDATE_NAME:{
		MsgCZUpdateName imsg;
		if(pb.Parse(imsg)){
			Server::instance->pandaDB.UpdateUserName(imsg.uid().c_str(),imsg.name().c_str());
			MsgZCUpdateName msg;
			msg.set_mid(eMsg::MSG_ZC_MOVE);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			PDLOG<<"client update name("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_TEAM_EDIT:{
		MsgCZTeamEdit imsg;
		MsgZCTeamUpdate msg;
		msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
		msg.set_op(proto3::eTeamOp::EDIT);
		if(pb.Parse(imsg)){
			if(auto ti=Server::instance->teams.update(*imsg.mutable_team())){
				msg.set_result(eResult::SUCCEESS);
				Server::instance->teams.broadcast();
			}else
				msg.set_result(eResult::FAILED);
		} else
			msg.set_result(eResult::ERR_PROTOCOL);
		PBHelper::Send(sh,msg);
		PDLOG<<"team edit.\n";
		break;
	}
	case MSG_CZ_TEAM_CREATE:{
		MsgCZTeamCreate imsg;
		MsgZCTeamUpdate msg;
		msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
		msg.set_op(proto3::eTeamOp::CREATE);
		if(pb.Parse(imsg)){
			proto3::eResult res;
			if(auto ti=Server::instance->teams.create(sh.id(),*imsg.mutable_team(),res)){
				msg.mutable_team()->CopyFrom(*ti);
				PDLOG<<"team created: "<<msg.team().title().c_str()<<"\n";
			}
			msg.set_result(res);
		} else
			msg.set_result(eResult::ERR_PROTOCOL);
		PBHelper::Send(sh,msg);
		break;
	}
	case MSG_CZ_TEAM_DISMISS:{
		//disable, goto leave
		PDLOG<<"team dismiss.\n";
		MsgCZTeamDismiss imsg;
		MsgZCTeamUpdate msg;
		msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
		msg.set_op(proto3::eTeamOp::DISMISS);
		if(pb.Parse(imsg)){
			if(Server::instance->teams.dismiss(sh.id(),imsg.team())){
				msg.set_result(eResult::SUCCEESS);
				//broadcast
				std::vector<std::string> uids;
				for(auto p:imsg.team().members())uids.push_back(p.uid());
				BroadcastMessage(msg,&uids);
				break;
			} else
				msg.set_result(eResult::FAILED);
		} else{
			msg.set_result(eResult::ERR_PROTOCOL);
		}
		PBHelper::Send(sh,msg);
		break;
	}
	case MSG_CZ_TEAM_KICK:{
		PDLOG<<"team kick.\n";
		MsgCZTeamKick imsg;
		MsgZCTeamUpdate msg;
		msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
		msg.set_op(proto3::eTeamOp::KICK);
		if(pb.Parse(imsg)){
			auto team=Server::instance->teams.kick(sh.id(),imsg.team(),imsg.targets());
			if(team){
				msg.set_result(eResult::SUCCEESS);
				//broadcast
				std::vector<std::string> uids;
				for(auto p:imsg.team().members())uids.push_back(p.uid());
				BroadcastMessage(msg,&uids);
				PDLOG<<"team kicked. team members: "<<team->members_size()<<"\n";
				break;
			} else{
				msg.set_result(eResult::FAILED);
				PDLOG<<"team kick, failed.\n";
			}
		} else
			msg.set_result(eResult::ERR_PROTOCOL);
		PBHelper::Send(sh,msg);
		break;
	}
	case MSG_CZ_TEAM_RECRUIT:{
		PDLOG<<"team recruit.\n";
		MsgCZTeamRecruit imsg;
		if(pb.Parse(imsg)){
			if(imsg.team().members_size()>0){
				auto team=Server::instance->teams.find(imsg.team().uid().c_str());
				if(team){
					PDLOG<<"team recruit, add to recruit list and invite: "<<imsg.targets_size()<<"\n";
					//inviting
					MsgZCTeamInvite msg;
					msg.set_mid(eMsg::MSG_ZC_TEAM_INVITE);
					msg.mutable_team()->CopyFrom(*team);
					for(auto& tgt:imsg.targets()){
						auto& ss=Server::instance->players.sessions;
						auto i=ss.find(tgt.uid());
						if(i!=ss.end()){
							//recruit
							PDLOG<<"team recruit, send inviting.\n";
							PBHelper::Send(*i->second->sh,msg);
						}
					}
					//add to recruit list
					for(auto& r:imsg.targets()){
						auto recr=team->add_recruits();
						recr->CopyFrom(r);
					}
				}
			}
		}
		break;
	}
	case MSG_CZ_TEAM_INVITE:{
		PDLOG<<"team invite.\n";
		MsgCZTeamInvite imsg;
		if(pb.Parse(imsg)){
			MsgZCTeamUpdate msg;
			msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
			msg.set_op(proto3::eTeamOp::INVITE);
			if(proto3::eResult::SUCCEESS==imsg.result()){
				auto& pi=Server::instance->clientService.find(sh.id())->player;
				auto team=Server::instance->teams.join(imsg.team(),pi);
				if(team){
					PDLOG<<"team recruit, aggreed inviting. team members: "<<team->members_size()<<"\n";
					msg.set_result(eResult::SUCCEESS);
					//broadcast
					std::vector<std::string> uids;
					for(auto p:team->members())uids.push_back(p.uid());
					BroadcastMessage(msg,&uids);

					Server::instance->teams.broadcast();
					break;
				}
			} else{
				PDLOG<<"team recruit, refused.\n";
				msg.set_result(eResult::FAILED);
				PBHelper::Send(sh,msg);
			}
		}
		break;
	}

	case MSG_CZ_TEAM_JOIN:{
		PDLOG<<"team join.\n";
		MsgCZTeamJoin imsg;
		if(pb.Parse(imsg)){
			if(auto team=Server::instance->teams.find(imsg.team().uid().c_str())){
				auto& pi=Server::instance->clientService.find(sh.id())->player;
				if(Server::instance->teams.joinable(*team,pi)){
					//append to join list
					PDLOG<<"team join, add to join list.\n";
					auto j=team->add_joins();
					j->CopyFrom(pi);
					//find leader and send message
					auto sessions=Server::instance->players.sessions;
					auto i=sessions.find(team->members().Get(0).uid());
					if(i!=sessions.end()){
						PDLOG<<"team join, send request.\n";
						MsgZCTeamApply msg;
						msg.set_mid(eMsg::MSG_ZC_TEAM_APPLY);
						msg.mutable_team()->CopyFrom(*team);
						PBHelper::Send(*i->second->sh,msg);
					}
				}
			}
		}
		break;
	}
	case MSG_CZ_TEAM_APPLY:{
		PDLOG<<"team apply.\n";
		MsgCZTeamApply imsg;
		if(pb.Parse(imsg)){
			if(imsg.result()==proto3::eResult::SUCCEESS){
				auto team=Server::instance->teams.apply(sh.id(),imsg.applicant());
				if(team){
					PDLOG<<"team join, applied. team members: "<<team->members_size()<<"\n";
					MsgZCTeamUpdate msg;
					msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
					msg.set_op(proto3::eTeamOp::APPLY);
					msg.mutable_team()->CopyFrom(*team);
					msg.set_result(eResult::SUCCEESS);
					//broadcast
					std::vector<std::string> uids;
					for(auto p:team->members())uids.push_back(p.uid());
					BroadcastMessage(msg,&uids);

					Server::instance->teams.broadcast();
					break;
				}
			}
		}
		break;
	}
	
	case MSG_CZ_TEAM_LEAVE:{
		PDLOG<<"team leave.\n";
		MsgCZTeamLeave imsg;
		MsgZCTeamUpdate msg;
		msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
		msg.set_op(proto3::eTeamOp::LEAVE);
		if(pb.Parse(imsg)){
			proto3::eResult res;
			auto team=Server::instance->teams.leave(sh.id(),imsg.team(),res);
			msg.set_result(res);
			if(team){
				PBHelper::Send(sh,msg);

				//broadcast
				msg.mutable_team()->CopyFrom(*team);
				std::vector<std::string> uids;
				for(auto p:team->members())uids.push_back(p.uid());
				BroadcastMessage(msg,&uids);
				break;
			}
			PBHelper::Send(sh,msg);
			//if(res==proto3::eResult::SUCCEESS)
			Server::instance->teams.broadcast();
		}
		break;
	}
	default:
		break;
	}
}

void ClientHandler::SyncPlayers(keye::svc_handler& sh){
	//sync all players to one
	auto& mp=Server::instance->clientService._sessions;
	if(mp.size()>1){
		auto id=sh.id();
		MsgZCSyncPlayers msg;
		msg.set_mid(eMsg::MSG_ZC_SYNC_PLAYERS);
		for(auto& i:mp){
			if(id==i.first)continue;
			auto p=msg.add_players();
			p->CopyFrom(i.second->player);
		}
		PBHelper::Send(sh,msg);
	}
}

void ClientHandler::BroadcastPlayer(keye::svc_handler& sh){
	//broadcast player to others
	auto& mp=Server::instance->clientService._sessions;
	if(mp.size()>1){
		auto id=sh.id();
		MsgZCBroadcastPlayer msg;
		msg.set_mid(eMsg::MSG_ZC_BROADCAST_PLAYER);
		if(auto me=Server::instance->findClient(sh.id()))
			msg.mutable_player()->CopyFrom(*me);

		for(auto& i:mp){
			if(id==i.first)continue;
			auto& shi=*i.second->sh;
			PBHelper::Send(shi,msg);
		}
	}
}

void ClientHandler::BroadcastMessage(::google::protobuf::MessageLite& msg,std::vector<std::string>* uids){
	auto& sessions=Server::instance->players.sessions;
	if(uids)for(auto& uid:*uids){
		//to range
		auto ss=sessions.find(uid.c_str());
		if(ss!=sessions.end())PBHelper::Send(*ss->second->sh,msg);
	} else{
		//to all
		for(auto& i:sessions)
			PBHelper::Send(*i.second->sh,msg);
	}
}
