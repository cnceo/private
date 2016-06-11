// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserBaseData.h
//  Panda
//  
//  Created by White.tian on 16-5-4-14:58.
//  Copyright (c) 2016年 White.tian All rights reserved.
//
#pragma once

#include "Components/ActorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PADataBaseInterface.h"
#include "CommonDefine.h"
#include "PAMonsterHeroBaseData.generated.h"


/** User Base Data. 怪物属性数据表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAMonsterHeroBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nNameId;							//role name

	/*
		1金
		2木
		3水
		4火
		5土
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nSign;								//role nSign

	/**
		1普通
		2精英
		3BOSS
		4NPC
		5伙伴
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nType;								//type

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_NextMonsterID;			//切换状态(切换到的下个怪物ID)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_AnimId;				//切换动画,切换怪物ID时候的动画

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_EffectId;				//切换特效,切换怪物ID时候的特效	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nStageChange_SoundId;					//切换声音,切换怪物ID时候的声音

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nAITreeId;							//AItree

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nCharacterBPId;					//角色蓝图

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nAnimBPId;							//动画蓝图

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fModelScale;							//模型缩放系数
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nNPCId;								//nNPCId 如果是NPC,值为NPCId,索引到NPC数据表

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nTaskID;								//TaskID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nAvatar;								//Avatar

	/*
		1.战士型(近战均衡)
		2.肉盾型（近战T）
		3.弓箭手型（远程DPS）
		4.法师型（远程DPS）
		5.辅助型
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nVocation;							//Vocation

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_1;								//头部插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_2;								//左肩插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_3;								//右肩插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_4;								//左手插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_5;								//右手插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_6;								//腰部插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_7;								//披风插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nEquip_8;								//背部武器插槽

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nWeapon_1;							//主武器（右手）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nWeapon_2;							//副武器（右手）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fWalkSpeed;							//走路速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fRunSpeed;							//跑步速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fJumpHeight;							//跳跃高度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fBodyConstitution;					//体质值
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fHP;									//HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMAX_HP;								//MAX HP
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMP;									//MP 内力
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMAX_MP;								//MAX MP
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fArmor;								//霸体值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fMAX_Armor;							//MAX Armor
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fNormalAttack;						//普通攻击

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fNormalDefend;						//普通防御

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fDodge;								//Dodge	闪避
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fCrit;								//Crit	暴击

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fCritHurt;							//CritHurt	暴击伤害

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fBlock;								//Block	招架

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fAttackResistance;					//AttackResistance	攻击免疫
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fAttackMulti;							//AttackMulti	攻击增益
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float fSkillTreeId;							//SkillTreeId	技能树ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	int32 nIntroductionId;						//Introduction	介绍文字

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float PatrolRadius;							//巡逻半径_AI使用

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float WanderDistance;						//最大迈步距离_AI使用

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float HearingRadius;						//听力范围_AI使用

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float ChaseRadius;							//追击范围_AI使用

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAMonsterHeroBaseData")
	float SprintRadius;							//与目标之间的距离_AI使用


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