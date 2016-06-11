// Fill out your copyright notice in the Description page of Project Settings.
//
//  MainAIController.h
//  Panda
//  
//  Created by White.tian on 2016-4-27 13:44:30
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#pragma once

#include "Components/ActorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PAMonsterHeroBaseData.h"
#include "CommonDefine.h"
#include "AIStaticParamComponent.generated.h"

// COLLSION_TYPE 
namespace PANDA_COLLSION_TYPE {
	enum class COLLSION_TYPE : uint8
	{
		COLLSION_TYPE_BOX = 0,
		COLLSION_TYPE_SPHERE = 1,
		COLLSION_TYPE_CAPSULE = 2,

		COLLSION_TYPE_OTHER,
	};
};
using namespace PANDA_COLLSION_TYPE;
UCLASS( ClassGroup=(Panda_Custom), meta=(BlueprintSpawnableComponent) )
class PANDA_API UAIStaticParamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIStaticParamComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

protected:
	/*
	*	This is NPC Used Param, 
	*	priority: npc > monster.. If this is monster, it's can't be npc again; if this is npc, it's can't be monster again.
	*	bNPC
	*	nNPCId
	*	nTaskId
	*/

	/* Init */
	void InitNpcData();
public:
	
	// This is a npc?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComponentsParam)
	bool bNPC;

	// NPCID:: if bNPC true, nNPCId must be not equal 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|NPC")
	int32 nNPCId;
	
	// TaskID:: if bNPC true, It can have nTaskId.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|NPC")
	int32 nTaskId;

	// Check need to create the task capsule collsion
	void CheckNeedCreateCollsion();
	void CreateCollsion(PANDA_COLLSION_TYPE::COLLSION_TYPE nType);

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* m_BoxComponent;
	class UShapeComponent* m_ShapeComponent;
	class UCapsuleComponent* m_CapsuleComponent;*/


protected:

	/*
	*	This is AI Used Param
	*		
	*	bMonster
	*	SpawnPoint
	*	PatrolRadius
	*	PatrolPaths
	*	WanderDistance
	*	HearingRadius
	*	BehaviorTree
	*	ChaseRadius
	*	SprintRadius
	*	Direction
	*	TargetActor
	*	TargetActorArr
	*	Monster_type
	*/

	/* Init */
	void InitMonsterData();
public:

	// This is a monster?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComponentsParam)
	bool bMonster;

	// spawn point, auto filled 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	FVector SpawnPoint;

	// radius from spawn point for patrol
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float PatrolRadius;

	// paths for patrol, need more than 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	TArray<AActor*> PatrolPaths;

	// max wander distance between 2 steps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float WanderDistance;

	// sensing distance of hearing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float HearingRadius;

	// special behavior tree will been run
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	UBehaviorTree* BehaviorTree;

	// chase area radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float ChaseRadius;

	// sprint distance between target actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float SprintRadius;
	
	// self current direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float Direction;

	// current attack target actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	AActor* TargetActor;
	
	// monster search all monsters array, finally need to filter a monster(desginer need)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	TArray<AActor*> TargetActorArr;

	// monster type, temp data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	CHARACTER_TYPE Monster_type;

	// bOnce Sound Enemy: deafult:false, when
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	int32 nSoundEnemy;

	// ChaseMove?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	bool bChaseMove;

	// AI_Pawn与敌人之间达到下面参数的距离的时候 追击状态为True
	// AI_Pawn self actionLocation between enemy and self distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float CanImplementChaseMoveDistance;

	// 第一次检测是否可以达到追击条件的距离值
	// The first time check is can reach chase condition's distance value 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComponentsParam|Monster")
	float FirstCheckPatrolDistance;
};