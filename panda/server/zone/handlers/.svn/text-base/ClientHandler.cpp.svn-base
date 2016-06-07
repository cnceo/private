#include "stdafx.h"
#include "ZoneServerFwd.h"

using namespace proto3;

void ClientHandler::on_open(keye::svc_handler& sh){
	PDLOG<<"client connected("<<sh.address()<<")\n";
}

void ClientHandler::on_close(keye::svc_handler& sh){
	auto shid=sh.id();
	auto& mp=Server::instance->clientService._sessions;
	auto i=mp.find(shid);
	if(i!=mp.end()){
		auto& pi=i->second->player;
		Server::instance->players.onLogout(pi.uid().c_str());
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

			if(auto level=Server::instance->levels.findLevelBySh(sh.id()))
				level->BroadcastPlayer(iMsg.playerinfo().uid().c_str());
			//PDLOG<<"client request arena("<<sh.address()<<")\n";
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
			//PDLOG<<"client request arena("<<sh.address()<<")\n";
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
			//PDLOG<<"client request arena("<<sh.address()<<")\n";
		}
		break;
	}
	case MSG_CZ_MOVE:{
		MsgCZMove iMsg;
		if(pb.Parse(iMsg)){
			if(iMsg.to_size()<=0)break;
			//update
			auto p=Server::instance->findClient(sh.id());
			if(p){
				auto& to=*iMsg.to().rbegin();
				auto zid=p->lastplace().zid();
				auto lid=p->lastplace().nmapid();
				p->mutable_lastplace()->CopyFrom(to);
				p->mutable_lastplace()->set_zid(zid);
				p->mutable_lastplace()->set_nmapid(lid);

				//TODO:optimize
				//Server::instance->pandaDB.UpdatePlayer(*p,sh.id());
			}
			//reply
			MsgZCMove msg;
			msg.set_mid(eMsg::MSG_ZC_MOVE);
			msg.set_result(eResult::SUCCEESS);
			PBHelper::Send(sh,msg);
			//PDLOG<<"client request arena("<<sh.address()<<")\n";
			
			if(p)if(auto level=Server::instance->levels.findLevelBySh(sh.id()))
				level->BroadcastPlayer(p->uid().c_str());
		}
		break;
	}
	case MSG_CZ_CHALLENGE_CREATE:{
		MsgCZChallengeCreate iMsg;
		if(pb.Parse(iMsg)){
			if(/*iMsg.challengers_size()>0&&*/iMsg.opposites_size()>0){
				auto ime=Server::instance->findClient(sh.id());
				auto pme=iMsg.add_challengers();
				*pme=ime->uid();
				auto uid0=iMsg.challengers().Get(0);
				if(uid0.empty()&&iMsg.challengers_size()>1)uid0=iMsg.challengers().Get(1);
				auto uid1=iMsg.opposites().Get(0);

				auto& ss=Server::instance->players.sessions;
				auto i=ss.find(uid1);
				if(i!=ss.end()){
					MsgZCChallengeInvite msg;
					msg.set_mid(eMsg::MSG_ZC_CHALLENGE_INVITE);
					msg.mutable_challengers()->CopyFrom(iMsg.challengers());
					msg.mutable_opposites()->CopyFrom(iMsg.opposites());
					PBHelper::Send(*i->second->sh,msg);
					PDLOG<<"challenge create: "<<uid0<<":"<<uid1<<"\n";
					break;
				}
			}
			/*
			MsgZCChallengeStart msg;
			msg.set_mid(eMsg::MSG_ZC_CHALLENGE_START);
			msg.mutable_challengers()->CopyFrom(iMsg.challengers());
			msg.mutable_opposites()->CopyFrom(iMsg.opposites());
			msg.set_result(eResult::ERR_PARAM);
			PBHelper::Send(sh,msg);
			*/
		}
		break;
	}
	case MSG_CZ_CHALLENGE_AGREE:{
		MsgCZChallengeAgree iMsg;
		if(pb.Parse(iMsg)){
			if(iMsg.challengers_size()>0){
				auto& uid0=iMsg.challengers().Get(0);
				auto& uid1=iMsg.opposites();

				auto& ss=Server::instance->players.sessions;
				auto i=ss.find(uid0),j=ss.find(uid1);
				if(i!=ss.end()&&j!=ss.end()&&i!=j){
					MsgZCChallengeStart msg;
					msg.set_mid(eMsg::MSG_ZC_CHALLENGE_START);
					msg.mutable_challengers()->CopyFrom(iMsg.challengers());
					(*msg.add_opposites())=uid1;
					msg.set_result(iMsg.result());

					PBHelper::Send(*i->second->sh,msg);
					PBHelper::Send(*j->second->sh,msg);
					PDLOG<<"challenge start: "<<uid0<<":"<<uid1<<"\n";
				}
			}
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
				msg.mutable_team()->CopyFrom(*ti);
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
				if(auto level=Server::instance->levels.findLevelBySh(sh.id()))
					level->BroadcastMessage(msg,&uids);
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
			auto& ts=Server::instance->teams;
			if(auto team=ts.find(imsg.team().uid().c_str())){
				auto owner=Server::instance->findClient(sh.id());
				auto idx=ts.check(*team,*owner);
				if(idx>0){
					//not leader
				} else{
					idx=ts.check(*team,imsg.targets());
					if(idx>0){
						msg.set_result(eResult::SUCCEESS);
						if(auto level=Server::instance->levels.findLevelBySh(sh.id())){
							//give target null
							if(auto tgt=level->findSession(imsg.targets().uid().c_str()))
								PBHelper::Send(*tgt->sh,msg);

							//broadcast
							team->mutable_members()->DeleteSubrange(idx,1);
							msg.mutable_team()->CopyFrom(*team);
							std::vector<std::string> uids;
							for(auto p:msg.team().members())uids.push_back(p.uid());
							level->BroadcastMessage(msg,&uids);
						}
						PDLOG<<"team kicked. team members: "<<team->members_size()<<"\n";
						break;
					}
				}
			}

			msg.set_result(eResult::FAILED);
			PDLOG<<"team kick, failed.\n";
		} else
			msg.set_result(eResult::ERR_PROTOCOL);
		PBHelper::Send(sh,msg);
		break;
	}
	case MSG_CZ_TEAM_RECRUIT_START:{
		PDLOG<<"team recruit.\n";
		MsgCZTeamRecruitStart imsg;
		if(pb.Parse(imsg)){
			if(imsg.team().members_size()>0){
				auto team=Server::instance->teams.find(imsg.team().uid().c_str());
				if(team){
					PDLOG<<"team recruit, add to recruit list and invite: "<<imsg.targets_size()<<"\n";
					//inviting
					MsgZCTeamRecruitAsk msg;
					msg.set_mid(eMsg::MSG_CZ_TEAM_RECRUIT_ASK);
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
	case MSG_CZ_TEAM_RECRUIT_REPLY:{
		PDLOG<<"team invite.\n";
		MsgCZTeamRecruitReply imsg;
		if(pb.Parse(imsg)){
			MsgZCTeamUpdate msg;
			msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
			msg.set_op(proto3::eTeamOp::INVITE);
			if(proto3::eResult::SUCCEESS==imsg.result()){
				auto& pi=Server::instance->clientService.find(sh.id())->player;
				auto team=Server::instance->teams.join(imsg.team(),pi);
				if(team){
					/*
					//remove from join list
					for(int i=0;i<t->joins_size();++i){
						if(t->joins().Get(i).uid()==pi.uid()){
							t->mutable_joins()->DeleteSubrange(i,1);
							break;
						}
					}
					*/
					PDLOG<<"team recruit, aggreed inviting. team members: "<<team->members_size()<<"\n";
					msg.set_result(eResult::SUCCEESS);
					//broadcast
					std::vector<std::string> uids;
					for(auto p:team->members())uids.push_back(p.uid());
					if(auto level=Server::instance->levels.findLevelBySh(sh.id()))
						level->BroadcastMessage(msg,&uids);

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

	case MSG_CZ_TEAM_JOIN_START:{
		PDLOG<<"team join.\n";
		MsgCZTeamJoinStart imsg;
		if(pb.Parse(imsg)){
			if(auto team=Server::instance->teams.find(imsg.team().uid().c_str())){
				auto& pi=Server::instance->clientService.find(sh.id())->player;
				if(Server::instance->teams.joinable(*team,pi)){
					auto dup=false;
					for(auto& j:team->joins())
						if(j.uid()==pi.uid()){
							//duplicated
							dup=true;
							break;
						}
					//if(dup)break;

					for(auto& j:team->members())
						if(j.uid()==pi.uid()){
							//duplicated
							dup=true;
							break;
						}
					if(dup){
						MsgZCTeamUpdate msg;
						msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
						msg.set_op(proto3::eTeamOp::APPLY);
						msg.set_result(eResult::ERR_DUPLICATED);
						PBHelper::Send(sh,msg);

						break;
					}

					//append to join list
					PDLOG<<"team join, add to join list.\n";
					auto j=team->add_joins();
					j->CopyFrom(pi);
					//find leader and send message
					auto sessions=Server::instance->players.sessions;
					auto i=sessions.find(team->members().Get(0).uid());
					if(i!=sessions.end()){
						PDLOG<<"team join, send request.\n";
						MsgZCTeamJoinAsk msg;
						msg.set_mid(eMsg::MSG_ZC_TEAM_JOIN_ASK);
						msg.mutable_team()->CopyFrom(*team);
						PBHelper::Send(*i->second->sh,msg);
					}
				}
			}
		}
		break;
	}
	case MSG_CZ_TEAM_JOIN_REPLY:{
		PDLOG<<"team apply.\n";
		MsgCZTeamJoinReply imsg;
		if(pb.Parse(imsg)){
			//prepare message
			MsgZCTeamUpdate msg;
			msg.set_mid(eMsg::MSG_ZC_TEAM_UPDATE);
			msg.set_op(proto3::eTeamOp::APPLY);
			msg.set_result(imsg.result());

			auto ok=imsg.result()==proto3::eResult::SUCCEESS;
			//process members:apply or refuse
			auto team=Server::instance->teams.apply(sh.id(),imsg.applicant(),ok);
			if(team){
				//remove from join list
				for(int i=0;i<team->joins_size();++i){
					if(team->joins().Get(i).uid()==imsg.applicant().uid()){
						team->mutable_joins()->DeleteSubrange(i,1);
						break;
					}
				}

				PDLOG<<"team join, applied="<<(ok?"OK":"REFUSE")<<". team members: "<<team->members_size()<<"\n";
				msg.mutable_team()->CopyFrom(*team);

				//broadcast
				std::vector<std::string> uids;
				for(auto p:team->members())uids.push_back(p.uid());
				if(auto level=Server::instance->levels.findLevelBySh(sh.id()))
					level->BroadcastMessage(msg,&uids);

				Server::instance->teams.broadcast();
				break;
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
			PBHelper::Send(sh,msg);	//include empty team for leave member
			
			if(team){
				//broadcast
				msg.mutable_team()->CopyFrom(*team);
				std::vector<std::string> uids;
				for(auto p:team->members())uids.push_back(p.uid());
				if(auto level=Server::instance->levels.findLevelBySh(sh.id()))
					level->BroadcastMessage(msg,&uids);
				break;
			}
			//if(res==proto3::eResult::SUCCEESS)
			Server::instance->teams.broadcast();
		}
		break;
	}
	case MSG_CZ_SYN_ITEM:
	{
		//game_ItemInfo imsg;
		break;
	}
	case MSG_CZ_REMOVE_ITEM:
	{
		game_ItemInfo imsg;
		if (pb.Parse(imsg))
		{
			auto& pi = Server::instance->clientService.find(sh.id())->player;
			Server::instance->pandaItems.removeItem(pi.id(), imsg.itemid());
		}
		break;
	}
	case MSG_CZ_ADD_ITEM:
	{

		break;
	}
	default:
		break;
	}
}
