// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserBaseData.h
//  Panda
//  
//  Created by White.tian on 16-5-4-14:58.
//  Copyright (c) 2016�� White.tian All rights reserved.
//
#pragma once

#include "Components/ActorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PADataBaseInterface.h"
#include "CommonDefine.h"
#include "PAMonsterHeroBaseData.generated.h"


/** User Base Data. �����������ݱ�.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAMonsterHeroBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nNameId;							//role name

	/*
		1��
		2ľ
		3ˮ
		4��
		5��
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nSign;								//role nSign

	/**
		1��ͨ
		2��Ӣ
		3BOSS
		4NPC
		5���
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nType;								//type

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_NextMonsterID;			//�л�״̬(�л������¸�����ID)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_AnimId;				//�л�����,�л�����IDʱ��Ķ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_EffectId;				//�л���Ч,�л�����IDʱ�����Ч	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_SoundId;					//�л�����,�л�����IDʱ�������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nAITreeId;							//AItree

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nCharacterBPId;					//��ɫ��ͼ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nAnimBPId;							//������ͼ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fModelScale;							//ģ������ϵ��
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nNPCId;								//nNPCId �����NPC,ֵΪNPCId,������NPC���ݱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nTaskID;								//TaskID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nAvatar;								//Avatar

	/*
		1.սʿ��(��ս����)
		2.����ͣ���սT��
		3.�������ͣ�Զ��DPS��
		4.��ʦ�ͣ�Զ��DPS��
		5.������
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nVocation;							//Vocation

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_1;								//ͷ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_2;								//�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_3;								//�Ҽ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_4;								//���ֲ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_5;								//���ֲ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_6;								//�������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_7;								//������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_8;								//�����������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nWeapon_1;							//�����������֣�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nWeapon_2;							//�����������֣�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fWalkSpeed;							//��·�ٶ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fRunSpeed;							//�ܲ��ٶ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fJumpHeight;							//��Ծ�߶�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fBodyConstitution;					//����ֵ
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fHP;									//HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMAX_HP;								//MAX HP
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMP;									//MP ����
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMAX_MP;								//MAX MP
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fArmor;								//����ֵ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMAX_Armor;							//MAX Armor
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fNormalAttack;						//��ͨ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fNormalDefend;						//��ͨ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fDodge;								//Dodge	����
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fCrit;								//Crit	����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fCritHurt;							//CritHurt	�����˺�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fBlock;								//Block	�м�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fAttackResistance;					//AttackResistance	��������
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fAttackMulti;							//AttackMulti	��������
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fSkillTreeId;							//SkillTreeId	������ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nIntroductionId;						//Introduction	��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float PatrolRadius;							//Ѳ�߰뾶_AIʹ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float WanderDistance;						//�����������_AIʹ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float HearingRadius;						//������Χ_AIʹ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float ChaseRadius;							//׷����Χ_AIʹ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float SprintRadius;							//��Ŀ��֮��ľ���_AIʹ��


	FsPAMonsterHeroBaseData()
		//: nId(1)
		//, fstrName(TEXT("TaiLung"))
		//, nSign(1)
		//, nType(1)
		//, nStageChange_NextMonsterID(1)
		//, fstrStageChange_Anim(TEXT(""))
		//, fstrStageChange_Effect(TEXT(""))
		//, fstrAITree(TEXT(""))
		//, fstrCharacterBP(TEXT(""))
		//, fstrAnimBP(TEXT(""))
		//, nTaskID(1)
		//, nAvatar(1)
		//, nVocation(1)
		//, nEquip_1(0)
		//, nEquip_2(0)
		//, nEquip_3(0)
		//, nEquip_4(0)
		//, nEquip_5(0)
		//, nEquip_6(0)
		//, nEquip_7(0)
		//, nEquip_8(0)
		//, nWeapon_1(0)
		//, nWeapon_2(0)
		//, fWalkSpeed(0.f)
		//, fRunSpeed(0.f)
		//, fJumpHeight(0.f)
		//, fBodyConstitution(0.f)
		//, fHP(300.f)
		//, fMAX_HP(300.f)
		//, fMP(1.f)
		//, fMAX_MP(1.f)
		//, fArmor(80.f)
		//, fMAX_Armor(80.f)
		//, fNormalAttack(10.f)
		//, fNormalDefend(10.f)
		//, fDodge(10.f)
		//, fCrit(10.f)
		//, fCritHurt(1.5f)
		//, fBlock(10.f)
		//, fAttackResistance(10.f)
		//, fAttackMulti(10.f)
		//, fSkillTreeId(10.f)
		//, fstrIntroduction(TEXT("This is Introduce String."))
	{
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PANDA_API UPAMonsterHeroBaseData : public UActorComponent
{
	GENERATED_BODY()

	/* Server Data*/
	proto3::MonsterHeroBaseData Proto3Data;
	void InitProto3Data();
	void ParseProto3ToUnreal(const proto3::MonsterHeroBaseData& data);
public:	
	// Sets default values for this component's properties
	UPAMonsterHeroBaseData();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public:
	/** Information about the current user data variable. */
	UPROPERTY(EditAnywhere, Category = "UPAMonsterHeroBaseDataComponent"/*, VisibleInstanceOnly*/, Replicated)
	FsPAMonsterHeroBaseData UnrealCurrentData;
	
	// Monster Data No Have Set
	//void set...();
public:
	/*
	*	GetNowHP()
	*	GetNowMP()
	*	GetNowPower()
	*/
	float GetHP();
	float GetMaxHP();
	float GetMP();
	float GetMaxMP();
	float GetArmor();
	float GetMaxArmor();
	float GetPower();
	float GetMaxPower();

	/*
	*	SetNowHP()
	*	SetNowMP()
	*	SetNowPower()
	*/
	void SetHP(float fHP);
	void SetMP(float fMP);
	void SetArmor(float fArmor);
	void SetPower(float fPower);


	UBehaviorTree* m_UBehaviorTree;
	/* Fisrt parse local data, after Create BehaviorTree Asset by excel data */
	void ParseCreateBehaviorTree();
	/* Get BehaviorTree */
	UBehaviorTree* GetBehaviorTree();

	/* Create Role BP */
	void ParseCreateCharacterBP();

	/* Create Anim BP */
	UClass* NewAnimBPClass;
	void ParseCreateAnimBPClass();
	/* Get Anim BP */
	UClass* GetAnimBPClass();
};