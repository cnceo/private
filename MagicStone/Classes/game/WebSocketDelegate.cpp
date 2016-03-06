// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: WebSocketDelegate
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-8-14
 */
// --------------------------------------------------------
#include "AppFwd.h"

USING_NS_CC;
void WebSocketDelegate::onMessage(WebSocket_t* ws, const WebSocket_t::Data& data){
	auto& pack=*(packet_server_t*)data.bytes;
	short signal=*(short*)(pack.data);
	switch(signal){
	case SC_USERNAME_TO_USERID:
		{
			auto pPak=*(NPAK_SC_USERNAME_TO_USERID*)pack.data;
			auto res=pPak.cResult;
		    //0,成功;1,用户不存在;2,密码错误;3,重复登录
			if(res==0){
				//get user info
				NPAK_CS_USER_LOGIN pk;
				pk.signal=CS_USER_LOGIN;
				pk.iUserID=pPak.iUserID;
				SceneMan::instance()->send(pk);
			}else
				cocos2d::MessageBox("User name or password error!","Error");
		}
		break;
	case SC_ALLUSER_INFO://SC_USER_LOGIN
		{
			auto result=(short*)(pack.data+2);  //user_t
			if(*result++==0){
				//error
			}else{
				CEventDispatch(onLogin,(void*)result);
			}
		}
		break;
    case SC_SELECT_BINNER:
        {
            short signal=CS_PLAYER_CARDINFO;
            SceneMan::instance()->send(signal);
            break;
        }
	case SC_PLAYER_CARDINFO:
		//test enter game
		{
			NPAK_CS_PLAYER_CHANGE pk;
			pk.signal=CS_PLAYER_CHANGE;
			pk.heroID=100;
			pk.Mode=eGame_Training;
			SceneMan::instance()->send(pk);
		}
		break;
	case SC_PLAYER_CHANGE:
		{
			auto pPak=*(NPAK_SC_PLAYER_CHANGE*)pack.data;
			if(pPak.result==1){
				//request a game
				NPAK_CS_JOIN_SEAT pk;
				pk.signal=CS_START_GAME;
				pk.mode=eGame_Training;
				SceneMan::instance()->send(pk);
			}
		}
		break;
	case SC_JOIN_SEAT:
		{
			auto pPak=*(NPAK_SC_JOIN_SEAT*)pack.data;
			if(pPak.seat_id==1){
				///start game
				short signal=CS_PLAYER_READY;
				SceneMan::instance()->send(signal);
			}
		}
		break;
    case SC_PLAYER_READY:
        {
            break;
        }
	case SC_TABLE_DATA:
		{
			GameLogic::instance()->onUpdate(*(NPAK_SC_TABLE_DATA*)pack.data);
		}
		break;
	case SC_GAME_START:
		{
		}
		break;
	case SC_PLAYER_ACTION_START:
		{
            auto& pak=*(NPAK_SC_PLAYER_ACTION_START*)pack.data;
            /*
            if(gameData->GameState==GSTATE_CHANGE)
                pak.action_type = 0;
            else if(gameData->GameState == GSTATE_COMPARE)
                pak.action_type = 1;
            else if(gameData->GameState == GSTATE_HIT)
                pak.action_type = 2;
            else if(gameData->GameState == GSTATE_CA)
                pak.action_type = 3;
            else if(gameData->GameState == GSTATE_EXP)
                pak.action_type = 4;
            else if(gameData->GameState == GSTATE_ITEM)
                pak.action_type = 5;
            */
		}
		break;
    case SC_PLAY_CARD:
        {
            auto pak=(NPAK_SC_PLAY_CARD*)pack.data;
            CEventDispatch(onPlay,(void*)pak);
            //GameLogic::instance()->onPlay(*(NPAK_SC_PLAY_CARD*)pack.data);
        }
        break;
	}
	printf("recv %d: %s\n",(int)data.len,data.bytes);
}

void WebSocketDelegate::onOpen(WebSocket_t* ws){
}

void WebSocketDelegate::onClose(WebSocket_t* ws){
	SceneMan::instance()->standalone(true);
}

void WebSocketDelegate::onError(WebSocket_t* ws, const WebSocket_t::ErrorCode& error){
	SceneMan::instance()->standalone(true);
}
