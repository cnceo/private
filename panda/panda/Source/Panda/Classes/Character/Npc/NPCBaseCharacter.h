// Fill out your copyright notice in the Description page of Project Settings.
//
//  NPCBaseCharacter.h
//  Panda: NPC Base Class
//  This Obj only can as NPC
//  Created by White.tian on 2016-5-10 11:23:56
//  Copyright (c) 2016Äê White.tian All rights reserved.
//

#pragma once

#include "Character/Monster/MonsterBaseCharacter.h"
#include "NPCBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API ANPCBaseCharacter : public AMonsterBaseCharacter
{
	GENERATED_BODY()

public:
	ANPCBaseCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	/*
	*	NPC: Capsule Collsion  Data
	*/
	virtual void InitCapsuleCollsionData();

	/* NPC: Check Data*/

	/* Check Is Have UAIStaticParamComponent*/
	bool CheckAIParamComponentExist();
	UAIStaticParamComponent* m_AIStaticParamComponent;

	/*Check Is Have TaskId*/
	virtual bool CheckHaveTaskId();
	/*Check Is Need to create task ui, if task_id > 0 (true)*/
	virtual bool CheckNeedToCreateTaskUI();

	/* Check Is NPC */
	virtual bool CheckBNPC();
	/* Check Is Monster*/
	virtual bool CheckBMonster();
	/* Get TaskId*/
	virtual int32 GetTaskId();
	/* Get NpcId*/
	virtual int32 GetNPCId();
};
