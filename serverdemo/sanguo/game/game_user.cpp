#include "stdafx.h"
#include "game/fwd.h"
#include <time.h>

#ifndef USING_XSMART
#define REG_IF_NOT_EXIST
#endif

using namespace vl;
const int iMax_seat = 2;		//seat num
const int server_version = 20131101;

size_t *id_list;
int ids = 0;

int *table_id_list;
int table_ids = 0;

struct userData **user_list;
size_t user_list_size;
int user_total;

// Free users
struct userData **free_user_list;
size_t free_user_list_size;
int free_user_total;

int tranNum;
int wrongNum;

//pthread_mutex_t user_list_lock = PTHREAD_MUTEX_INITIALIZER;

//pthread_mutex_t table_list_lock = PTHREAD_MUTEX_INITIALIZER;


int init_user()
{
   return 1;
}

int client_conn(size_t client_id)
{
	if (ids >= 500)
    {
        return 0;
    }
    id_list[ids] = client_id;
    ids ++;

	return 1;
}

int client_close(size_t client_id)
{
    int i;
    for (i = 0; i < ids; i ++)
    {
        if (id_list[i] == client_id)
        {
            // Remove it
            if (i < ids - 1)
            {
                memmove(&id_list[i], &id_list[i+1], sizeof(size_t)*(ids-i-1));
            }
            ids --;
        }
    }

	return close_user(client_id);
}

int client_onData(size_t client_id,char *msg,size_t len,MYSQL * mysql)
{
//	debug_info("message of client(%d: %d B)\n",client_id,len);
	auto& pk=*(packet_client_t*)msg;
	short size = pk.length;
//	unsigned int crc32 = pk.crc32;
	short cmd = *(short *)(pk.data);
    if(true)//crc32==CheckPakCRC32(msg+sizeof(short)+sizeof(int),len-sizeof(short)-sizeof(int) ))
    {
        if(len!=size)
        {
			LOG_INFO<<"protocol: packet size wrong,length="<<(int)len<<",size="<<(int)size<<Endl;
            wrongNum=wrongNum+1;
            return -1;
        }
        tranNum = tranNum+1;
		if(cmd>=9000 && cmd<10000)
		{
			handleRecvGameData(client_id,pk.data,len-6,mysql);
		}
        else
			handleRecvData(client_id,pk.data,len-6,mysql);

        return (int)len;
    }
    /*
	else
    {
		LOG_INFO<<"protocol: wrong commang,"<<cmd<<Endl;
        wrongNum=wrongNum+1;
        return -1;
    }
     */
}

void onRecvNetworkData(int game_id,int nSeatIndex,char *msg,size_t len,MYSQL *mysql,short mode)
{
    short signal = *(short *)msg;
    switch(signal)
    {
        case CS_PLAYER_READY:
        {
        }
            break;
    }
}

void handleRecvGameData(size_t client_id,char *msg,size_t len,MYSQL * mysql)
{
	struct userData * user = get_user(client_id);
	if(user->udGameId>=0 && user->seat_id>=0)
	{
		onRecvNetworkData(user->udGameId,user->seat_id,msg,len,mysql,user->udMode);
	}
}


void handleRecvData(size_t client_id,char *msg,size_t len,MYSQL * mysql)
{
    short signal = *(short *)msg;
    switch(signal)
    {
        case CS_SERVERBASE_MODULE_VERSION:
            {
            }
            break;
    }
}

struct userData * get_user(size_t client_id)
{
    struct userData *c = NULL;
	Player* p=Game::instance()->connects().find(client_id);
	if(!p)p=Game::instance()->players().find(client_id);
	if(p)
		c=p->spData.get();
	/*
    if (client_id >= 0 && client_id < user_list_size)
    {
        c = user_list[client_id];
    }
	*/
    return c;
}

int close_user(size_t client_id)
{
    struct userData *c = get_user(client_id);
    if(c)
    {
		c->udGameId = -1;
		c->udMode = -1;
		c->seat_id = -1;
        return free_user(c);
    }
	return 0;
}


int free_user(struct userData *c)
{
    if (!c)
    {
        return -1;//RTN_ERROR_GENERAL;
    }
    auto id = c->client_id;

	auto& gPlayers=Game::instance()->players();
	if(auto p=gPlayers.find(c->user_id)){
		LOG_INFO<<"logout: "<<c->user_id<<","<<c->sUserNick<<Endl;
		gPlayers.remove(c->user_id);
		p->release();
		return 0;
	}
    return 0;//RTN_SUCCESS;
}

