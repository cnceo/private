#ifndef GAME_USER_H
#define GAME_USER_H                            1

#include "GameDefine.h"
#include <mysql/mysql.h>

struct userData * get_user(size_t);
bool match_Game_New(int user_id,short mode);
int init_user();
void init_ai_handcard(short*,int);

int close_user(size_t);
int free_user(struct userData *);

//void get_user_name(short ,char *);

int client_conn(size_t);
int client_close(size_t);
int client_onData(size_t, char*, size_t,MYSQL *);

void handleRecvData(size_t, char*, size_t,MYSQL *);
void handleRecvGameData(size_t,char *,size_t,MYSQL *);

void registerPlayer(char*,MYSQL*);
void onRecvRegister(size_t,char *,MYSQL *);
void onRecvCardInfo(size_t,char *,MYSQL *);
void addCardsToPlayer(int,int,MYSQL *);
void onRecvGetCard(size_t,char *,MYSQL *);
int getPlayerCardNum(int,MYSQL *);
void onRecvAddCard(size_t,char *,MYSQL *);
void onBeginGame(size_t,char *,MYSQL *);
void onEndGame(size_t,char *,MYSQL *);
void onRecvServerVersion(size_t,char*);
void onRecvPlayerChat(size_t,char*);
void onRecvPlayerChoseHero(size_t,char *,MYSQL *);	// ѡ������
#ifdef CARD_NEW
void InitCheckGardGroup(size_t);					// ������飨���ʺ��õ������ʺŲ��ã�
void LoadCardGroup(size_t);							// װ��ȫ������
void SaveCardGroup(size_t);							// �洢ȫ������
void onRecvPlayerChoseHero_New(size_t,char *);		// ѡ������
void onRecvPlayerUpdateCard_New(size_t,char *);		// ��������
void onRecvGetCard_New(size_t,char *);				// ��ȡ��������
#endif
void onRecvPlayerGetAward(size_t,char *,MYSQL *);
int onCheckCardNum(size_t,MYSQL *);
void onSendMessage(size_t,int);

void onRecvPlayerDoAward(size_t,char *,MYSQL *);
void onRecvQueryUserID(size_t,char*,MYSQL *);
void onRecvUserLogin(size_t,char*,MYSQL *);
void onRecvPlayerUpdateCard(size_t,char *,MYSQL *);	// ��������
void onRecvNewHero(size_t,char *,MYSQL *);
void onRecvPlayerDelHeroCard(size_t,char *,MYSQL *);
void sendUserToOther(size_t,int);
void update_user(size_t ,short ,short ,short);
void sendUserInfo(size_t,short);

void delPlayerToTable(int ,short,short,short );
void update_user_result(SPlayerData*,short);
void update_user_db(size_t,MYSQL *);
void onRecvSearchExchange(size_t ,char * ,MYSQL * );
bool AddScore(size_t client_id , int count);

void onRecvExchangeCard(size_t,char * msg,MYSQL *);
void onRecvDoExchange(size_t,char *,MYSQL *);
void addToPlayerALLCards(int,short,MYSQL *);
int DoExchangeCard(int,short,short,MYSQL *);
void delExchangeCardsToPlayer(int,int,int,MYSQL *);
void onRecvUpdateUserInfo(size_t,char *,MYSQL *);

void onShopOpen(size_t,char *,MYSQL *);
void onShopBuy_New(size_t,char *,MYSQL *);
void onShopSell_New(size_t,char *,MYSQL *);
void onGmCommand(size_t,char *,MYSQL *);
void update_user_state(size_t);
void onDailySignal(size_t,char *,MYSQL *);
void onSelectBeginner(size_t,char *,MYSQL *);
void onSkipBeginner(size_t,char *,MYSQL *);

void onCompetition_In(size_t,char *,MYSQL *);

int  ReadDb_AwardGetCount(size_t);			// ��_��Ҳ��������
void WriteDb_AwardDelCount(size_t,int=1);	// д_��Ҳ����-n
bool WriteDb_AwardAddCount(size_t,int);		// д_��Ҳ����+n

#endif
