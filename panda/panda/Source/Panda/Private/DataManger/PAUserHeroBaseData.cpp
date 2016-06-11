// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PAUserHeroBaseData.h"


//void UPAUserHeroBaseData::InitServerData_Implementation(int32 nServerTag)
//{}
//void UPAUserHeroBaseData::InitClientData_Implementation()
//{}
//void UPAUserHeroBaseData::Init_Implementation(float fTime, FName AnimName)
//{}

// Sets default values for this component's properties
UPAUserHeroBaseData::UPAUserHeroBaseData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	InitProto3Data();
	// ...
}

// Called when the game starts
void UPAUserHeroBaseData::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UPAUserHeroBaseData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPAUserHeroBaseData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	DOREPLIFETIME(UPAUserHeroBaseData, UnrealCurrentData);
}

void UPAUserHeroBaseData::InitProto3Data()
{

	// do something... Proto3Data
}

void UPAUserHeroBaseData::ParseProto3ToUnreal(const proto3::UserHeroBaseData& data)
{
	/* 1 */
	UnrealCurrentData.nID = data.nid();
	/* 2 */
	UnrealCurrentData.nNameId = data.nnameid();
	/* 3 */
	UnrealCurrentData.nSign = data.nsign();
	/* 4 */
	UnrealCurrentData.nType = data.ntype();
	/* 5 */
	UnrealCurrentData.nStageChange_NextHeroID = data.nstagechange_nextheroid();
	/* 6 */
	UnrealCurrentData.nStageChange_AnimId = data.nstagechange_animid();
	/* 7 */
	UnrealCurrentData.nStageChange_EffectId = data.nstagechange_effectid();
	UnrealCurrentData.nStageChange_SoundId = data.nstagechange_soundid();
	/* 8 */
	UnrealCurrentData.nAITreeId = data.naitreeid();
	/* 9 */
	UnrealCurrentData.nCharacterBPId = data.ncharacterbpid();
	/* 10 */
	UnrealCurrentData.nAnimBPId = data.nanimbpid();
	/* 11 */
	UnrealCurrentData.nTaskID = data.ntaskid();
	/* 12 */
	UnrealCurrentData.nAvatar = data.navatar();
	/* 13 */
	UnrealCurrentData.nVocation = data.nvocation();
	/* 14 */
	UnrealCurrentData.nEquip_1 = data.nequip_1();
	/* 15 */
	UnrealCurrentData.nEquip_2 = data.nequip_2();
	/* 16 */
	UnrealCurrentData.nEquip_3 = data.nequip_3();
	/* 17 */
	UnrealCurrentData.nEquip_4 = data.nequip_4();
	/* 18 */
	UnrealCurrentData.nEquip_5 = data.nequip_5();
	/* 19 */
	UnrealCurrentData.nEquip_6 = data.nequip_6();
	/* 20 */
	UnrealCurrentData.nEquip_7 = data.nequip_7();
	/* 21 */
	UnrealCurrentData.nEquip_8 = data.nequip_8();
	/* 22 */
	UnrealCurrentData.nWeapon_1 = data.nequip_1();
	/* 23 */
	UnrealCurrentData.nWeapon_2 = data.nequip_2();
	/* 24 */
	UnrealCurrentData.fWalkSpeed = data.fwalkspeed();
	/* 25 */
	UnrealCurrentData.fRunSpeed = data.frunspeed();

	/* 26 */
	UnrealCurrentData.fJumpHeight = data.fjumpheight();
	/* 27 */
	UnrealCurrentData.fHP = data.fhp();
	/* 28 */
	UnrealCurrentData.fMAX_HP = data.fmax_hp();

	/* 29 */
	UnrealCurrentData.fMP = data.fmp();
	/* 30 */
	UnrealCurrentData.fMAX_MP = data.fmax_mp();

	/* 31 */
	UnrealCurrentData.fArmor = data.farmor();
	/* 32 */
	UnrealCurrentData.fMAX_Armor = data.fmax_armor();

	/* 33 */
	UnrealCurrentData.fNormalAttack = data.fnormalattack();
	/* 34 */
	UnrealCurrentData.fNormalDefend = data.fnormaldefend();

	/* 35 */
	UnrealCurrentData.fDodge = data.fdodge();
	/* 36 */
	UnrealCurrentData.fCrit = data.fcrit();
	/* 37 */
	UnrealCurrentData.fCritHurt = data.fcrithurt();
	/* 38 */
	UnrealCurrentData.fBlock = data.fblock();

	/* 39 */
	UnrealCurrentData.fAttackResistance = data.fattackresistance();
	/* 40 */
	UnrealCurrentData.fAttackMulti = data.fattackmulti();
	/* 41 */
	UnrealCurrentData.nLandSkillId = data.nlandskillid();
	/* 42 */
	UnrealCurrentData.nSkillTreeId = data.nskilltreeid();
	/* 43 */
	UnrealCurrentData.nSkySkillId = data.nskyskillid();
	/* 44 */
	UnrealCurrentData.nIntroductionId = data.nintroductionid();

	//种族天赋技能为数组，特殊同步(未编写代码)
	/* 45 */
	//UnrealCurrentData.tArrRacialTalent = FString(data.fstrintroduction().c_str());
}

bool UPAUserHeroBaseData::Server_SetCurrentData_Validate(const FsPAPlayerHeroBaseData& data)
{
	return true;
}

void UPAUserHeroBaseData::Server_SetCurrentData_Implementation(const FsPAPlayerHeroBaseData& data)
{
	UnrealCurrentData = data;
	// if need to set client
	//Client_SetCurrentData(data);
}

void UPAUserHeroBaseData::Client_SetCurrentData(const FsPAPlayerHeroBaseData& data)
{
	UnrealCurrentData = data;
}

float UPAUserHeroBaseData::GetHP()
{
	return UnrealCurrentData.fHP;
}
float UPAUserHeroBaseData::GetMaxHP()
{
	return UnrealCurrentData.fMAX_HP;
}
float UPAUserHeroBaseData::GetMP()
{
	return UnrealCurrentData.fMP;
}
float UPAUserHeroBaseData::GetMaxMP()
{
	return UnrealCurrentData.fMAX_MP;
}
float UPAUserHeroBaseData::GetArmor()
{
	return UnrealCurrentData.fArmor;
}
float UPAUserHeroBaseData::GetMaxArmor()
{
	return UnrealCurrentData.fMAX_Armor;
}
float UPAUserHeroBaseData::GetPower()
{
	return 100;
}
float UPAUserHeroBaseData::GetMaxPower()
{
	return 100;
}

void UPAUserHeroBaseData::SetHP(float fHP)
{
	UnrealCurrentData.fHP = fHP;
}
void UPAUserHeroBaseData::SetMP(float fMP)
{
	UnrealCurrentData.fMP = fMP;
}
void UPAUserHeroBaseData::SetArmor(float fArmor)
{
	UnrealCurrentData.fArmor = fArmor;
}
void UPAUserHeroBaseData::SetPower(float fPower)
{
	// test position
}
