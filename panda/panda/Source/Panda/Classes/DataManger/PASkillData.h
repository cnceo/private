#pragma once
#include "CommonDefine.h"
#include "PASkillData.generated.h"

//技能连续招式结构
USTRUCT(BlueprintType)
struct FsNextInput
{
public:
	GENERATED_USTRUCT_BODY()

	//输入按键1 PLAYER_KEY
	UPROPERTY(BlueprintReadWrite, Category = "NextInput")
	int32 nKey_1;

	//输入按键2 PLAYER_KEY
	UPROPERTY(BlueprintReadWrite, Category = "NextInput")
	int32 nKey_2;

	//触发的技能实例中.原子扩展数组下标
	UPROPERTY(BlueprintReadWrite, Category = "NextInput")
		int32 nNextIndex;

	FsNextInput()
		: nNextIndex(0)
		, nKey_1(0)
		, nKey_2(0)
	{

	}
};

//技能原子类型
UENUM(BlueprintType)
enum class SKILL_ATOM_TYPE :uint8
{
	//无
	SKILL_ATOM_NONE = 0				UMETA(DisplayName = "ATOM_NONE"),
	//命中
	SKILL_ATOM_HIT = 1				UMETA(DisplayName = "ATOM_HIT"),
	//追击
	SKILL_ATOM_CHASE = 2				UMETA(DisplayName = "ATOM_CHASE"),
	//子弹
	SKILL_ATOM_BULLET = 3				UMETA(DisplayName = "ATOM_BULLET"),
	//引导
	SKILL_ATOM_GUIDE = 4				UMETA(DisplayName = "ATOM_GUIDE"),
	//连锁
	SKILL_ATOM_CHAIN = 5				UMETA(DisplayName = "ATOM_CHAIN"),

	SKILL_ATOM_MAX					UMETA(DisplayName = "ATOM_MAX"),
};

//原子接连类型
UENUM(BlueprintType)
enum class ATOM_NEXT_TYPE :uint8
{
	//无
	ATOM_NEXT_NONE = 0				UMETA(DisplayName = "NEXT_NONE"),
	//时间连接
	ATOM_NEXT_TIME = 1				UMETA(DisplayName = "NEXT_TIME"),
	//结束连接
	ATOM_NEXT_BEEND = 2				UMETA(DisplayName = "NEXT_BEEND"),
	//用户输入连接(主角限定)
	ATOM_NEXT_INPUT = 3				UMETA(DisplayName = "NEXT_INPUT"),
	//被攻击时连接
	ATOM_NEXT_BEHIT = 4				UMETA(DisplayName = "NEXT_BEHIT"),
	//调用播放节点接口时连接(主角限定)
	ATOM_NEXT_CALL = 5				UMETA(DisplayName = "NEXT_CALL"),
	//碰撞时连接(子弹原子限定)
	ATOM_NEXT_COLLISTION = 6			UMETA(DisplayName = "NEXT_COLLISTION"),

	ATOM_NEXT_MAX,
};

//技能命中效果类型
UENUM(BlueprintType)
enum class EFFECT_HIT_LEVEL :uint8
{
	//无
	EFFECT_HIT_NONE = 0				UMETA(DisplayName = "EFFECT_HIT_NONE"),

	//普通
	EFFECT_HIT_PUTONG = 1				UMETA(DisplayName = "EFFECT_HIT_PUTONG"),

	//破除防御
	EFFECT_HIT_POFANG = 21				UMETA(DisplayName = "EFFECT_HIT_POFANG"),

	//破除架招
	EFFECT_HIT_POJIAZHAO = 41			UMETA(DisplayName = "EFFECT_HIT_POJIAZHAO"),

	//破除闪避
	EFFECT_HIT_POSHANBI = 61			UMETA(DisplayName = "EFFECT_HIT_POSHANBI"),

	//必中
	EFFECT_HIT_POMAX = 101				UMETA(DisplayName = "EFFECT_HIT_POJIAZHAO"),

	EFFECT_HIT_MAX,
};

//子弹触发类型
UENUM(BlueprintType)
enum class BULLET_TRIGGER_TYPE :uint8
{
	//无
	BULLET_TRIGGER_NONE = 0			UMETA(DisplayName = "BULLET_TRIGGER_NONE"),
	//立刻触发
	BULLET_TRIGGER_BEGIN = 1			UMETA(DisplayName = "BULLET_TRIGGER_BEGIN"),
	//延迟触发
	BULLET_TRIGGER_DELAY = 2			UMETA(DisplayName = "BULLET_TRIGGER_DELAY"),
	//碰撞触发
	BULLET_TRIGGER_COLLISTION = 3		UMETA(DisplayName = "BULLET_TRIGGER_COLLISTION"),

	BULLET_TRIGGER__MAX,
};

//子弹可穿透类型
UENUM(BlueprintType)
enum class BULLET_PIERCE_TYPE :uint8
{
	//无
	BULLET_PIERCE_NONE = 0			UMETA(DisplayName = "BULLET_PIERCE_NONE"),
	//人
	BULLET_PIERCE_PAWN = 1			UMETA(DisplayName = "BULLET_PIERCE_PAWN"),
	//可破坏物体
	BULLET_PIERCE_BROKEN = 2		UMETA(DisplayName = "BULLET_PIERCE_BROKEN"),
	//队友
	BULLET_PIERCE_FRIEND = 3		UMETA(DisplayName = "BULLET_PIERCE_FRIEND"),
	//敌人
	BULLET_PIERCE_ENEMY = 4		UMETA(DisplayName = "BULLET_PIERCE_ENEMY"),

	BULLET_PIERCE_MAX,
};

//子弹命中类型
UENUM(BlueprintType)
enum class BULLET_HIT_TYPE :uint8
{
	//无
	BULLET_HIT_NONE = 0			UMETA(DisplayName = "BULLET_HIT_NONE"),
	//碰撞一次命中
	BULLET_HIT_ONCE = 1			UMETA(DisplayName = "BULLET_HIT_ONCE"),
	//每次碰撞命中
	BULLET_HIT_MORE = 2			UMETA(DisplayName = "BULLET_HIT_MORE"),
	//时间间隔命中
	BULLET_HIT_INTERVAL = 3		UMETA(DisplayName = "BULLET_HIT_INTERVAL"),

	BULLET_HIT_MAX,
};

//原子效果表
USTRUCT(BlueprintType)
struct FsAtomEffectTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//是否包含伤害效果
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	bool bDamage;

	//是否强制连击(在目标未切换到死亡状态前，即使HP<0也会播受击动画)
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	bool bCombo;

	//HP影响蓝图脚本资源ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nHPBP;

	//HP系数
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	float fHPNum;

	//MP影响蓝图脚本资源ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nMPBP;

	//MP系数
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	float fMPNum;

	//体力影响蓝图脚本资源ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nPowerBP;

	//体力系数
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	float fPowerNum;

	//命中效果等级 EFFECT_HIT_LEVEL
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nHitLevel;

	//打断值
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nBreak;

	//状态 CHARACTER_STATE
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nState;

	//子状态 CHARACTER_SUB_STATE
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nSubState;

	//movementMode 
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nMode;

	//BUFF
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	TArray<int32> arrBUFF;

	//力的方向
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	FVector vDirection;

	//力的长度(强度)
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nForce;

	//加速度
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	FVector vVelocity;

	FsAtomEffectTable()
		: bDamage(false)
		, bCombo(false)
		, nHPBP(0)
		, fHPNum(0)
		, nMPBP(0)
		, fMPNum(0)
		, nPowerBP(0)
		, fPowerNum(0)
		, nHitLevel(0)
		, nBreak(0)
		, nState(0)
		, nSubState(0)
		, nMode(0)
		, nForce(0)
	{

	}
};

//原子基础表
USTRUCT(BlueprintType)
struct FsAtomBaseTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//原子类型 SKILL_ATOM_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nType;

	//角色动画资源ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nResourcesID;

	//可融合时间
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	float fFuseTime;

	/***********************释放需求****************************/
	//消耗生命值
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nHP;

	//消耗魔法值
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nMP;

	//消耗体力值
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nPower;

	//需求角色行为状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrCharacterState;

	//需求角色行为子状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrCharacterSubState;

	//需求Movement状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrMovementMode;

	//需求BUFF状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrBUFF;

	//是否需要索敌
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	bool bTarget;

	//与目标的直线距离.(单位CM)
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nDistance;

	//需求目标行为状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetState;

	//需求目标行为子状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetSubState;

	//需求目标Movement状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetMovementMode;

	//需求目标BUFF状态
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetBUFF;

	FsAtomBaseTable()
		: nType(0)
		, nResourcesID(0)
		, nHP(0)
		, nMP(0)
		, nPower(0)
		, fFuseTime(0)
		, bTarget(false)
		, nDistance(0)
	{

	}

};

//命中原子表
USTRUCT(BlueprintType)
struct FsAtomHitTable : public FsAtomBaseTable
{
public:
	GENERATED_USTRUCT_BODY()

	//命中生效的Collision类型
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	TArray<FString> arrCollision;

	//伤害生效条件(多段伤害)
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	TArray<FsInterval> arrHitCount;

	//是否可以对倒地的敌人造成伤害
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	bool bTumbleHit;

	FsAtomHitTable()
		:bTumbleHit(false)
	{

	}
};

//追击原子表
USTRUCT(BlueprintType)
struct FsAtomChaseTable : public FsAtomBaseTable
{
public:
	GENERATED_USTRUCT_BODY()

	//与追击目标最终间隔距离
	UPROPERTY(BlueprintReadWrite, Category = "AtomChaseTable")
	int32 nSpace;

	//加速度
	UPROPERTY(BlueprintReadWrite, Category = "AtomChaseTable")
	int32 nSpeed;

	//追击完成后的浮空时间
	UPROPERTY(BlueprintReadWrite, Category = "AtomChaseTable")
	float fFlyTime;

	FsAtomChaseTable()
		: nSpace(0)
		, nSpeed(0)
		, fFlyTime(0)
	{

	}
};

//子弹原子表
USTRUCT(BlueprintType)
struct FsAtomBulletTable : public FsAtomBaseTable
{
public:
	GENERATED_USTRUCT_BODY()

	//粒子发射器资源ID
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	int32 nParticle;
	
	//触发类型 BULLET_TRIGGER_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	int32 nTriggerType;

	//是否启用命名规则(碰撞触发独有)
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	bool bNameRules;

	//绑定的插槽名称.如果没有，则绑定到角色身上
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FString strSlot;

	//粒子发射开始时间 当nTriggerType=2时，生效
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	float fBeginTime;

	//可穿透类型 BULLET_PIERCE_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<int32> arrPierce;

	//最大生命周期
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	float fLifeTime;

	//命中检测类型 BULLET_HIT_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	int32 nHitType;

	//间隔时间 nHitType=3时生效
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	float FsIntervalTime;

	//是否以目标点为结果运动
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	bool bDirectionTarget;

	//相对位置
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vLocation;

	//相对旋转度
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FRotator rRotation;

	//碰撞体数组
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<int32> vCollision;

	FsAtomBulletTable()
		: fLifeTime(0.0f)
		, bDirectionTarget(false)
	{

	}
};

//子弹碰撞体表
USTRUCT(BlueprintType)
struct FsAtomBulletShapeTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//collision类型名称.只能是 "","Box","Capsule","Sphere"
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FString strCollision;

	//collision尺寸
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vSize;

	//相对位置
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vLocation;

	//相对旋转度
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FRotator vRotation;

	//子弹的方向及速度(加速度)
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vDirection;

	//子弹的曲线时段
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<FsInterval> arrTime;

	//子弹曲线
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<FVector> arrInVal;

	//子弹曲线
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<FVector> arrOutVal;


	FsAtomBulletShapeTable()
		: strCollision(TEXT(""))
	{

	}
};

//技能实例中的原子扩展表
USTRUCT(BlueprintType)
struct FsAtomExtendTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//原子类型 SKILL_ATOM_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nType;

	//原子ID对应nType类型原子表
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nAtomID;

	//附加的子弹原子数组
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	TArray<int32> arrBulletAtom;

	//原子连接类型 ATOM_NEXT_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nNextType;

	//原子连接时间 nNextType=1时需配置  经过时间-可融合时间>fNextTime时触发
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	float fNextTime;

	//连接原子的下标 nNextType!=0&&nNextType!=3时需配置
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nNextIndex;

	//原子连接输入 nNextType=3时需配置
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	TArray<FsNextInput> arrInput;

	//技能对自己产生的影响.对应FsAtomEffectTable表
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nEffectSelf;

	//技能对友方产生的影响.对应FsAtomEffectTable表
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nEffectFriend;

	//技能对敌人产生的影响.对应FsAtomEffectTable表
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nEffectEnemy;

	//是否开启角色碰撞检测球的技能角度调整
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	bool bAutoAngle;

	//该技能自动调整角度所需要的角度范围
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	TArray<FsInterval> arrHitAngle;

	FsAtomExtendTable()
		: nType(0)
		, nAtomID(0)
		, nNextType(0)
		, fNextTime(0)
		, nNextIndex(0)
		, nEffectSelf(0)
		, nEffectFriend(0)
		, nEffectEnemy(0)
		, bAutoAngle(false)
	{

	}
};

//技能实例表
USTRUCT(BlueprintType)
struct FsSkillTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//技能名称ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nName;

	//技能描述ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nDesc;

	//动画资源ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nAnim;

	//原子数组 对应FsAtomExtendTable表
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	TArray<FString> arrAtomExtend;

	FsSkillTable()
	{

	}
};

//技能树表
USTRUCT(BlueprintType)
struct FsSkillTreeTable
{
public:
	GENERATED_USTRUCT_BODY()

	//树ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	int32 nID;

	FsSkillTreeTable()
		: nID(0)
	{

	}
};

//技能命中目标数据
USTRUCT(BlueprintType)
struct FsSkillHitResult
{
public:
	GENERATED_USTRUCT_BODY()

	//当前伤害计数
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurHitCount;

	//HP改变
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurHP;

	//MP改变
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurMP;

	//体力改变
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurPower;

	//当前命中组件
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	UPrimitiveComponent* pOtherComp;

	//命中效果表数据
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	FsAtomEffectTable sTableData;

	FsSkillHitResult()
		: nCurHitCount(0)
		, pOtherComp(nullptr)
		, nCurHP(0)
		, nCurMP(0)
		, nCurPower(0)
	{

	}

	FsSkillHitResult(FsAtomEffectTable EffectTable, int32 nHitCount, UPrimitiveComponent* pComp, int32 nHP = 0, int32 nMP = 0, int32 nPower = 0)
	{
		nCurHitCount = nHitCount;
		nCurHP = nHP;
		nCurMP = nMP;
		nCurPower = nPower;
		pOtherComp = pComp;
		sTableData = EffectTable;
	}
};
