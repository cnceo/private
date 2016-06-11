// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PAMonsterHeroBaseData.h"
#include "PandaUtils.h"
#include "PandaGameInstance.h"


// Sets default values for this component's properties
UPAMonsterHeroBaseData::UPAMonsterHeroBaseData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	InitProto3Data();

	/* ConstructorHelpers */
	/*static ConstructorHelpers::FObjectFinder<UBehaviorTree> BasicTree(TEXT("BlackboardData'/Game/AI/MonsterBehavior.MonsterBehavior_C'"));
	m_UBehaviorTree = BasicTree.Object;*/

	// ...
}

// Called when the game starts
void UPAMonsterHeroBaseData::BeginPlay()
{
	Super::BeginPlay();

	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		//auto b = gameInstance->SafeGetDataManager()->m_FsPANPCBaseData.Find(1);
	}
	/*auto nSize = GGameInstance->SafeGetDataManager()->m_FsPAChapterGroupData.Num();
	for (int i = 0; i < nSize; i++)
	{
		auto data = GGameInstance->SafeGetDataManager()->m_FsPAChapterGroupData.Find(i + 1);
	}*/
	// ...	
}

// Called every frame
void UPAMonsterHeroBaseData::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UPAMonsterHeroBaseData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	DOREPLIFETIME(UPAMonsterHeroBaseData, UnrealCurrentData);
}

void UPAMonsterHeroBaseData::ParseProto3ToUnreal(const proto3::MonsterHeroBaseData& data)
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
	UnrealCurrentData.nStageChange_NextMonsterID = data.nstagechange_nextmonsterid();
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
	UnrealCurrentData.fModelScale = data.fmodelscale();	
	/* 12 */
	UnrealCurrentData.nNPCId = data.nnpcid();
	/* 13 */
	UnrealCurrentData.nTaskID = data.ntaskid();	
	/* 14 */
	UnrealCurrentData.nAvatar = data.navatar();
	/* 15 */
	UnrealCurrentData.nVocation = data.nvocation();
	/* 16 */
	UnrealCurrentData.nEquip_1 = data.nequip_1();
	/* 17 */
	UnrealCurrentData.nEquip_2 = data.nequip_2();
	/* 18 */
	UnrealCurrentData.nEquip_3 = data.nequip_3();
	/* 19 */
	UnrealCurrentData.nEquip_4 = data.nequip_4();
	/* 20 */
	UnrealCurrentData.nEquip_5 = data.nequip_5();
	/* 21 */
	UnrealCurrentData.nEquip_6 = data.nequip_6();
	/* 22 */
	UnrealCurrentData.nEquip_7 = data.nequip_7();
	/* 23 */
	UnrealCurrentData.nEquip_8 = data.nequip_8();
	/* 24 */
	UnrealCurrentData.nWeapon_1 = data.nequip_1();
	/* 25 */
	UnrealCurrentData.nWeapon_2 = data.nequip_2();
	/* 26 */
	UnrealCurrentData.fWalkSpeed = data.fwalkspeed();
	/* 27 */
	UnrealCurrentData.fRunSpeed = data.frunspeed();

	/* 28 */
	UnrealCurrentData.fJumpHeight = data.fjumpheight();
	/* 29 */
	UnrealCurrentData.fBodyConstitution = data.fbodyconstitution();
	/* 30 */
	UnrealCurrentData.fHP = data.fhp();
	/* 31 */
	UnrealCurrentData.fMAX_HP = data.fmax_hp();

	/* 32 */
	UnrealCurrentData.fMP = data.fmp();
	/* 33 */
	UnrealCurrentData.fMAX_MP = data.fmax_mp();

	/* 34 */
	UnrealCurrentData.fArmor = data.farmor();
	/* 35 */
	UnrealCurrentData.fMAX_Armor = data.fmax_armor();

	/* 36 */
	UnrealCurrentData.fNormalAttack = data.fnormalattack();
	/* 37 */
	UnrealCurrentData.fNormalDefend = data.fnormaldefend();

	/* 38 */
	UnrealCurrentData.fDodge = data.fdodge();
	/* 39 */
	UnrealCurrentData.fCrit = data.fcrit();
	/* 40 */
	UnrealCurrentData.fCritHurt = data.fcrithurt();
	/* 41 */
	UnrealCurrentData.fBlock = data.fblock();
	
	/* 42 */
	UnrealCurrentData.fAttackResistance = data.fattackresistance();
	/* 43 */
	UnrealCurrentData.fAttackMulti = data.fattackmulti();
	/* 44 */
	UnrealCurrentData.fSkillTreeId = data.fskilltreeid();
	/* 45 */
	UnrealCurrentData.nIntroductionId = data.nintroductionid();

	/* 46 */
	UnrealCurrentData.PatrolRadius = data.patrolradius();
	/* 47 */
	UnrealCurrentData.WanderDistance = data.wanderdistance();
	/* 48 */
	UnrealCurrentData.HearingRadius = data.hearingradius();
	/* 49 */
	UnrealCurrentData.ChaseRadius = data.chaseradius();
	/* 50 */
	UnrealCurrentData.SprintRadius = data.sprintradius();
}

void UPAMonsterHeroBaseData::InitProto3Data()
{

	// do something... Proto3Data
}

float UPAMonsterHeroBaseData::GetHP()
{
	return UnrealCurrentData.fHP;
}
float UPAMonsterHeroBaseData::GetMaxHP()
{
	return UnrealCurrentData.fMAX_HP;
}
float UPAMonsterHeroBaseData::GetMP()
{
	return UnrealCurrentData.fMP;
}
float UPAMonsterHeroBaseData::GetMaxMP()
{
	return UnrealCurrentData.fMAX_MP;
}
float UPAMonsterHeroBaseData::GetArmor()
{
	return UnrealCurrentData.fArmor;
}
float UPAMonsterHeroBaseData::GetMaxArmor()
{
	return UnrealCurrentData.fMAX_Armor;
}
float UPAMonsterHeroBaseData::GetPower()
{
	return 100;
}
float UPAMonsterHeroBaseData::GetMaxPower()
{
	return 100;
}

void UPAMonsterHeroBaseData::SetHP(float fHP)
{
	UnrealCurrentData.fHP = fHP;
}
void UPAMonsterHeroBaseData::SetMP(float fMP)
{
	UnrealCurrentData.fMP = fMP;
}
void UPAMonsterHeroBaseData::SetArmor(float fArmor)
{
	UnrealCurrentData.fArmor = fArmor;
}
void UPAMonsterHeroBaseData::SetPower(float fPower)
{
	// test postion to do something
}

void UPAMonsterHeroBaseData::ParseCreateBehaviorTree()
{
	if (UnrealCurrentData.nAITreeId != 0)
	{
		auto data = GGameInstance->SafeGetDataManager()->m_ResourcesTable.Find(UnrealCurrentData.nAITreeId);
		auto uoTmp = UPandaUtils::CreateAsset(data->strPath);
		m_UBehaviorTree = Cast<UBehaviorTree>(uoTmp);

		// another create asset way
		//static ConstructorHelpers::FObjectFinder<UBehaviorTree>BasicTree(TEXT("/Game/AI/MonsterBehavior"));
		//m_UBehaviorTree = Cast<UBehaviorTree>(obj);
	}
}

UBehaviorTree* UPAMonsterHeroBaseData::GetBehaviorTree()
{
	return m_UBehaviorTree;
}

/* Create Role BP */
void UPAMonsterHeroBaseData::ParseCreateCharacterBP()
{
	if (UnrealCurrentData.nCharacterBPId != 0)
	{
		auto data = GGameInstance->SafeGetDataManager()->m_ResourcesTable.Find(UnrealCurrentData.nCharacterBPId);
		FString AssetPath = data->strPath;
	}
}

/* Create Anim BP */
void UPAMonsterHeroBaseData::ParseCreateAnimBPClass()
{
	if (UnrealCurrentData.nAnimBPId != 0)
	{
		auto data = GGameInstance->SafeGetDataManager()->m_ResourcesTable.Find(UnrealCurrentData.nAnimBPId);
		FString AssetPath = data->strPath;
		auto uoTmp = UPandaUtils::GetAssetFromPath(AssetPath);
		NewAnimBPClass = uoTmp->GetClass();

		//class UClass* NewClass = uoTmp->GetClass();
		//auto SetAnimInstanceClass(NewClass)
		//SetAnimationMode(EAnimationMode::Type InAnimationMode = AnimationBlueprint/AnimationSingleNode)
	}
}

/* Get Anim BP */
UClass* UPAMonsterHeroBaseData::GetAnimBPClass()
{
	return NewAnimBPClass;
}