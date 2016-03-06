// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: GameMan
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------

#include "AppFwd.h"

USING_NS_CC;
// --------------------------------------------------------
INSTANCE_IMP(SceneMan)
SceneMan::SceneMan()
:_socket(nullptr)
,_standalone(false){
}

SceneMan::~SceneMan(){
	if(_socket)_socket->close();
}

Scene* SceneMan::init(){
	//custom events
	CEventSetup(SceneMan,onConnectErr);
	CEventSetup(SceneMan,onConnectClose);
	CEventSetup(SceneMan,doLogin);
	connect(nullptr);

	SceneMan::instance()->registry(UI_LOGIN,SceneMan::SceneFunc(UILogin::scene));
	SceneMan::instance()->registry(UI_GAME,SceneMan::SceneFunc(UIGame::scene));
	return UILogin::scene(.3f);
}

void SceneMan::registry(int id,SceneFunc f){
	auto i=_scenes.find(id);
	if(i==_scenes.end()){
		//create TransitionScene
/*
		auto ts=f(1.f/3.f);	//1/3 sec
		ts->retain();
		//registry
		std::pair<SceneFunc,TransitionScene*> p(f,ts);
*/
		std::pair<SceneFunc,TransitionScene*> p(f,nullptr);
		_scenes.insert(std::make_pair(id,p));
	}
}

bool SceneMan::transition(int id){
	auto i=_scenes.find(id);
	if(i!=_scenes.end()){
/*
		if(auto scene=i->second.second){
		   Director::getInstance()->replaceScene(scene);
		   return true;
		}
*/
		auto& f=i->second.first;
		auto ts=f(1.f/5.f);	//1/3 sec
		ts->retain();
		Director::getInstance()->replaceScene(ts);
		return true;
	}
	return false;
}

bool SceneMan::standalone()const{
	return _standalone;
}

void SceneMan::standalone(bool b){
	_standalone=b;
}

bool SceneMan::connect(const char* ws){
	if(!_socketDelegate)
		_socketDelegate.reset(new WebSocketDelegate);

	//	const char* host="http://192.168.28.244:7778";
//	const char* msg="aaaaa";
//	ws="192.168.0.230:23454";
	ws="127.0.0.1:23454";
	if(!_socket){
		_socket=new WebSocket_t();
		std::vector<std::string> protocols;
		protocols.push_back("keye-websocket");
//		protocols.push_back("http-only");
		auto ret=_socket->init(*_socketDelegate.get(),ws,&protocols);
		if(!ret)
			return false;
	}
	return true;
}

void SceneMan::send(void* raw,int len){
	//send raw data by wsocket
	if(_socket&&raw&&len>0){
		static char buf[2048];
		auto& pack=*(packet_client_t*)buf;
		memcpy(pack.data,raw,len);
		pack.crc32=0;
		pack.length=sizeof(pack)+len;
		_socket->send((const unsigned char*)buf,pack.length);
	}
}

user_t& SceneMan::userInfo(){
	if(!_user)_user.reset(new user_t);
	return *_user;
}

void SceneMan::createUser(user_t* u){
	_user.reset();
	memcpy(&userInfo(),u,sizeof(*u));
	//test get decks
	if(standalone()){
		game_t pak;
		memset(&pak,0,sizeof(pak));
		pak.sGameID=1;
		pak.GameState=GSTATE_CHANGE;
		for(int k=0;k<MAX_PLAYER;++k){
			memset((void *)&pak.m_PlayerData[k],0,sizeof(struct SPlayerDataPak));
			if(0==k){
				pak.m_PlayerData[k].user_id = u->user_id;
				strcpy(pak.m_PlayerData[k].szUserNick,u->sUserNick);
			}else{
				pak.m_PlayerData[k].user_id = -1;
				strcpy(pak.m_PlayerData[k].szUserNick,"autobot");
			}
			pak.m_PlayerData[k].cardNum = INIT_HAND_CARD;
			memcpy(pak.m_PlayerData[k].HandCards,u->sCards,INIT_HAND_CARD*sizeof(short));
			pak.m_PlayerData[k].StoreCards=INIT_HAND_CARD;
		}
		GameLogic::instance()->onUpdate(pak);
    }else if(u->user_flag<9){
        struct NPAK_CS_PLAYER_NEWHERO pak;
        pak.signal=CS_SELECT_BINNER;
        pak.heroID=0;   //[0-5]
        this->send(pak);
    }else{
		short signal=CS_PLAYER_CARDINFO;
		this->send(signal);
	}
}

void SceneMan::onConnectErr(cocos2d::EventCustom* e){
	standalone(true);
}

void SceneMan::onConnectClose(cocos2d::EventCustom* e){
	standalone(true);
}

void SceneMan::doLogin(cocos2d::EventCustom* e){
	if(standalone()){
		user_t u;
		memset(&u,0,sizeof(u));
		u.user_id=100111;
		strcpy(u.sUserNick,"test1111");
		for(int i=0;i<INIT_HAND_CARD;++i)
			u.sCards[i]=CARD_ID_TRAIN_BEGIN+i;

		CEventDispatch(onLogin,(void*)&u);
	}else{
//		auto name=static_cast<const char*>(e->getUserData());
		NPAK_CS_USERNAME_TO_USERID pk;
		pk.signal=CS_USERNAME_TO_USERID;
		strcpy(pk.sUsername,"test1111");
		strcpy(pk.sPswd,"e10adc3949ba59abbe56e057f20f883e");	//123456
		this->send(pk);
	}
}
// --------------------------------------------------------
