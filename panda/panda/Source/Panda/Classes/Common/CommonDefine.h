//  CommonDefine.h
//  Created by yang 公共数据定义

#pragma once
#include "EngineMinimal.h"
#include "CommonDefine.generated.h"

//手柄键盘定义
enum class PLAYER_KEY:uint8
{
	PLAYER_KEY_NONE = 0,
	PLAYER_KEY_QUAN = 1,
	PLAYER_KEY_CHA = 2,
	PLAYER_KEY_FANGKUAI = 3,
	PLAYER_KEY_SANJIAO = 4,
	PLAYER_KEY_L1 = 5,
	PLAYER_KEY_R1 = 6,
	PLAYER_KEY_L2 = 7,
	PLAYER_KEY_R2 = 8,
	PLAYER_KEY_SHANG = 9,
	PLAYER_KEY_XIA = 10,
	PLAYER_KEY_ZUO = 11,
	PLAYER_KEY_YOU = 12,

	PLAYER_KEY_MAX,
};

//角色状态定义(带动作的,同时只能存在一个)
UENUM(BlueprintType)
enum class CHARACTER_STATE:uint8
{
	//默认
	CHARACTER_STATE_NONE = 0		UMETA(DisplayName = "STATE_NONE"),	
	//待机
	CHARACTER_STATE_NORMAL	= 1		UMETA(DisplayName = "STATE_NORMAL"),
	//站立
	CHARACTER_STATE_STAND = 2		UMETA(DisplayName = "STATE_STAND"),
	//行动
	CHARACTER_STATE_ACTION	 = 3		UMETA(DisplayName = "STATE_ACTION"),
	//跳跃与下落
	CHARACTER_STATE_FALLING = 4	UMETA(DisplayName = "STATE_FALLING"),
	//放技能
	CHARACTER_STATE_SKILL = 5		UMETA(DisplayName = "STATE_SKILL"),
	//被攻击(被命中)
	CHARACTER_STATE_BEHIT = 6		UMETA(DisplayName = "STATE_BEHIT"),
	//死亡
	CHARACTER_STATE_DIE = 7		UMETA(DisplayName = "STATE_DIE"),


	CHARACTER_STATE_MAX = 255,
};

//角色子状态定义(CHARACTER_STATE的从属关系)
UENUM(BlueprintType)
enum class CHARACTER_SUB_STATE :uint8
{
	//默认
	SUB_STATE_NONE = 0			UMETA(DisplayName = "None"),
	//普通待机
	SUB_STATE_NORMAL = 1			UMETA(DisplayName = "DAIJI_NORMAL"),
	//战斗待机
	SUB_STATE_FIGHTING = 2			UMETA(DisplayName = "DAIJI_FIGHTING"),

	//**************站立状态子状态*********************
	//摆造型
	SUB_STATE_POSE1 = 3			UMETA(DisplayName = "ZHANLI_POSE1"),
	//摆造型
	SUB_STATE_POSE2 = 4			UMETA(DisplayName = "ZHANLI_POSE2"),
	//摆造型
	SUB_STATE_POSE3 = 5			UMETA(DisplayName = "ZHANLI_POSE3"),
	//摆造型
	SUB_STATE_POSE4 = 6			UMETA(DisplayName = "ZHANLI_POSE4"),
	//摆造型
	SUB_STATE_POSE5 = 7			UMETA(DisplayName = "ZHANLI_POSE5"),
	//摆造型
	SUB_STATE_POSE6 = 8			UMETA(DisplayName = "ZHANLI_POSE6"),
	//胜利表情
	SUB_STATE_WIN = 9				UMETA(DisplayName = "ZHANLI_WIN"),
	//失败表情
	SUB_STATE_LOSE = 10			UMETA(DisplayName = "ZHANLI_LOSE"),
	//尴尬表情
	SUB_STATE_AWKWARD = 11			UMETA(DisplayName = "ZHANLI_AWKWARD"),
	//挑衅表情
	SUB_STATE_TAUNT = 12			UMETA(DisplayName = "ZHANLI_TAUNT"),
	//卖萌表情
	SUB_STATE_LOVELY = 13			UMETA(DisplayName = "ZHANLI_LOVELY"),
	//打招呼表情
	SUB_STATE_HELLO = 14			UMETA(DisplayName = "ZHANLI_HELLO"),
	//拾取物品
	SUB_STATE_PICK = 15			UMETA(DisplayName = "ZHANLI_PICK"),
	//喝东西
	SUB_STATE_DRINK = 16			UMETA(DisplayName = "ZHANLI_DRINK"),

	//**************行动状态子状态*********************
	//行走
	SUB_STATE_MOVE = 21				UMETA(DisplayName = "XINGDONG_MOVE"),
	//防御
	SUB_STATE_DEFENCE = 22				UMETA(DisplayName = "XINGDONG_DEFENCE"),
	//闪避
	SUB_STATE_DODGE = 23				UMETA(DisplayName = "XINGDONG_DODGE"),
	//锁定目标闪避
	SUB_STATE_DODGE_TARGET = 24		UMETA(DisplayName = "XINGDONG_DODGE_TARGET"),
	//倒地打滚闪避
	SUB_STATE_TUMBLE_DODGE = 25		UMETA(DisplayName = "XINGDONG_TUMBLE_DODGE"),

	//**************跳跃与下落子状态*********************
	//跳跃
	SUB_STATE_JUMP = 41			UMETA(DisplayName = "FALLING_JUMP"),
	//二段跳跃
	SUB_STATE_JUMP2 = 42			UMETA(DisplayName = "FALLING_JUMP2"),
	//自由下落状态
	SUB_STATE_FALL = 43			UMETA(DisplayName = "FALLING_FALL"),
	//着地状态
	SUB_STATE_LAND = 44			UMETA(DisplayName = "FALLING_LAND"),

	//**************技能状态子状态*********************
	//命中原子
	SUB_STATE_HIT = 61			UMETA(DisplayName = "JINENG_HIT"),
	//追击原子
	SUB_STATE_CHASE = 62			UMETA(DisplayName = "JINENG_CHASE"),
	//引导原子
	SUB_STATE_GUIDE = 63			UMETA(DisplayName = "JINENG_GUIDE"),

	//**************死亡状态子状态*********************
	//普通死亡	
	SUB_STATE_DIE_NORMAL = 81			UMETA(DisplayName = "SIWANG_DIE_NORMAL"),

	//被击倒后死亡	
	SUB_STATE_DIE_FLOOR = 82			UMETA(DisplayName = "SIWANG_DIE_FLOOR"),

	//死亡被击飞	
	SUB_STATE_DIE_FLY = 90				UMETA(DisplayName = "SIWANG_DIE_FLY"),

	//**************被击状态子状态*********************
	//被攻击(挨打1)
	SUB_STATE_BEHIT1 = 121				UMETA(DisplayName = "BEIJI_BEHIT1"),
	//被攻击(挨打2)
	SUB_STATE_BEHIT2 = 122				UMETA(DisplayName = "BEIJI_BEHIT2"),
	//趔趄1
	SUB_STATE_REEL1 = 125				UMETA(DisplayName = "BEIJI_REEL1"),
	//被击倒(倒地)
	SUB_STATE_TUMBLE = 126				UMETA(DisplayName = "BEIJI_TUMBLE"),
	//倒地起身
	SUB_STATE_GETUP	= 127			UMETA(DisplayName = "BEIJI_GETUP"),
	//眩晕
	SUB_STATE_DIZZY	= 128			UMETA(DisplayName = "BEIJI_DIZZY"),
	//被重击
	SUB_STATE_BEHEAVY = 129			UMETA(DisplayName = "BEIJI_BEHEAVY"),
	//被重击后起身
	SUB_STATE_BEHEAVY_GETUP = 130		UMETA(DisplayName = "BEIJI_BEHEAVY_GETUP"),
	//趔趄2
	SUB_STATE_REEL2 = 131				UMETA(DisplayName = "BEIJI_REEL2"),
	//趔趄3
	SUB_STATE_REEL3 = 132				UMETA(DisplayName = "BEIJI_REEL3"),
	//被击倒后立刻起身
	SUB_STATE_GETUP_QUICK =133			UMETA(DisplayName = "BEIJI_GETUP_QUICK"),
	//倒地被击1
	SUB_STATE_TUMBLE_HIT1 = 134		UMETA(DisplayName = "BEIJI_TUMBLE_HIT1"),
	//倒地被击2
	SUB_STATE_TUMBLE_HIT2 = 135		UMETA(DisplayName = "BEIJI_TUMBLE_HIT2"),
	//被击飞到空中
	SUB_STATE_BEHITFLY = 151			UMETA(DisplayName = "BEIJI_BEHITFLY"),
	//被击飞在空中漂浮
	SUB_STATE_HITFLY_FLOATING = 152		UMETA(DisplayName = "BEIJI_HITFLY_FLOATING"),
	//被击飞开始下落
	SUB_STATE_HITFLY_FALLING = 153		UMETA(DisplayName = "BEIJI_HITFLY_FALLING"),
	//被击飞漂浮后着陆
	SUB_STATE_HITFLY_LAND = 154		UMETA(DisplayName = "BEIJI_HITFLY_LAND"),
	//空中被攻击(挨打1)
	SUB_STATE_FLY_BEHIT1 = 155			UMETA(DisplayName = "BEIJI_FLY_BEHIT1"),
	//空中被攻击(挨打2)
	SUB_STATE_FLY_BEHIT2 = 156			UMETA(DisplayName = "BEIJI_FLY_BEHIT2"),
	//空中被击落(快速下落)
	SUB_STATE_FLY_HITFALL = 157		UMETA(DisplayName = "BEIJI_FLY_HITFALL"),
	//空中被击落倒地后打滚
	SUB_STATE_FLY_HITROLL = 158		UMETA(DisplayName = "BEIJI_FLY_HITROLL"),

	SUB_STATE_MAX = 255,
};

//角色增益减易状态定义(无实际动作,可同时存在多个)
UENUM(BlueprintType)
enum class CHARACTER_BUFF:uint8
{
	CHARACTER_BUFF_NONE		UMETA(DisplayName = "None"),		//默认 = 0
	CHARACTER_BUFF_DIZZY		UMETA(DisplayName = "XuanYun"),		//眩晕 = 1

	CHARACTER_BUFF_MAX,
};

//角色阵营(同时只能存在一个)
UENUM(BlueprintType)
enum class CHARACTER_CAMP:uint8
{
	CHARACTER_CAMP_NONE		UMETA(DisplayName = "None"),		//默认
	CHARACTER_CAMP_PLAYER		UMETA(DisplayName = "WanJia"),		//玩家
	CHARACTER_CAMP_ENEMY		UMETA(DisplayName = "DiRen"),		//玩家的敌人
	CHARACTER_CAMP_FRIEND		UMETA(DisplayName = "YouFang"),		//玩家的友方

	CHARACTER_CAMP_MAX,
};

//角色类型
UENUM(BlueprintType)
enum class CHARACTER_TYPE :uint8
{
	//默认
	CHARACTER_TYPE_NONE		UMETA(DisplayName = "CHARACTER_TYPE_NONE"),
	//玩家
	CHARACTER_TYPE_PLAYER		UMETA(DisplayName = "CHARACTER_TYPE_PLAYER"),
	//小怪
	CHARACTER_TYPE_MONSTER		UMETA(DisplayName = "CHARACTER_TYPE_MONSTER"),
	//精英
	CHARACTER_TYPE_ELITE		UMETA(DisplayName = "CHARACTER_TYPE_ELITE"),
	//BOSS
	CHARACTER_TYPE_BOSS		UMETA(DisplayName = "CHARACTER_TYPE_BOSS"),
	//伙伴
	CHARACTER_TYPE_PARTNER		UMETA(DisplayName = "CHARACTER_TYPE_PARTNER"),

	CHARACTER_TYPE_MAX,
};

//角色攻击碰撞点类型
UENUM(BlueprintType)
enum class CHARACTER_COLLISION_TYPE:uint8
{
	//无
	COLLISION_NONE = 0		UMETA(DisplayName = "None"),
	//左手
	COLLISION_HAND_L = 1 		UMETA(DisplayName = "ZuoShou"),
	//右手
	COLLISION_HAND_R = 2		UMETA(DisplayName = "YouShou"),
	//左脚
	COLLISION_FOOT_L = 3		UMETA(DisplayName = "ZuoJiao"),
	//右脚
	COLLISION_FOOT_R = 4		UMETA(DisplayName = "YouJiao"),
	//肚子
	COLLISION_BELLY	= 5		UMETA(DisplayName = "DuZi"),
	//屁股
	COLLISION_ASS = 6			UMETA(DisplayName = "PiGu"),	
	//背部
	COLLISION_BACK = 7		UMETA(DisplayName = "BeiBu"),
	//左手武器
	COLLISION_WEAPON_L = 8		UMETA(DisplayName = "ZuoWuQi"),
	//右手武器
	COLLISION_WEAPON_R = 9		UMETA(DisplayName = "YouWuQi"),

	//全部碰撞点
	COLLISION_ALL_MAX			UMETA(DisplayName = "QuanBu"),
};

//角色默认技能下标
UENUM(BlueprintType)
enum PLAYER_SKILL_TYPE	
{
	//默认
	PLAYER_SKILL_NONE = 0			UMETA(DisplayName = "PLAYER_SKILL_NONE"),	
	//普通攻击
	PLAYER_SKILL_ATTACK = 1		UMETA(DisplayName = "PLAYER_SKILL_ATTACK"),
	//空中攻击
	PLAYER_SKILL_SKYATTACK = 2		UMETA(DisplayName = "PLAYER_SKILL_SKYATTACK"),
	//追击
	PLAYER_SKILL_CHASE = 3			UMETA(DisplayName = "PLAYER_SKILL_CHASE"),
	//临时1
	PLAYER_SKILL_TEMP1 = 4			UMETA(DisplayName = "PLAYER_SKILL_TEMP1"),
	//临时2
	PLAYER_SKILL_TEMP2 = 5			UMETA(DisplayName = "PLAYER_SKILL_TEMP2"),
	//临时3
	PLAYER_SKILL_TEMP3 = 6			UMETA(DisplayName = "PLAYER_SKILL_TEMP3"),
	//临时4
	PLAYER_SKILL_TEMP4 = 7			UMETA(DisplayName = "PLAYER_SKILL_TEMP4"),

	PLAYER_SKILL_MAX,
};

//武器类型
UENUM(BlueprintType)
enum class CHARACTER_WEAPON_TYPE : uint8
{
	//默认
	WEAPON_NONE = 0  UMETA(DisplayName = "WEAPON_NONE"),
	//双手棍
	WEAPON_STICK = 1 UMETA(DisplayName = "WEAPON_STICK"),

	WEAPON_MAX = 255,

};

UENUM(BlueprintType)
enum  WeaponQuality
{
	WQ_None,		  //
	WQ_White,			  //白色[凡品]
	WQ_Green,	          //绿色[良品]
	WQ_Blue,              //蓝色[上品]
	WQ_Purple,			  //紫色[精品]
	WQ_Orange,			  //橙色[极品]
	WQ_Max
};

UENUM(BlueprintType)
enum AddtionalProperty
{
	AP_None ,
	AP_Gold,			  //   金木水火土
	AP_Wood,
	AP_Water,
	AP_Fire,
	AP_Earth,
	AP_Max
};

UENUM(BlueprintType)
enum WeaponType
{
	WT_None,
	WT_Stick,
	WT_Max
};

/** keep in sync with PandaImpactEffect */
UENUM()
namespace PandaPhysMaterialType
{
	enum Type
	{
		Unknown,
		Concrete,
		Dirt,
		Water,
		Metal,
		Wood,
		Grass,
		Glass,
		Flesh,
	};
}

#define PANDA_SURFACE_Default	SurfaceType_Default
#define PANDA_SURFACE_Concrete	SurfaceType1
#define PANDA_SURFACE_Dirt		SurfaceType2
#define PANDA_SURFACE_Water		SurfaceType3
#define PANDA_SURFACE_Metal		SurfaceType4
#define PANDA_SURFACE_Wood		SurfaceType5
#define PANDA_SURFACE_Grass		SurfaceType6
#define PANDA_SURFACE_Glass		SurfaceType7
#define PANDA_SURFACE_Flesh		SurfaceType8

USTRUCT(BlueprintType)
struct FsWeaponBaseData
{
public:
	GENERATED_USTRUCT_BODY()

public:
	//品质
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	TEnumAsByte<enum WeaponQuality>	 m_WeaponQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	TEnumAsByte<enum WeaponType>     m_WeaponType;

	//附加属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	TEnumAsByte<enum AddtionalProperty>	 m_AddtionalProperty;

	//物品等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int32 m_nItemLevel;

	//幸运
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
    float m_fLuck;

	//灵气
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float m_fSpirit;


    FsWeaponBaseData():
		m_WeaponQuality(WQ_None),
		m_WeaponType(WT_None),
		m_AddtionalProperty(AP_None),
		m_nItemLevel(0),
		m_fLuck(0),
		m_fSpirit(0)
	{
	}

};

//区间结构
USTRUCT(BlueprintType)
struct FsInterval
{
public:
	GENERATED_USTRUCT_BODY()

	//起始
	UPROPERTY(BlueprintReadWrite, Category = "FsInterval")
	float fBegin;

	//结束
	UPROPERTY(BlueprintReadWrite, Category = "FsInterval")
	float fEnd;

	FsInterval()
		: fBegin(0)
		, fEnd(0)
	{

	}
};

//数据表头.所有数据表继承此结构
USTRUCT(BlueprintType)
struct FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()
	//表ID
	UPROPERTY(BlueprintReadWrite, Category = "FsTableBase")
	int32 nID;

	FsTableBase()
		: nID(0)
	{

	}
};

//公用字符串表
USTRUCT(BlueprintType)
struct FsStringTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//字符串内容
	UPROPERTY(BlueprintReadWrite, Category = "StringTable")
	FString strDesc;

	FsStringTable()
		: strDesc(TEXT(""))
	{

	}
};

// 任务表
USTRUCT()
struct FsTaskInfo : public FsTableBase
{
	GENERATED_USTRUCT_BODY()
public:
	/** 任务ID*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32  TaskId;
	/** 集成任务IDID*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32  NextTaskId;
	/** 限制等级*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32  LevelLimit;
	/** 推荐等级*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32  RecommendLevel;
	/** 任务名称*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	FString TaskName;
	/** 任务类型*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 TaskType;
	/** 任务触发类型*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 TriggerType;
	/** 任务限制时间*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 LimitTime;
	/** 领取NPCID*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 AcceptNPCID;
	/** 交付NPCID*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 ConsignNPCID;
	/** 目标ID*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 TargetID;
	/** 副本ID*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 SceneID;
	/** 目标数量*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 TargetNum;
	/** 奖励金币*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 RewardGold;
	/** 奖励经验*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 RewardEXP;
	/** 奖励道具数组*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	TArray<int32> RewardItemID;
	/** 领取对话ID 数组*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	TArray<int32> TalkContentID;
	/** 交付对话ID 数组*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 ConsignDialogID;
	/** 失败对话ID 数组*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 FailedDialogID;
	/** 执行中对话ID 数组*/
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 DoingDialogID;
	//////////////////////////////////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, Category = "TaskInfoTable")
	int32 DescriptionID;


	FsTaskInfo()
	{
		NextTaskId = 0;
		LevelLimit = 0;
		RecommendLevel = 0;
		TaskName = FString(TEXT(""));
		TaskType = 0;
		TriggerType = 0;
		LimitTime = 0.0f;
		AcceptNPCID = 0;
		ConsignNPCID = 0;
		TargetID = 0;
		SceneID = 0;
		TargetNum = 0;
		RewardGold = 0;
		RewardEXP = 0;
		RewardItemID.Empty();
		TalkContentID.Empty();
		ConsignDialogID = 0;
		FailedDialogID = 0;
		DoingDialogID = 0;
		DescriptionID = 0;
	}
};


// 武馆数据表
USTRUCT(BlueprintType)
struct FsMartialclubTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	// 武馆等级
	UPROPERTY(BlueprintReadWrite, Category = "MartialclubTable")
	int32 nLevel;
	// 最大人数
	UPROPERTY(BlueprintReadWrite, Category = "MartialclubTable")
	int32 nMaxMember;
	// 武馆设施数量
	UPROPERTY(BlueprintReadWrite, Category = "MartialclubTable")
	int32 nBuildNum;
	// 声望
	UPROPERTY(BlueprintReadWrite, Category = "MartialclubTable")
	int32 nPrestige;
	// 家丁等级
	UPROPERTY(BlueprintReadWrite, Category = "ResourcesTable")
	int32 nNPCLevel;
	// 家丁数量
	UPROPERTY(BlueprintReadWrite, Category = "ResourcesTable")
	int32 nNPCNum;

	FsMartialclubTable()
		: nLevel(1)
		, nMaxMember(50)
		, nBuildNum(1)
		, nPrestige(0)
		, nNPCLevel(1)
		, nNPCNum(5)
	{

	}
};

//公用资源表
USTRUCT(BlueprintType)
struct FsResourcesTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//路径
	UPROPERTY(BlueprintReadWrite, Category = "ResourcesTable")
	FString strPath;

	//名称
	UPROPERTY(BlueprintReadWrite, Category = "ResourcesTable")
	FString strName;

	FsResourcesTable()
		: strPath(TEXT(""))
		, strName(TEXT(""))
	{

	}
};