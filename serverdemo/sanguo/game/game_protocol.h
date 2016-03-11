#ifndef GAME_PROTOCOL_H
#define GAME_PROTOCOL_H                            1

// --------------------------------------------------------------
// protocols 
enum
{
	//ͨ��
	CS_SERVERBASE_MODULE_VERSION=100,
	SC_SERVERBASE_MODULE_VERSION,
	SC_HEART,
	CS_HEART,
	CS_NETWORK_SEND_RECV_TEST,
	SC_NETWORK_SEND_RECV_TEST,

	//
	CS_SEARCH_EXCHANGE=8001,
	SC_SEARCH_EXCHANGE,

	//����
	CS_USERNAME_TO_USERID=17009,
	SC_USERNAME_TO_USERID,
	CS_CREATE_LOGINKEY,
	SC_CREATE_LOGINKEY,
	CS_USER_LOGIN,
	SC_USER_LOGIN,				//see SC_ALLUSER_INFO
	CS_USER_LOGIN_INFO,
	SC_USER_LOGIN_INFO,
	CS_USER_REGISTER,
	SC_USER_REGISTER,
	CS_PLAYER_ALLCARD,			//ȡ��������п���
	SC_PLAYER_ALLCARD,
	CS_PLAYER_ADDCARD,
	SC_PLAYER_ADDCARD,
	CS_PLAYER_CARDINFO,
	SC_PLAYER_CARDINFO,
	CS_PLAYER_UPDATECARD,		//ȷ�ϵ�������
	SC_PLAYER_UPDATECARD,
	CS_PLAYER_NEWHERO,			//��������
	SC_PLAYER_NEWHERO,
	CS_PLAYER_CHANGE,			//ѡ������
	SC_PLAYER_CHANGE,
	CS_PLAYER_DELCARD,
	SC_PLAYER_DELCARD,
	CS_PLAYER_GETAWARD,			//ȡ��ȫ�������
	SC_PLAYER_GETAWARD,
	CS_PLAYER_DOAWARD,			//����
	SC_PLAYER_DOAWARD,
	CS_UPDATE_USERINFO,
	SC_UPDATE_USERINFO,

	CS_GM_COMMAND,
	SC_USER_UPDATE,
	//							�̳�
	CS_SHOP_OPEN,
	SC_SHOP_OPEN,
	CS_SHOP_BUY,
	SC_SHOP_BUY,
	CS_SHOP_SELL,
	SC_SHOP_SELL,
	//
	CS_DAILY_SIGNAL,
	SC_DAILY_SIGNAL,
	CS_SELECT_BINNER,
	SC_SELECT_BINNER,
	//
	SC_SYSTEM_INFO,
	CS_SKIP_BEGINNER,
	//matches
	CS_MATCHES,		//����
	SC_MATCHES,
	CS_MATCH,		//����
	SC_MATCH,
	CS_MATCH_SIGNUP,//����,����
	SC_MATCH_SIGNUP,
	SC_MATCH_NOTIFY,//����֪ͨ

	CS_GAME_CORE_VERSION=7001,
	SC_GAME_CORE_VERSION,
	SC_USER_DATA_LOAD_FROM_DB_OK,
	SC_USER_LOGIN_FROM_ANOTHER_CLIENT,
	CS_MY_TABLE_INFO_QUERY,
	SC_MY_TABLE_INFO,
	CS_JOIN_NEXT_TABLE,
	CS_USER_JOIN_TABLE,
	CS_USER_LEAVE_TABLE,
	SC_USER_JOIN_OR_LEAVE_TABLE,			// �û�������뿪�����ӻ���ͬ���ϻ�λ��
	CS_SEAT_USER_INFO_QUERY,
	SC_SEAT_USER_INFO,
	CS_CLIENT_INIT_DATA_QUERY_END,
	SC_CLIENT_INIT_DATA_QUERY_END,
	CS_GAME_PING,
	SC_GAME_PING,
	SC_EVENT_NOTIFY_TEXT,					// (�ڲ��ı���̬����)
	CS_ASSIGN_LOGIN_SERVER,
	SC_ASSIGN_LOGIN_SERVER,
	CS_DBWORK_NETWORK_COMMAND,
	SC_DBWORK_NETWORK_COMMAND,
	SERVERBASEEX_BASE_SIGNAL_END,

	CS_ALLSEAT_INFO=7400,
	SC_ALLSEAT_INFO,
	CS_START_GAME,
	CS_END_GEME,
	SC_JOIN_SEAT,
	SC_LEAVE_SEAT,
	SC_ALLUSER_INFO,
	SC_USER_STATE,
	CS_REPLACING_FACE,
	SC_REPLACING_FACE,
	SC_SEAT_STATE,
	SC_TABLE_STATE,
	CS_GM_MESSAGE,
	SC_GM_MESSAGE,
	SC_SERVER_NAME,
	SC_TS_MESSAGE,
	SC_LOCK_MESSAGE,
	CS_PLAYER_QUIT,
	CS_PLAYER_CHAT=7418,
	SC_PLAYER_CHAT,
	CS_QUICK_PLAY,
	SC_QUICK_PLAY,
	CS_ALL_RANK,
	SC_ALL_RANK,
	CS_EXCHANGE_CARD=7424,
	SC_EXCHANGE_CARD,
	CS_DO_EXCHANGE,
	SC_DO_EXCHANGE,

	//����
	CS_MY_SEAT_INDEX_QUERY=9001,
	SC_MY_SEAT_INIT,
	CS_GAME_WORLD_TDATA_QUERY,
	SC_TABLE_DATA,						// data for game
	CS_PLAYER_READY,					//����ս��,�ȴ����
	SC_PLAYER_READY,
	SC_PLAYER_READY_BAULK,
	CS_PLAY_CARD,
	SC_PLAY_CARD,
	CS_LOOT_LOAD,
	SC_LOOT_LOAD,
	SC_TABLE_DATA_CHANGED_NOTIFY,
	SC_GAME_OVER,
	SC_GAME_WAIT,
	SC_GAME_START,
	SC_COMPARE_SHOW,
	SC_MY_NOTIFY_TEXT,
	SC_PLAYER_ACTION_START,
	SC_DAMAGE,
	CS_PLAY_END,
	CS_SKILL_IFACTION,
	SC_SKILL_IFACTION,
	CS_SKILL_ACTION=9023,
	SC_SKILL_ACTION=9024,
	SC_SKILL_ACTION_OVER,
	SC_SKILL_EFFECT,
	CS_GAME_CHAT,
	SC_GAME_CHAT,
	SC_GAME_COMPARE,
	SC_GAME_AWARDS,						// awards data for game
	
	// == add by TYT at 2014-2-7 ���� begin == 
	CS_COMPETITION_IN					= 10001,	// ����������ĳһ����
	SC_COMPETITION_IN					= 10002,	// ��������Ӧ�������
	SC_COMPETITION_BEGIN				= 10103,	// ������ץ��ҽ���ս��
	SC_COMPETITION_BROADCAST_MAIN		= 10120,	// ս����Ϣͬ��_�ִ���
	SC_COMPETITION_BROADCAST_PAIR		= 10121,	// ս����Ϣͬ��_�����Ϣ
	SC_COMPETITION_BROADCAST_USER		= 10122,	// ս����Ϣͬ��_ʤ����Ϣ	
	SC_COMPETITION_BROADCAST_RANK		= 10123,	// ս����Ϣͬ��_���������Ϣ	
	// == add by TYT at 2014-2-7 ���� end == 
};

// --------------------------------------------------------------
// protocol packet structures
#pragma pack(1)

struct packet_server_t{
	short	length;		//within this short
	char	data[0];	//signal+data
};

struct packet_client_t{
	short	length;		//within this short
	int		crc32;		//crc for server
	char	data[0];	//signal+data
};

struct NPAK_BASE	// Network Packet Base
{
	short signal;	// Network Signal
};

struct NPAK_SC_TABLE_STATE
{
    short signal;
    short nTableIndex;
    short nTableLevel;
    short nPlayerNum;
    short nTableStatus;
};

struct NPAK_CS_UPDATE_USERINFO
{
	short signal;
};

struct NPAK_SC_UPDATE_USERINFO
{
	short signal;
	int32 score;
	int win;
	int lose;
};

struct NPAK_CS_EXCHANGE_CARD
{
	short signal;
	short cardID;
	short needCardID;
};

struct NPAK_SC_EXCHANGE_CARD
{
	short signal;
	short result;
};

struct NPAK_CS_DO_EXCHANGE
{
	short signal;
	short id;
	short type;
};

struct NPAK_SC_DO_EXCHANGE
{
	short signal;
	short result;
};


struct NPAK_CS_QUICK_PLAY
{
	short signal;
};

struct NPAK_SC_QUICK_PLAY
{
	short signal;
	short result;
};

struct NPAK_CS_SERVERBASE_MODULE_VERSION
{
	short signal;
	int	iVersion;
};

struct NPAK_SC_SERVERBASE_MODULE_VERSION
{
	short signal;
	short cResult;
};

struct NPAK_CS_USERNAME_TO_USERID
{
	short signal;
	char sUsername[64];
	char sPswd[33];
};

struct NPAK_SC_USERNAME_TO_USERID
{
	short signal;
	short cResult;	//0,�ɹ�;1,�û�������;2,�������;3,�ظ���¼
	int iUserID;
	int ServerTime;//������ʱ��		1970����ʱ��ʼ�Ǻ�����
};

struct NPAK_CS_CREATE_LOGINKEY
{
	short signal;
	int iUserID;
	char sPassWord[64];
};

struct NPAK_SC_CREATE_LOGINKEY
{
	short signal;
	short cResult;
	int iLoginKey;
};

struct NPAK_CS_USER_LOGIN
{
	short signal;
	int iUserID;
//	char sPassWord[64];
};

struct NPAK_SC_USER_LOGIN
{
	short signal;
	short cResult;
};

struct NPAK_CS_JOIN_SEAT
{
	short signal;
	short mode;
};

struct NPAK_SC_JOIN_SEAT
{
	short signal;
//	short	client_id;
	int		user_id;
	short	table_id;//table
	short	seat_id;//seat
	char	sUserNick[64];
	short	face_id;
	int32	user_money;
	int32	user_rank;
	int32	user_score;
	short level;
	short status;//0 - player,1 - observer
	short mode;
};

struct NPAK_SC_TABLE_DATA
{
	short signal;
	short	sGameID;
	short	sCurrentTurnPlayer;  // ��ǰ�ֵ�˭��
	int		sTurnTimeRest;		// ��ǰ��ʣ��ʱ��(����)
	char	sLastCardsPlayer;	// �ϴ���˭����
	char	GameState;
	char	GameResultStatus;   //0-����,������,1-��;��Ӯ��!
	short   sGameLevel;//game level
	short   sCompareWinPlayer;
	short   priorityPlayer;
	short	IsContinue;
	struct SPlayerDataPak m_PlayerData[2];
};

struct NPAK_SC_GAME_AWARDS{
	struct awards_t{
		int		uid;		//user id
		char	boosters,	//booster packs
				stars,
				rank,		//rank for match
				placeholder;
		short	money,
				score,
				TaskWinCount,		// ������й���
				ContinueWinNum,		// ��ʤ����
				ContinueWinScore,	// ��ʤ��������
				ContinueWinBag;		// ��ʤ�����������
	};
	short		signal;
	char		type,		//game type:0,normal;1,training;2,match
				winner,		//the winner
				continous,	//0,end normal;1,continue for match
				end_reason;	//��Ϸ����ԭ��
	awards_t	awards[2];
};

struct NPAK_SC_PLAYER_ACTION_START
{
	short	signal;
	short	nSeatIndex;
	short	action_type;
};

struct NPAK_SC_MY_NOTIFY_TEXT
{
	short signal;
	char content[128];
};

struct NPAK_SC_PLAYER_READY_BAULK
{
	short signal;
	short nSeatIndex;
};

struct NPAK_CS_PLAY_CARD
{
	short signal;
	short action_id;
	short cardPos;
	short ifChangeCard;
};

struct NPAK_SC_PLAY_CARD
{
	short	signal;
	short	nError;
	short	nSeatIndex;
	short   cardPos;
	short	cardValue;
	short   action_id;
	short   ifChangeCard;
};

struct NPAK_SC_GAME_OVER
{
	short signal;
	struct SGameData GameData;
};

struct NPAK_SC_PLAYER_READY
{
	short	signal;
	short	nSeatIndex;
};

struct NPAK_SC_LEAVE_SEAT
{
	short signal;
	short nTableIndex;
	short nTableLevel;
	short nSeatIndex;
};

struct NPAK_SC_USER_STATE
{
	short signal;
	short state;
//	short	client_id;
	int		user_id;
	short	league_id;//player's league id
	short	table_id;//table
	short	seat_id;//seat
	char	sUserNick[64];
	int32	user_win;
	int32	user_lose;
	short	face_id;
	int32	user_money;
	int32	user_rank;
	int32	user_score;
	int		sHero;
};

struct NPAK_SC_DAMAGE
{
	short signal;
	short nTarget;
	short nDamage;
	short nCardID;
};

struct NPAK_CS_PLAY_END
{
	short signal;
};

struct NPAK_CS_USER_REGISTER
{
	short signal;
	unsigned int userID;
	short heroID;
	char username[64];
};

struct NPAK_SC_USER_REGISTER
{
	short signal;
	short result;
	char username[64];
};

struct NPAK_CS_PLAYER_ALLCARD
{
	short signal;
};

struct NPAK_CS_PLAYER_ADDCARD
{
	short signal;
	short heroID;
};

struct NPAK_SC_PLAYER_ADDCARD
{
	short signal;
	short result;
};

struct NPAK_CS_PLAYER_CHANGE
{
	short signal;
	short heroID;
	short Mode;		//eMatch
};

struct NPAK_SC_PLAYER_CHANGE
{
	short signal;
	short result;
};

struct NPAK_CS_PLAYER_DELCARD
{
	short signal;
	short serialID;
};

struct NPAK_SC_PLAYER_DELCARD
{
	short signal;
	short serialID;
};

struct NPAK_CS_PLAYER_NEWHERO
{
	short signal;
	short heroID;
};

struct NPAK_SC_PLAYER_NEWHERO
{
	short signal;
	short result;
};

struct NPAK_CS_SKILL_IFACTION
{
	short signal;
	short result;
};

struct NPAK_SC_SKILL_IFACTION
{
	short signal;
	short nSeatIndex;
	int iId;
};

struct NPAK_CS_SKILL_ACTION
{
	short signal;
	short action;
	int cardPos[5];
};

struct NPAK_SC_SKILL_ACTION
{
	short signal;
	short nSeatIndex;
	short id;
	short action;
	short ifflg;
	short cardNum;
	short cardID[MAX_CARD];
};

struct NPAK_SC_SKILL_ACTION_OVER
{
	short signal;
	short nSeatIndex;
	short action;
	short ifSuccess;
	short cardID[5];
};

struct NPAK_SC_SKILL_EFFECT
{
	short signal;
	short nSeatIndex;
	short skillid;
	short effect;
	short value;// 1-������Ϊvalue  2-����+value 3-����*value 4-�ٶȱ�Ϊvalue 5-�ٶ�+value 6-��Ŀ�����value���˺� 7-��һ���ƹ���+value 8-���������˺�����+value 9-����3���˺��ٶ�+value
};

struct NPAK_SC_GAME_CHAT
{
	short signal;
	short nSeatIndex;
	char msg[256];
};

struct NPAK_CS_GAME_CHAT
{
	short signal;
	char msg[256];
};

struct NPAK_SC_PLAYER_CHAT
{
	short signal;
	int user_id;
	char msg[256];
};

struct NPAK_CS_PLAYER_CHAT
{
	short signal;
	char msg[256];
};

struct NPAK_SC_INFO
{
	short	signal,
			flag,
			len;
	char	msg[0];
};

struct NPAK_SC_TS_MESSAGE
{
	short signal;
	short error_id;
};

struct NPAK_SC_PLAYER_GETAWARD
{
	short signal;
	short num;
};

struct NPAK_SC_PLAYER_DOAWARD
{
	short signal;
	int cardArr[8];
};

struct NPAK_CS_SEARCH_EXCHANGE
{
	short signal;
	short page;
};

struct NPAK_SC_GAME_COMPARE
{
	short signal;
	short speed_0;
	short batimin_0;
	short batimax_0;
	short speed_1;
	short batimin_1;
	short batimax_1;
};

struct NPAK_CS_SHOP_BUY{
	short signal;
	short shop_id;
	short count;
};

struct NPAK_SC_SHOP_BUY{
	short signal;
	short result;	//0:���,1:no enough money,2:shop_id error,3:no enough items,4:other errors��5����,6:total
	int money,jade;
};

struct NPAK_SC_DAILY_SIGNAL{
	short signal;
	short result;
	int   data;
};

// == add by TYT at 2014-2-7 ���� begin == 
struct NPAK_CS_COMPETITION_IN
{
	short	signal;
	int		Type;		//��������

};

struct NPAK_SC_COMPETITION_IN
{
	short	signal;
	int		IsOk;		//����ͨ����	1ͨ��,0ûͨ��	
	int		Type;		//��������	

};

struct NPAK_SC_COMPETITION_BEGIN
{
	short	signal;
	int		Type;		//��������	
};

struct NPAK_SC_COMPETITION_BROADCAST_MAIN
{
	short	signal;
	int		RoundNum;	//����				
	int		Time;		//ʱ��		1900����ʱ��ʼ�Ǻ�����	
};

struct match_pairs{
	enum	{MAX_NAME=16};
//	char	Type;		//���		0���,1�ֿ�(ֻ�����A)	
	unsigned char	group,		//���		1,ʤ����;0,������
					score;		//�ȷ�		s2|s1<<4
	int		P1_ID;		//���A_ID	�ֿ�idΪ0		
	int		P2_ID;		//���A_ID			
	char	P1_Name[MAX_NAME];//���A_Name			
	char	P2_Name[MAX_NAME];//���B_Name
};

struct NPAK_SC_COMPETITION_BROADCAST_PAIR
{
	short		signal;
	short		RoundNum;	//����
	short		PairsNum;
	match_pairs	Pairs[0];
};

struct NPAK_SC_COMPETITION_BROADCAST_USER
{
	short	signal;
	int		RoundNum;	//����
	int		P1_ID;		//���-ʤ	
	int		P2_ID;		//���-��
};
struct NPAK_SC_COMPETITION_BROADCAST_RANK{
	struct rank_t{
		int		uid,
				rank;
		char	name[16];
	};
	short		signal;
	short		count;
	rank_t		ranks[0];
};
// == add by TYT at 2014-2-7 ���� end == 

struct NPAK_SC_MATCHES{
	struct	mids_t{unsigned char type_id,info_id;};
	short	signal,
			len;
	mids_t	mids[0];
};

struct NPAK_CS_MATCH{
	short	signal,
			type_id;
};

struct NPAK_CS_MATCH_SIGNUP{
	short	signal,
			match_id,
			action,
			deck;
};

struct NPAK_SC_MATCH_SIGNUP{
	short	signal,
			match_id,
			result;
};

struct NPAK_SC_MATCH_NOTIFY{
	short	signal,
			match_id;
};

#pragma pack()

int GetString(int,char *,char *,unsigned char);//���String
int GetShort(int,short *,char *);//���short
int SetShort(int,short,char *);//����short
int SetString(int,char *,char *,unsigned char);//����string

#endif
