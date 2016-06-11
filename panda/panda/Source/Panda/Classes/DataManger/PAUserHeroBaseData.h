// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserBaseData.h
//  Panda
//  
//  Created by White.tian on 16-5-3.
//  Copyright (c) 2016�� White.tian All rights reserved.
//
#pragma once

#include "Components/ActorComponent.h"
#include "PADataBaseInterface.h"
#include "CommonDefine.h"
#include "PAUserHeroBaseData.generated.h"



/** User Base Data. ��ɫ�������ݱ�.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAPlayerHeroBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nNameId;							//role name

	/*
		1��
		2ľ
		3ˮ
		4��
		5��
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nSign;								//role nSign

	/**
		1��ͨ
		2��Ӣ
		3BOSS
		4NPC
		5���
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nType;								//type

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_NextHeroID;				//�л�״̬(�л������¸�Ӣ��ID)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_AnimId;					//�л�����,�л�����IDʱ��Ķ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_EffectId;				//�л���Ч,�л�����IDʱ�����Ч	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_SoundId;					//�л�����,�л�����IDʱ�������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nAITreeId;							//AItree

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nCharacterBPId;						//��ɫ��ͼ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nAnimBPId;							//������ͼ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nTaskID;								//TaskID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nAvatar;								//Avatar

	/*
		1.ȭʦ���䵱�ɣ�
		2.��ʿ��ؤ�
		3.��ɮ�����֣�
		4.���ͣ����ţ�
		5.���ͣ���ɽ�ɣ�
		6.��ʿ��ȫ��̣�
		7.ҩʦ���һ�����
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nVocation;							//Vocation

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_1;								//ͷ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_2;								//�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_3;								//�Ҽ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_4;								//���ֲ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_5;								//���ֲ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_6;								//�������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_7;								//������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_8;								//�����������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nWeapon_1;							//�����������֣�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nWeapon_2;							//�����������֣�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fWalkSpeed;							//��·�ٶ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fRunSpeed;							//�ܲ��ٶ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fJumpHeight;							//��Ծ�߶�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fHP;									//HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMAX_HP;								//MAX HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMP;									//MP ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMAX_MP;								//MAX MP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fArmor;								//����ֵ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMAX_Armor;							//MAX Armor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fNormalAttack;						//��ͨ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fNormalDefend;						//��ͨ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fDodge;								//Dodge	����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fCrit;								//Crit	����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fCritHurt;							//CritHurt	�����˺�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fBlock;								//Block	�м�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fAttackResistance;					//AttackResistance	��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fAttackMulti;							//AttackMulti	��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int nLandSkillId;								//nSkillId	½�ؼ���ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int nSkillTreeId;							//nSkillTreeId	������ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int nSkySkillId;							//nSkySkillId	���м�����ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nIntroductionId;					//Introduction	��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	TArray<int> tArrRacialTalent;				//�����츳����

	FsPAPlayerHeroBaseData()
		: fHP(300)
		//: nId(1)
		//, fstrName(TEXT(""))
		//, nSign(1)
		//, nType(1)
		//, nStageChange_NextHeroID(1)
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
		//, fstrIntroduction(TEXT("This is Introduce String."))
	{
	}
};

// a.�������ԣ�����������Ҫָ��¼���������Ĺ��������������Ŀ��
// b.ս�����ԣ�ս���еĻ���һ�����ԡ�
// c.�������ԣ���ɫ�����ж���ֵ��Ӱ��ȫ�֡�
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PANDA_API UPAUserHeroBaseData : public UActorComponent, public IPADataBaseInterface
{
	GENERATED_BODY()

	/* Server Data*/
	proto3::UserHeroBaseData Proto3Data;
	void InitProto3Data();
	//������·�User���ݺ󣬷������ȥȡ����ǰ��UserHero_Id��proto3::UserBaseHero��
	void ParseProto3ToUnreal(const proto3::UserHeroBaseData& data);
public:
	// Sets default values for this component's properties
	UPAUserHeroBaseData();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Information about the current user data variable. */
	UPROPERTY(EditAnywhere, Category = "UPAUserBaseHeroDataComponent"/*, VisibleInstanceOnly*/, Replicated)
	FsPAPlayerHeroBaseData UnrealCurrentData;
	
	/** Server:Information about to set current user base data. */
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_SetCurrentData(const FsPAPlayerHeroBaseData& data);

	void Server_SetCurrentData_Implementation(const FsPAPlayerHeroBaseData& data);
	bool Server_SetCurrentData_Validate(const FsPAPlayerHeroBaseData& data);

	/** Client:Information about to set current user base data. */
	void Client_SetCurrentData(const FsPAPlayerHeroBaseData& data);

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
};
