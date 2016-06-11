// Fill out your copyright notice in the Description page of Project Settings.
//  Created by yang 玩家角色类
#pragma once

#include "BaseCharacter.h"
#include "SkillIInstance.h"
#include "System/Quest/QuestComponent.h"
#include "PAUserData.h"
#include "PandaPlayerState.h"
#include "PlayerCharacter.generated.h"



/**
 * 
 */
UCLASS(HideDropdown)
class PANDA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	~APlayerCharacter();
public:
	/** User Base Data component used for record player data(hp, mp, etc). */
	UPROPERTY(Category = PlayerCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPAUserHeroBaseData* BaseDataComponent;

public:
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)override;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "MainPlayer")
	virtual void SetState(CHARACTER_SUB_STATE emSubState, CHARACTER_STATE emState = CHARACTER_STATE::CHARACTER_STATE_NONE) override;

	UFUNCTION(BlueprintCallable, Category = "MainPlayer")
	virtual bool PlaySkillInstance(ASkillIInstance* pSkill);

	UFUNCTION()
	virtual void OnBeginOverlap( AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void  BeginPlay() override;

	//改变主角移动速度
	UFUNCTION(BlueprintCallable,Category = "MainPlayer")
	void setMaxWalkSpeed(float speed);

	//select target
	UFUNCTION(BlueprintCallable, Category = "MainPlayer")
	ABaseCharacter* FindTarget(float fAxis = 0.0f);

	//check a actor by character 
	UFUNCTION(BlueprintCallable, Category = "MainPlayer")
	bool CheckTarget(ABaseCharacter* start, AActor* target, float& fDistance, float& fAngle);

	UFUNCTION(BlueprintCallable, Category = "MainPlayer")
	void TurnAtTarget();

	UFUNCTION(BlueprintCallable, Category = "MainPlayer")
	ASkillIInstance* GetBaseSkill(PLAYER_SKILL_TYPE emType);


	//改变状态到跳跃
	bool ChangeStateToJump();

	//改变状态到行走
	bool ChangeStateToMove();

	//改变状态到闪避
	bool ChangeStateToDodge();

	//改变状态到防御
	bool ChangeStateToDefence();

	//清除防御效果
	void ClearDefence();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Camera,meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera Normail behavior*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Camera,meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

private:

	//基础攻击技能
	TMap<PLAYER_SKILL_TYPE, ASkillIInstance*> m_mapBaseSkill;

//******Quest
public:
	//this to handle Quest
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	class UQuestComponent*  m_QuestHandler;

	//request server get quest
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AcceptQuest(int id);
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateQuest(int taskId);
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CommitQuest(int taskId);
	// 获得任务奖励
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AcquireQuestReward(int taskId);
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void OpenTaskPanel();
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CloseTaskPanel();
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void Talk2Npc();
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void LeaveNpc(int npcId);

	class AMonsterBaseCharacter* TargetNPC;
	class UQuestComponent* GetQuestHandler() const;

	//////////////////////////////////////////////////////////////////////////
	// 武馆相关
	UFUNCTION(BlueprintCallable, Category = "Club")
	class UMartialclubData* GetMartialclub() const;
	UFUNCTION(BlueprintCallable, Category = "Club")
	void SetMartialclub(UMartialclubData* inData) ;


//******Jump define
public:
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void OnJump(bool bJump);
	virtual void OnDelayJumpGround();
protected:
	bool IsJumpProvidingForce() const;
	void ClearJumpInput();
	void SetJumpHoldTimer();
	void JumpHoldTimerCallback();
	int32 m_nMaxJumpNum;	//max jump count
	int32 m_nJumpCount;	//cur jump count
	FTimerHandle m_JumpHoldTimerHandle;
	FTimerHandle m_JumpGroundTimerHandle;

	FTimerHandle m_FightingTimerHandle;
	void SetFightingTimer();
	void FightingTimerCallback();

	FTimerHandle m_PoseTimerHandle;
	void SetPoseTimer();
	void PoseTimerCallback();

public:
	/*
	*	Player Data
	*	
	*	member: PlayerInfoData, like playerLevel, playerExp...
	*	member: PlaceInfoData,	like last_place_x_y_z
	*	member: PlayerExtraInfoData, like...
	*/

	// GetPlayerInfo, SetPlayerInfo
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	FsPAPlayerInfo GetPlayerInfo();
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	void SetPlayerInfo(FsPAPlayerInfo PlayerInfo);

	// GetPlaceInfo, SetPlaceInfo
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	FsPAPlaceInfo GetPlaceInfo();
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	void SetPlaceInfo(FsPAPlaceInfo PlaceInfo);

	// GetPlayerExtraInfo, SetPlayerExtraInfo
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	FsPAPlayerExtraInfo GetPlayerExtraInfo();
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	void SetPlayerExtraInfo(FsPAPlayerExtraInfo PlayerExtraInfo);

	APandaPlayerState* GetPlayerState() const
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			APandaPlayerState* PlayerState = Cast<APandaPlayerState>(PC->PlayerState);
			if (PlayerState)
			{
				return PlayerState;
			}
		}
		return nullptr;
	};
};

//FORCEINLINE class APandaPlayerState* APlayerCharacter::GetPlayerState() const
//{
//	APlayerController* PC = Cast<APlayerController>(GetController());
//	if (PC)
//	{
//		APandaPlayerState* PlayerState = Cast<APandaPlayerState>(PC->PlayerState);
//		if (PlayerState)
//		{
//			return PlayerState;
//		}
//	}
//
//	return nullptr;
//}

FORCEINLINE class UQuestComponent* APlayerCharacter::GetQuestHandler() const 
{ 
	return m_QuestHandler; 
}

FORCEINLINE class UMartialclubData* APlayerCharacter::GetMartialclub() const
{
	if (GetPlayerState())
	{
		if (Cast<APandaPlayerState>(GetPlayerState()))
		{ 
			return GetPlayerState()->Martialclub;
		}
	}

	return nullptr;
}
FORCEINLINE void APlayerCharacter::SetMartialclub(UMartialclubData* inData)
{
	if (GetPlayerState())
	{
		if (Cast<APandaPlayerState>(GetPlayerState()))
		{
			GetPlayerState()->Martialclub = inData;
		}
	}
}