#ifndef GAME_DEFINE_H
#define GAME_DEFINE_H                            1


#pragma pack(1)

#define MAX_NOTIFY_TEXT_50		50
#define TURN_TIME_DELAY			2000 // 秒
#define ACTION_TIME_DELAY_FOR_OFFLINE	3*1000
#define iActionTime	1500

#define MAX_PLAYER				2
#define MAX_CARD				40	//套牌最大数量
#define INIT_HAND_CARD			5	//手牌的初始数量
#define MAX_HAND_CARD			10	//手牌的最大数量
#define CARDID_NULL				0
#define CARDID_BACK				666	// 'B' 牌背
#define CARDID_TRANSPARENT		888	// 'T' 透明牌,用于占位
/* 牌库格式
	{[1001:short][n:short],[1002:short][n:short],...[1203:short][n:short]}
	共支持202张牌,每张牌2个short,共808字节 */
#define CARDS_SIZE				(404*sizeof(short))	//牌库尺寸

#define GAME_LIST_INITIAL		500	//多少局？
#define CARD_LIST_INITIAL		300 //多少张卡牌？
#define HERO_LIST_INITIAL		30 //多少个英雄？
#define SKILL_LIST_INITIAL      200

#define CARD_ID_BEGIN			1001
#define CARD_ID_END				1129
#define CARD_ID_TRAIN_BEGIN		1121
#define CARD_ID_TRAIN_END		1129

// --------------------------------------------------------------
// Game global
// --------------------------------------------------------------
enum eGameGlobal:int{
	//game
	MAX_GAME_TRAINING		=500,
	MAX_GAME_NORMAL			=1000,
	MAX_GAME_PAY			=500,
	MAX_GAME_MATCH_MON		=1000,

	GAME_TIMEOUT_ACTION		=5*60,
	GAME_TIMEOUT_NORMAL		=10*60,	//SEC
	GAME_TIMEOUT_MATCH_MON	=10*60,

	MAX_TRAINING_LEVEL		=5,
	//timer
	FRAME_TIMER_ID	=119,
	HALF_HOUR_TIMER_ID,
	HOUR_TIMER_ID,
	MINUTE_TIMER_ID,

	FRAME_INTERVAL	=1,			//游戏帧率,秒
	HOUR_INTERVAL	=60*60,		//1小时
	MINUTE_INTERVAL	=60*1,		//1分钟
};

typedef int int32;

enum eMatch:unsigned short{
	eGame_Training	= 0,// 训练模式(PVE)
	eGame_Normal,		// 一般对战
	eGame_Pay,			// 付费对战
	eGame_Month,		// 月赛
	eGame_Match		=100,// 比赛起始
	eGame_Max		=999,
};
#define CompetitionCheckTime 300

enum GAMESTATE
{
	GSTATE_WAITING = 0,
	GSTATE_CHANGE,//换牌阶段1
	GSTATE_COMPARE,//比拼牌2
	GSTATE_HIT,//连击牌3
	GSTATE_CA,//反击4
	GSTATE_EXP,//经验阶段5
	GSTATE_ITEM,//装备牌6
	GSTATE_OVER,
	GSTATE_RESULTING,
	GSTATE_COMPARE_SKILL, //比拼技能结算阶段
	GSTATE_COMPARE_DAMAGE,
	GSTATE_COMPARE_RESULT,
	GSTATE_COMPARE_RESULT_SKILL,
	GSTATE_HIT_SKILL,
	GSTATE_HIT_DAMAGE,
	GSTATE_CA_SKILL,
	GSTATE_CA_DAMAGE,
	GSTATE_START,//回合开始阶段,要看一下有没有技能的触发
	GSTATE_START_SKILL,//回合开始阶段后,去看看技能的情况,18
	GSTATE_OVER_SKILL,//回合结束技能阶段
	GSTATE_END,	//真正显示结果,从GSTATE_RESULTING来

	GSTATE_END_DISCONNECT,
	GSTATE_END_DAMAGE,
	GSTATE_END_SKILL_DAMAGE,
	GSTATE_END_NO_CARD,

	GSTATE_END_OUTTIME,
};

enum GAMERESULT
{
	GRESULT_WIN  =  1,//赢了
	GRESULT_DRAW =  0,//平局
	GRESULT_LOSE = -1,//失败
	GRESULT_FLEE = -2,//逃跑
	GRESULT_GLOW = -3,//爆了
	GRESULT_SURRENDER = -4,//投降
	GRESULT_NULL=-5,
};


struct sCardSkill
{
	int skillid;//技能ID
	int skilltype;//技能类型 0-加攻击 1-加速度 2-摸牌 3-加治疗 4-加buff 5-展示牌库顶牌 6-造成伤害 7-获得经验 8-霸体
	int target; //技能的对象,0-自己,1-对手
	int value; //
	int valuetype; //伤害类型
	int othervalue; //
	int skilltime;//0-任意阶段 1-开始阶段  2-摸牌阶段  3-比拼阶段  4-连技阶段
};

struct sHero
{
	int		iId;
	short	cClass;// 10-暗夜使者 20-鬼剑士 30-圣职者 40-魔法师 50-格斗家 60-神枪手
	short	cSubclass;// 11-刺客  21-狂战士  31-圣骑士 41-魔道学者 51-街霸 61-枪炮师
	short	shieldtype;// 0-轻甲 1-布甲 2-皮甲 3-重甲 4-板甲
	int		life;
	short	level;
	short	exp;
	short   lowSkill;//觉醒前的技能
	short   highSkill;//觉醒后的技能
};

struct sCard
{
	int		iId;
	short	type;// 0-勇士牌 1-攻击牌 2-装备牌 9-刮刮卡
	short   Rarity;
	short	speed;
	short	damage;
	short	skill;//技能ID
	short	batiMin;
	short	batiMax;
	short	color;
	short	exp;
	short	energy;//打出后产生的费用
	short	cost_0;
	short	cost_1;
	short	cost_2;
	short	cost_3;
	short	cost_4;
	short	cost_5;
	char	name[32];
};

struct sSkill
{
	int iId;
	short skilltime;
	short method;
	short effect;
	short action;
	short effecttype;
	short value;
	short condition;
	short conditionvalue;
	short ifask;
	char  name[32];
	char  des[256];
};

struct sStocks
{
	int	itemId;		//#物品ID(0牌包不用此字段，卡牌与卡牌表一样)
	int	itemType;	//#物品种类(0，牌包；1，卡牌）
	int	count;		//#物品数量（一次购买物品的叠加数量）
	int	BuyType;	//#买-货币类型(0，金币。1，玉)
	int	BuyCost;	//#买-物品价格(9位)
	int	SellType;	//#卖-货币类型(0，金币。1，玉)
	int	Sellcost;	//#卖-物品价格(9位)
};

struct sHeroData
{
	int		iId;
	short	cClass;// 10-暗夜使者 20-鬼剑士 30-圣职者 40-魔法师 50-格斗家 60-神枪手
	short	cSubclass;// 11-刺客  21-狂战士  31-圣骑士 41-魔道学者 51-街霸 61-枪炮师
	short	shieldtype;// 0-轻甲 1-布甲 2-皮甲 3-重甲 4-板甲
	int		life;
	short	level;
	int		StoreCards[MAX_CARD];//手牌,这个用来初始化的
};

struct sBuff
{
//	short attackPlus;//当前要加的攻击力
	short attackmultiply;//d当前要乘的攻击力
	short ifattackchange;//当前是否要改变攻击数值
	short attackvalue;//当前要改变数值的结果

	short speedPlus;//当前要加的速度
	short ifspeedchange;//当前是否要改变速度
	short speedvalue;//当前要改变速度的值

	short nextattackplus[MAX_CARD];

	short TurnAttackPlus;//本回合加攻击力

	short batimax;
	short batimin;
	int   must;//必须出的牌
	short   last;//必须出的牌

	short other[MAX_CARD];//一些其他类型BUFF

};

struct SGameData
{
	//game playing data
	int		mode;					//eMatch
	short	sGame_id;
	short	sCurrentTurnPlayer;		// 当前轮到谁了
	short	turn;					// 当前是第几回合
	int		sTurnTimeRest;			// 当前轮剩余时间(毫秒)
	short	sLastCardsPlayer;		// 上次的比拼是谁赢的,注意,是比拼！！
	char	GameState;				//游戏的阶段
	short	GameResultStatus;		//比拼结果如何,是不是打平了？ 0 - 有胜负 1 - 打平	
	short	playerNum;				// 几个人了
	short   sGameLevel;				//game level
	struct	SPlayerData *m_PlayerData[MAX_PLAYER];
	short	sCompareWinPlayer;		//比拼是那个玩家赢了？
	int		sCheckDelay;			//下一次判断需要延迟多少时间？
	short	byReadyUserCount;		//已经准备的玩家数量
	short	end_reason;				//游戏结束原因
	short	sSkillQueue[MAX_CARD];	//这个是技能的队列,初始都是-1,然后如果是有技能,那么就是座位ID,0或者1,先进先出！！！
	short   priorityPlayer;			//比拼前,看看谁具有优先权（速度低的有优先权）	
	short	IsContinue;
	int		RadyWaitTime;
};

struct SPlayerData
{
	//playing data of one player
	size_t	client_id;
	int		user_id;
	short	table_id;//table
	short	seat_id;//seat
	char	szUserNick[64];
	short	sFaceID;
	short	sFlag;
	int32	nScore;
	int32	nMoney;
	int32	nRank;
	short 	sWaitingTotalTime;
	short	byReadyForGame;	//是否准备
	short	byCardPass;		//停牌,不出了!
	short	byActionOverFlag;	//行动完毕,0-no action,1-跟注,2-加注,3-CHECK,4-弃牌, 5 - bet
	short	heroID;
	short	heroLife;//英雄的初始血量
	short	heroLifeLeft;//英雄剩余的血量
	short	cardNum;//手牌的数量
	short	energy_0;//经验值无色费用
	short	energy_1;//经验值白色费用
	short	energy_2;//经验值蓝色费用
	short	energy_3;//经验值黑色费用
	short	energy_4;//经验值红色费用
	short	energy_5;//经验值绿色费用
	short	lastHitSpeed;//上一张连击牌的实际速度
	short	    HandCards[MAX_CARD]; // 手牌
	short		TableCards[MAX_CARD]; // 已经打出的牌,包括比拼牌,在桌面上的,每个回合之后就进入经验区
	short		StoreCards[MAX_CARD]; // 自己的牌库里面的牌
	short		initialCards[MAX_CARD]; // 初始的牌
	short		ExpCards[MAX_CARD];//经验区
	short		DisCards[MAX_CARD];//弃牌区
	short		SkillQueue[MAX_CARD];//这个是技能队列,是技能的ID！先进先出
	short		RuneCards[MAX_CARD];
//	short		WeaponCard;//武器装备区
//	short		ShieldCard;//防具装备

	short   ifcure;//之前收到过多少治疗
	short   iffold;//之前弃过多少牌
	short   ifdeal;//之前抓过多少牌
	short   ifPoisoning;//是否中毒 0-未中毒,1-中毒
	short   ifpaylife;//支付过多少生命

	short 	sBet;	//用来标示英雄是否觉醒了,0-没有觉醒,1-觉醒了
	short	sWaitingActionTime;//玩家没有操作次数
	short	nCoverCharge;	//服务费
	short	winResult;		//
	short   winMoney;      //
	short   lastAction;    //上一次的行动,action
	struct sBuff *buff;
};

struct SPlayerDataPak //这个是用来发包用的,因为splayerdata太大了！！
{
//	short	client_id;
	int		user_id;
	short	table_id;//table
	short	seat_id;//seat
	char	szUserNick[64];
	short	sFaceID;
	short	sFlag;
	int32	nScore;
	int32	nMoney;
	int32	nRank;
	short 	sWaitingTotalTime;
	short	byReadyForGame;	//是否准备
	short	byCardPass;		//停牌,不出了!
	short	byActionOverFlag;	//行动完毕,0-no action,1-跟注,2-加注,3-CHECK,4-弃牌, 5 - bet
	short	heroID;
	short	heroLife;//英雄的初始血量
	short	heroLifeLeft;//英雄剩余的血量
	short	cardNum;//手牌的数量
	short	energy_0;//经验值
	short	energy_1;//经验值
	short	energy_2;//经验值
	short	energy_3;//经验值
	short	energy_4;//经验值
	short	energy_5;//经验值
	short	HandCards[20]; // 手牌
	short	TableCards[20]; // 已经打出的牌,包括比拼牌,在桌面上的,每个回合之后就进入经验区
	short	StoreCards; // 自己的牌库里面的牌
	short	ExpCards[20];//经验区
	short	DisCards[20];//弃牌区
	short	RuneCards[10];
//	short	WeaponCard;//武器装备区
//	short	ShieldCard;//防具装备
	short 	sBet;	//用来标示英雄是否觉醒了,0-没有觉醒,1-觉醒了
	short	sWaitingActionTime;//玩家没有操作次数
	short	nCoverCharge;	//服务费
	short	winResult;		//
	short   winMoney;      //
	short   lastAction;    //上一次的行动,action
	short   ifPoisoning;//是否中毒 0-未中毒,1-中毒
};

//#define CARD_NEW 
#ifdef CARD_NEW
#define HeroCount 6
static int HeroId[HeroCount] = {100,101,102,103,104,105};
#endif

struct userData
{
	//user info,related to database
	//SC_ALLUSER_INFO,SC_USER_UPDATE uses
	int		user_id;
	short	league_id;//player's league id
	short	udMode;
	short	udGameId;
	short	seat_id;//seat
	char	sUserNick[64];
	char	leaguename[64];
	int32	user_win;
	int32	user_lose;
	short	face_id;
	int32	user_money;
	int32	user_jade;
	int32	task_win;
	int32	out_time;
	short	ContinueWinNum;
	int32	user_rank;
	int32	user_score;
	int		sHero;
	short	sCards[MAX_CARD];
	short	user_flag;	//0-MAX_TRAINING_LEVEL,training;8,normal;9,gm account
	short	signal_flag;//daily signal flag:0,not signaled;1,signaled;
	size_t	client_id;	//must at end'cause of the size_t
};
inline int szUserData(){return sizeof(userData)-sizeof(size_t);}

struct user_base_t{
	int		user_id;
	short	face_id;
	char	nick_name[32];
	int32	user_win;
	int32	user_lose;
	int32	user_money;
	int32	user_rank;
	int32	user_score;
};

struct task_t{
	int				user_id;
	unsigned char	contionu;	//连胜模式下已胜场次
	unsigned char	tasks[7];	//正在进行的任务
};

#pragma pack()

// instance macro
#ifndef INSTANCE_DECL
	#define INSTANCE_DECL(T) \
		public: \
			static T*		instance(); \
			static void		close_instance(); \
		private: \
			static T*		_instance;	// don't use shared_ptr
#endif //INSTANCE_DECL
#ifndef INSTANCE_IMP
	#define INSTANCE_IMP(T) \
		T* T::_instance=nullptr; \
		T* T::instance() \
		{ \
			if(nullptr==_instance) \
				_instance=new T; \
			return _instance; \
		} \
		void T::close_instance() \
		{ \
			if(nullptr!=_instance) \
				delete _instance; \
			_instance=nullptr; \
		};
#endif //INSTANCE_IMP

#endif
