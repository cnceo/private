// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "AIStaticParamComponent.h"


// Sets default values for this component's properties
UAIStaticParamComponent::UAIStaticParamComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	InitNpcData();
	InitMonsterData();
	// ...
}

// Called when the game starts
void UAIStaticParamComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAIStaticParamComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UAIStaticParamComponent::InitNpcData()
{
	bNPC = false;
	nNPCId = 0;
	nTaskId = 0;
}

// Check need to create the task capsule collsion
void UAIStaticParamComponent::CheckNeedCreateCollsion()
{
	
}
void UAIStaticParamComponent::CreateCollsion(COLLSION_TYPE nType)
{
	switch (nType)
	{
	case COLLSION_TYPE::COLLSION_TYPE_BOX:
	{

	}break;
	case COLLSION_TYPE::COLLSION_TYPE_SPHERE:
	{

	}break;
	case COLLSION_TYPE::COLLSION_TYPE_CAPSULE:
	{

	}break;
	default:
		break;
	}
}

void UAIStaticParamComponent::InitMonsterData()
{
	bMonster = false;
	SpawnPoint = FVector::ZeroVector;
	PatrolRadius = 0.f;
	PatrolPaths.Reset(0);
	WanderDistance = 0.f;
	HearingRadius = 0.f;
	BehaviorTree = nullptr;
	ChaseRadius = 0.f;
	SprintRadius = 0.f;
	Direction = 0.f;
	TargetActor = nullptr;
	TargetActorArr.Reset(0);
	Monster_type = CHARACTER_TYPE::CHARACTER_TYPE_NONE;

	// 0,1,2   ---->   0:自己巡逻/1:开始发现目标/2:发现目标完成
	nSoundEnemy = 0;
	// 是否是追击状态
	bChaseMove = false;
	// The first time check is can reach chase condition's distance value /*第一次检测是否可以达到追击条件的距离值*/
	FirstCheckPatrolDistance = 0.f;
	// AI_Pawn self actionLocation between enemy and self distance 与敌人之间达到下面参数的距离的时候 追击状态为True
	CanImplementChaseMoveDistance = 0.f;
}