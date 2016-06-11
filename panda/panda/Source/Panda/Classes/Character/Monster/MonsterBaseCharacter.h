// Fill out your copyright notice in the Description page of Project Settings.
//
//  NPCBaseCharacter.h
//  Panda: Monster Base Class
//  This Obj Can as Monster, also can as NPC
//  Created by White.tian on 2016-4-28 11:17:21
//  Copyright (c) 2016年 White.tian All rights reserved.
//
#pragma once

#include "BaseCharacter.h"
#include "PAMonsterHeroBaseData.h"
#include "AIStaticParamComponent.h"
#include "MonsterBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API AMonsterBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Anim Begin notify
	// fTime = fTotalTime
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnAnimBegin_BP(float fTime, const FString& AnimName);

	// Anim Tick notify
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnAnimTick_BP(float fTime, const FString& AnimName);
	
	// Anim end notify
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnAnimEnd_BP(const FString& AnimName);
	
	// Current Anim time
	float fCurrentAnimTime;

	// Get Current Anim time
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	float GetCurrentAnimationTime();
public:
	AMonsterBaseCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	/** User Base Data component used for record player data(hp, mp, etc). */
	UPROPERTY(Category = PlayerCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPAMonsterHeroBaseData* BaseDataComponent;

public:
	/*
	*	Character State/Battle Model
	*/

	/*
	*	Desc: Character State: Change State Check
	*
	*	Func: ChangeStateToJump()
	*	Func: ChangeStateToMove()
	*	Func: ChangeStateToDodge()
	*	Func: ChangeStateToDefence()
	*	...
	*/
	//改变状态到跳跃
	UFUNCTION(BlueprintCallable, Category = "MonsterChangeState")
	bool ChangeStateToJump();

	//改变状态到行走
	UFUNCTION(BlueprintCallable, Category = "MonsterChangeState")
	bool ChangeStateToMove();

	//改变状态到闪避
	UFUNCTION(BlueprintCallable, Category = "MonsterChangeState")
	bool ChangeStateToDodge();

	//改变状态到防御
	UFUNCTION(BlueprintCallable, Category = "MonsterChangeState")
	bool ChangeStateToDefence();

	/*
	*	Battle Model: Monster Attack
	*/

	/* Load Used Skill, maybe this way is temp*/
	void LoadSkill();

	//播放当前技能的下一连招
	UFUNCTION(BlueprintCallable, Category = "MonsterBaseCharacter")
	virtual bool PlaySkillInstanceNextAtom(ASkillIInstance* pSkill = nullptr);

	UFUNCTION(BlueprintCallable, Category = "MonsterBaseCharacter")
	ASkillIInstance* GetBaseSkill(PLAYER_SKILL_TYPE emType);

	UFUNCTION(BlueprintCallable, Category = "MonsterBaseCharacter")
	virtual void PauseAI();

	UFUNCTION(BlueprintCallable, Category = "MonsterBaseCharacter")
	virtual void RestartAI();

private:

	//基础攻击技能
	TMap<PLAYER_SKILL_TYPE, ASkillIInstance*> m_mapBaseSkill;

public:

	/* Parse BaseDataComponent, Like, IsNpc? IsMonster? IsPartner? */
	void ParseBaseDataComponent();
	void ParseType();
public:
	/*
	*	NPC: Capsule Collsion  Data
	*/
	virtual void InitCapsuleCollsionData();

	/**
	 * Position of the last actor to enter the collision cylinder.
	 * This currently does not handle multiple actors affecting the foliage simultaneously.
	 */
	 /*UPROPERTY(transient)
	 FVector TouchingActorEntryPosition;*/
	
	UFUNCTION()
	virtual void OnBeginOverlap( AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
