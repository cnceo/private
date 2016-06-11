#pragma once
#include "CommonDefine.h"
#include "PASkillData.generated.h"

//����������ʽ�ṹ
USTRUCT(BlueprintType)
struct FsNextInput
{
public:
	GENERATED_USTRUCT_BODY()

	//���밴��1 PLAYER_KEY
	UPROPERTY(BlueprintReadWrite, Category = "NextInput")
	int32 nKey_1;

	//���밴��2 PLAYER_KEY
	UPROPERTY(BlueprintReadWrite, Category = "NextInput")
	int32 nKey_2;

	//�����ļ���ʵ����.ԭ����չ�����±�
	UPROPERTY(BlueprintReadWrite, Category = "NextInput")
		int32 nNextIndex;

	FsNextInput()
		: nNextIndex(0)
		, nKey_1(0)
		, nKey_2(0)
	{

	}
};

//����ԭ������
UENUM(BlueprintType)
enum class SKILL_ATOM_TYPE :uint8
{
	//��
	SKILL_ATOM_NONE = 0				UMETA(DisplayName = "ATOM_NONE"),
	//����
	SKILL_ATOM_HIT = 1				UMETA(DisplayName = "ATOM_HIT"),
	//׷��
	SKILL_ATOM_CHASE = 2				UMETA(DisplayName = "ATOM_CHASE"),
	//�ӵ�
	SKILL_ATOM_BULLET = 3				UMETA(DisplayName = "ATOM_BULLET"),
	//����
	SKILL_ATOM_GUIDE = 4				UMETA(DisplayName = "ATOM_GUIDE"),
	//����
	SKILL_ATOM_CHAIN = 5				UMETA(DisplayName = "ATOM_CHAIN"),

	SKILL_ATOM_MAX					UMETA(DisplayName = "ATOM_MAX"),
};

//ԭ�ӽ�������
UENUM(BlueprintType)
enum class ATOM_NEXT_TYPE :uint8
{
	//��
	ATOM_NEXT_NONE = 0				UMETA(DisplayName = "NEXT_NONE"),
	//ʱ������
	ATOM_NEXT_TIME = 1				UMETA(DisplayName = "NEXT_TIME"),
	//��������
	ATOM_NEXT_BEEND = 2				UMETA(DisplayName = "NEXT_BEEND"),
	//�û���������(�����޶�)
	ATOM_NEXT_INPUT = 3				UMETA(DisplayName = "NEXT_INPUT"),
	//������ʱ����
	ATOM_NEXT_BEHIT = 4				UMETA(DisplayName = "NEXT_BEHIT"),
	//���ò��Žڵ�ӿ�ʱ����(�����޶�)
	ATOM_NEXT_CALL = 5				UMETA(DisplayName = "NEXT_CALL"),
	//��ײʱ����(�ӵ�ԭ���޶�)
	ATOM_NEXT_COLLISTION = 6			UMETA(DisplayName = "NEXT_COLLISTION"),

	ATOM_NEXT_MAX,
};

//��������Ч������
UENUM(BlueprintType)
enum class EFFECT_HIT_LEVEL :uint8
{
	//��
	EFFECT_HIT_NONE = 0				UMETA(DisplayName = "EFFECT_HIT_NONE"),

	//��ͨ
	EFFECT_HIT_PUTONG = 1				UMETA(DisplayName = "EFFECT_HIT_PUTONG"),

	//�Ƴ�����
	EFFECT_HIT_POFANG = 21				UMETA(DisplayName = "EFFECT_HIT_POFANG"),

	//�Ƴ�����
	EFFECT_HIT_POJIAZHAO = 41			UMETA(DisplayName = "EFFECT_HIT_POJIAZHAO"),

	//�Ƴ�����
	EFFECT_HIT_POSHANBI = 61			UMETA(DisplayName = "EFFECT_HIT_POSHANBI"),

	//����
	EFFECT_HIT_POMAX = 101				UMETA(DisplayName = "EFFECT_HIT_POJIAZHAO"),

	EFFECT_HIT_MAX,
};

//�ӵ���������
UENUM(BlueprintType)
enum class BULLET_TRIGGER_TYPE :uint8
{
	//��
	BULLET_TRIGGER_NONE = 0			UMETA(DisplayName = "BULLET_TRIGGER_NONE"),
	//���̴���
	BULLET_TRIGGER_BEGIN = 1			UMETA(DisplayName = "BULLET_TRIGGER_BEGIN"),
	//�ӳٴ���
	BULLET_TRIGGER_DELAY = 2			UMETA(DisplayName = "BULLET_TRIGGER_DELAY"),
	//��ײ����
	BULLET_TRIGGER_COLLISTION = 3		UMETA(DisplayName = "BULLET_TRIGGER_COLLISTION"),

	BULLET_TRIGGER__MAX,
};

//�ӵ��ɴ�͸����
UENUM(BlueprintType)
enum class BULLET_PIERCE_TYPE :uint8
{
	//��
	BULLET_PIERCE_NONE = 0			UMETA(DisplayName = "BULLET_PIERCE_NONE"),
	//��
	BULLET_PIERCE_PAWN = 1			UMETA(DisplayName = "BULLET_PIERCE_PAWN"),
	//���ƻ�����
	BULLET_PIERCE_BROKEN = 2		UMETA(DisplayName = "BULLET_PIERCE_BROKEN"),
	//����
	BULLET_PIERCE_FRIEND = 3		UMETA(DisplayName = "BULLET_PIERCE_FRIEND"),
	//����
	BULLET_PIERCE_ENEMY = 4		UMETA(DisplayName = "BULLET_PIERCE_ENEMY"),

	BULLET_PIERCE_MAX,
};

//�ӵ���������
UENUM(BlueprintType)
enum class BULLET_HIT_TYPE :uint8
{
	//��
	BULLET_HIT_NONE = 0			UMETA(DisplayName = "BULLET_HIT_NONE"),
	//��ײһ������
	BULLET_HIT_ONCE = 1			UMETA(DisplayName = "BULLET_HIT_ONCE"),
	//ÿ����ײ����
	BULLET_HIT_MORE = 2			UMETA(DisplayName = "BULLET_HIT_MORE"),
	//ʱ��������
	BULLET_HIT_INTERVAL = 3		UMETA(DisplayName = "BULLET_HIT_INTERVAL"),

	BULLET_HIT_MAX,
};

//ԭ��Ч����
USTRUCT(BlueprintType)
struct FsAtomEffectTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//�Ƿ�����˺�Ч��
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	bool bDamage;

	//�Ƿ�ǿ������(��Ŀ��δ�л�������״̬ǰ����ʹHP<0Ҳ�Ქ�ܻ�����)
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	bool bCombo;

	//HPӰ����ͼ�ű���ԴID
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nHPBP;

	//HPϵ��
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	float fHPNum;

	//MPӰ����ͼ�ű���ԴID
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nMPBP;

	//MPϵ��
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	float fMPNum;

	//����Ӱ����ͼ�ű���ԴID
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nPowerBP;

	//����ϵ��
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	float fPowerNum;

	//����Ч���ȼ� EFFECT_HIT_LEVEL
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nHitLevel;

	//���ֵ
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nBreak;

	//״̬ CHARACTER_STATE
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nState;

	//��״̬ CHARACTER_SUB_STATE
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nSubState;

	//movementMode 
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nMode;

	//BUFF
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	TArray<int32> arrBUFF;

	//���ķ���
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	FVector vDirection;

	//���ĳ���(ǿ��)
	UPROPERTY(BlueprintReadWrite, Category = "AtomEffectTable")
	int32 nForce;

	//���ٶ�
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

//ԭ�ӻ�����
USTRUCT(BlueprintType)
struct FsAtomBaseTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//ԭ������ SKILL_ATOM_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nType;

	//��ɫ������ԴID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nResourcesID;

	//���ں�ʱ��
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	float fFuseTime;

	/***********************�ͷ�����****************************/
	//��������ֵ
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nHP;

	//����ħ��ֵ
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nMP;

	//��������ֵ
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nPower;

	//�����ɫ��Ϊ״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrCharacterState;

	//�����ɫ��Ϊ��״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrCharacterSubState;

	//����Movement״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrMovementMode;

	//����BUFF״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrBUFF;

	//�Ƿ���Ҫ����
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	bool bTarget;

	//��Ŀ���ֱ�߾���.(��λCM)
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	int32 nDistance;

	//����Ŀ����Ϊ״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetState;

	//����Ŀ����Ϊ��״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetSubState;

	//����Ŀ��Movement״̬
	UPROPERTY(BlueprintReadWrite, Category = "AtomBase_Demand")
	TArray<int32> arrTargetMovementMode;

	//����Ŀ��BUFF״̬
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

//����ԭ�ӱ�
USTRUCT(BlueprintType)
struct FsAtomHitTable : public FsAtomBaseTable
{
public:
	GENERATED_USTRUCT_BODY()

	//������Ч��Collision����
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	TArray<FString> arrCollision;

	//�˺���Ч����(����˺�)
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	TArray<FsInterval> arrHitCount;

	//�Ƿ���ԶԵ��صĵ�������˺�
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	bool bTumbleHit;

	FsAtomHitTable()
		:bTumbleHit(false)
	{

	}
};

//׷��ԭ�ӱ�
USTRUCT(BlueprintType)
struct FsAtomChaseTable : public FsAtomBaseTable
{
public:
	GENERATED_USTRUCT_BODY()

	//��׷��Ŀ�����ռ������
	UPROPERTY(BlueprintReadWrite, Category = "AtomChaseTable")
	int32 nSpace;

	//���ٶ�
	UPROPERTY(BlueprintReadWrite, Category = "AtomChaseTable")
	int32 nSpeed;

	//׷����ɺ�ĸ���ʱ��
	UPROPERTY(BlueprintReadWrite, Category = "AtomChaseTable")
	float fFlyTime;

	FsAtomChaseTable()
		: nSpace(0)
		, nSpeed(0)
		, fFlyTime(0)
	{

	}
};

//�ӵ�ԭ�ӱ�
USTRUCT(BlueprintType)
struct FsAtomBulletTable : public FsAtomBaseTable
{
public:
	GENERATED_USTRUCT_BODY()

	//���ӷ�������ԴID
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	int32 nParticle;
	
	//�������� BULLET_TRIGGER_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	int32 nTriggerType;

	//�Ƿ�������������(��ײ��������)
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	bool bNameRules;

	//�󶨵Ĳ������.���û�У���󶨵���ɫ����
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FString strSlot;

	//���ӷ��俪ʼʱ�� ��nTriggerType=2ʱ����Ч
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	float fBeginTime;

	//�ɴ�͸���� BULLET_PIERCE_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<int32> arrPierce;

	//�����������
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	float fLifeTime;

	//���м������ BULLET_HIT_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	int32 nHitType;

	//���ʱ�� nHitType=3ʱ��Ч
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	float FsIntervalTime;

	//�Ƿ���Ŀ���Ϊ����˶�
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	bool bDirectionTarget;

	//���λ��
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vLocation;

	//�����ת��
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FRotator rRotation;

	//��ײ������
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<int32> vCollision;

	FsAtomBulletTable()
		: fLifeTime(0.0f)
		, bDirectionTarget(false)
	{

	}
};

//�ӵ���ײ���
USTRUCT(BlueprintType)
struct FsAtomBulletShapeTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//collision��������.ֻ���� "","Box","Capsule","Sphere"
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FString strCollision;

	//collision�ߴ�
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vSize;

	//���λ��
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vLocation;

	//�����ת��
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FRotator vRotation;

	//�ӵ��ķ����ٶ�(���ٶ�)
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	FVector vDirection;

	//�ӵ�������ʱ��
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<FsInterval> arrTime;

	//�ӵ�����
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<FVector> arrInVal;

	//�ӵ�����
	UPROPERTY(BlueprintReadWrite, Category = "FsAtomBulletTable")
	TArray<FVector> arrOutVal;


	FsAtomBulletShapeTable()
		: strCollision(TEXT(""))
	{

	}
};

//����ʵ���е�ԭ����չ��
USTRUCT(BlueprintType)
struct FsAtomExtendTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//ԭ������ SKILL_ATOM_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nType;

	//ԭ��ID��ӦnType����ԭ�ӱ�
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nAtomID;

	//���ӵ��ӵ�ԭ������
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	TArray<int32> arrBulletAtom;

	//ԭ���������� ATOM_NEXT_TYPE
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nNextType;

	//ԭ������ʱ�� nNextType=1ʱ������  ����ʱ��-���ں�ʱ��>fNextTimeʱ����
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	float fNextTime;

	//����ԭ�ӵ��±� nNextType!=0&&nNextType!=3ʱ������
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nNextIndex;

	//ԭ���������� nNextType=3ʱ������
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	TArray<FsNextInput> arrInput;

	//���ܶ��Լ�������Ӱ��.��ӦFsAtomEffectTable��
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nEffectSelf;

	//���ܶ��ѷ�������Ӱ��.��ӦFsAtomEffectTable��
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nEffectFriend;

	//���ܶԵ��˲�����Ӱ��.��ӦFsAtomEffectTable��
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	int32 nEffectEnemy;

	//�Ƿ�����ɫ��ײ�����ļ��ܽǶȵ���
	UPROPERTY(BlueprintReadWrite, Category = "AtomExtendTable")
	bool bAutoAngle;

	//�ü����Զ������Ƕ�����Ҫ�ĽǶȷ�Χ
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

//����ʵ����
USTRUCT(BlueprintType)
struct FsSkillTable : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//��������ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nName;

	//��������ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nDesc;

	//������ԴID
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	int32 nAnim;

	//ԭ������ ��ӦFsAtomExtendTable��
	UPROPERTY(BlueprintReadWrite, Category = "AtomBaseTable")
	TArray<FString> arrAtomExtend;

	FsSkillTable()
	{

	}
};

//��������
USTRUCT(BlueprintType)
struct FsSkillTreeTable
{
public:
	GENERATED_USTRUCT_BODY()

	//��ID
	UPROPERTY(BlueprintReadWrite, Category = "AtomHitTable")
	int32 nID;

	FsSkillTreeTable()
		: nID(0)
	{

	}
};

//��������Ŀ������
USTRUCT(BlueprintType)
struct FsSkillHitResult
{
public:
	GENERATED_USTRUCT_BODY()

	//��ǰ�˺�����
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurHitCount;

	//HP�ı�
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurHP;

	//MP�ı�
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurMP;

	//�����ı�
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	int32 nCurPower;

	//��ǰ�������
	UPROPERTY(BlueprintReadWrite, Category = "SkillHitResult")
	UPrimitiveComponent* pOtherComp;

	//����Ч��������
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
