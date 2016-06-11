// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserBaseData.h
//  Panda
//  
//  Created by White.tian on 16-5-3.
//  Copyright (c) 2016年 White.tian All rights reserved.
//
#pragma once

#include "Components/ActorComponent.h"
#include "PADataBaseInterface.h"
#include "CommonDefine.h"
#include "PAUserHeroBaseData.generated.h"



/** User Base Data. 角色属性数据表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAPlayerHeroBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nNameId;							//role name

	/*
		1金
		2木
		3水
		4火
		5土
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nSign;								//role nSign

	/**
		1普通
		2精英
		3BOSS
		4NPC
		5伙伴
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nType;								//type

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_NextHeroID;				//切换状态(切换到的下个英雄ID)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_AnimId;					//切换动画,切换怪物ID时候的动画

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_EffectId;				//切换特效,切换怪物ID时候的特效	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nStageChange_SoundId;					//切换声音,切换怪物ID时候的声音

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nAITreeId;							//AItree

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nCharacterBPId;						//角色蓝图

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nAnimBPId;							//动画蓝图

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nTaskID;								//TaskID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nAvatar;								//Avatar

	/*
		1.拳师（武当派）
		2.力士（丐帮）
		3.武僧（少林）
		4.侠客（唐门）
		5.剑客（恒山派）
		6.道士（全真教）
		7.药师（桃花岛）
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nVocation;							//Vocation

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_1;								//头部插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_2;								//左肩插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_3;								//右肩插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_4;								//左手插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_5;								//右手插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_6;								//腰部插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_7;								//披风插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nEquip_8;								//背部武器插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nWeapon_1;							//主武器（右手）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nWeapon_2;							//副武器（右手）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fWalkSpeed;							//走路速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fRunSpeed;							//跑步速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fJumpHeight;							//跳跃高度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fHP;									//HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMAX_HP;								//MAX HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMP;									//MP 内力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMAX_MP;								//MAX MP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fArmor;								//霸体值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fMAX_Armor;							//MAX Armor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fNormalAttack;						//普通攻击

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fNormalDefend;						//普通防御

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fDodge;								//Dodge	闪避

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fCrit;								//Crit	暴击

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fCritHurt;							//CritHurt	暴击伤害

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fBlock;								//Block	招架

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fAttackResistance;					//AttackResistance	攻击免疫

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	float fAttackMulti;							//AttackMulti	攻击增益

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int nLandSkillId;								//nSkillId	陆地技能ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int nSkillTreeId;							//nSkillTreeId	技能树ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int nSkySkillId;							//nSkySkillId	空中技能树ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	int32 nIntroductionId;					//Introduction	介绍文字

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAPlayerHeroBaseData")
	TArray<int> tArrRacialTalent;				//种族天赋技能

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

// a.场外属性：场外属性主要指记录在玩家自身的功能所需的属性条目。
// b.战斗属性：战斗中的基础一级属性。
// c.自身属性：角色自身行动数值。影响全局。
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PANDA_API UPAUserHeroBaseData : public UActorComponent, public IPADataBaseInterface
{
	GENERATED_BODY()

	/* Server Data*/
	proto3::UserHeroBaseData Proto3Data;
	void InitProto3Data();
	//服务端下发User数据后，服务端再去取到当前的UserHero_Id从proto3::UserBaseHero中
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
