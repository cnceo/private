// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PlayerCharacter.h"
#include "AttachObjBase.h"
#include "AttachWeapon.h"
#include "Utils/PandaUtils.h"
#include "PandaGameInstance.h"
#include "PandaWidget_Talk2Npc.h"
#include "MonsterBaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainPlayerController.h"
#include "PAWidget_Dungeon_Chapter.h"


class UWorld;
class AAttachObjBase;
class AAttachWeapon;
class UEngine;

APlayerCharacter::APlayerCharacter()
	: m_nMaxJumpNum(2) 
	, m_nJumpCount(2)
	, TargetNPC(nullptr)
{
	m_emType = CHARACTER_TYPE::CHARACTER_TYPE_PLAYER;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	JumpMaxHoldTime = 0.2f;
	setMaxWalkSpeed(350);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom,USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	m_QuestHandler = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
	if (m_QuestHandler)
	{
		m_QuestHandler->SetNetAddressable();
		m_QuestHandler->SetIsReplicated(true);
	}
	bReplicates = true;
	
	// Add UserHeroBase data
	BaseDataComponent = CreateDefaultSubobject<UPAUserHeroBaseData>(TEXT("UserBaseDataComponent"));
}

APlayerCharacter::~APlayerCharacter()
{

}

bool APlayerCharacter::SetState_Validate(CHARACTER_SUB_STATE emSubState, CHARACTER_STATE emState)
{
	return true;
}

void APlayerCharacter::SetState_Implementation(CHARACTER_SUB_STATE emSubState, CHARACTER_STATE emState)
{
	if (m_bFighting && emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL)
	{
		emState = CHARACTER_STATE::CHARACTER_STATE_STAND;
		emSubState = CHARACTER_SUB_STATE::SUB_STATE_FIGHTING;
	}

	if (emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL)
	{
		SetPoseTimer();
	}

	if (emSubState != CHARACTER_SUB_STATE::SUB_STATE_NONE && m_emSubState != emSubState)
		m_emSubState = emSubState;

	if (emState != CHARACTER_STATE::CHARACTER_STATE_NONE && m_emState != emState)
		m_emState = emState;
}

void APlayerCharacter::setMaxWalkSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void APlayerCharacter::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetPoseTimer();
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_ATTACK, AppendSkill(1));
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_CHASE, AppendSkill(2));
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_SKYATTACK, AppendSkill(4));
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP1, AppendSkill(11));
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP2, AppendSkill(12));
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP3, AppendSkill(13));
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP4, AppendSkill(14));

	GetCapsuleComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &APlayerCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.RemoveDynamic(this, &APlayerCharacter::OnEndOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);
}

void APlayerCharacter::OnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other != NULL && OtherComp != NULL)
	{
		auto DisplayName = UKismetSystemLibrary::GetDisplayName(Other);

		// 撞击MainScene里面的传送门
		if (DisplayName == "TriggerVolume_chuansongmen01")
		{
			// do once
			// static bool bUIExsit = true;
			if (GGameInstance)
			{
				// 调用接口_调用打开武馆的接口
				FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_Club);
			}
		}
		// 主城区域里面的MainCity,撞击后进入中间区域
		else if (DisplayName == "TriggerVolume_MainCity")
		{
			// 谈出UI,选择去往哪一个中间区域
			if (GGameInstance)
			{
				auto controller = UPandaUtils::GetLocalPlayerController(GGameInstance);
				if (controller) {
					auto mainController = Cast<AMainPlayerController>(controller);
					if (mainController){
						// 打开中间区域界面
						mainController->OnOpenSelectRegion();
					}
				}
			}
		}
		// 中间区域的Trigger,触发通往不同的副本
		else if(DisplayName == "TriggerVolume_chuansongmen1" || DisplayName == "TriggerVolume_chuansongmen2"
			|| DisplayName == "TriggerVolume_chuansongmen3" || DisplayName == "TriggerVolume_chuansongmen4"){
			if (GGameInstance)
			{
				auto controller = UPandaUtils::GetLocalPlayerController(GGameInstance);
				if (controller) {
					auto mainController = Cast<AMainPlayerController>(controller);
					if (mainController)
						mainController->OnOpenACT();
				}
				
				/*auto ACTWidget = (GGameInstance->SafeGetUIManager()->FindInWidgetCache(UI_Dungeon_ACT));
				if (ACTWidget)
				{
					auto obj = Cast<UPAWidget_Dungeon_Chapter>(ACTWidget);
					obj->m_nCurrentDungeonGroupID = 1;
				}*/
			}
		}
	}
}

void APlayerCharacter::OnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other != NULL && OtherComp != NULL)
	{
		auto DisplayName = UKismetSystemLibrary::GetDisplayName(Other);
		if (DisplayName == "TriggerVolume_chuansongmen01")
		{
			// do once
			// static bool bUIExsit = true;
		}
	}
}

ASkillIInstance* APlayerCharacter::GetBaseSkill(PLAYER_SKILL_TYPE emType)
{ 
	auto pSkill = m_mapBaseSkill.Find(emType);
	if (pSkill)
		return *pSkill;

	return nullptr;
}
bool APlayerCharacter::CheckTarget(ABaseCharacter* start, AActor* target, float& fDistance, float& fAngle)
{
	fDistance = target->GetDistanceTo(start);
	if (fDistance > 1000) return false;
	FVector distance = target->GetActorLocation() - start->GetActorLocation();
	FVector direction = start->GetCapsuleComponent()->GetForwardVector();
	fAngle = UPandaUtils::VectorAngle(direction, distance);
	if (FMath::Abs(fAngle) > 75) return false;
	return true;
}

ABaseCharacter* APlayerCharacter::FindTarget(float fAxis)
{
	ABaseCharacter* pCurTarget = GetTarget();
	ABaseCharacter* pNewTarget = pCurTarget;
	float fCurDistance = 0;
	if (pCurTarget != nullptr) fCurDistance = pCurTarget->GetDistanceTo(this);
	float fCurAngle = 75;
	if (fAxis > 0) fCurAngle = -75;
	//遍历关卡内全部BaseCharacter
	for (auto it = GetWorld()->GetPawnIterator(); it; ++it) 
	{
		if (auto pPawn = (*it)) 
		{
			if (auto pActor = Cast<ABaseCharacter>(pPawn))
			{
				//没有目标时,先设置第1个符合锁定规则的目标
				if (!pNewTarget)
				{			
					float fDistance = 0;
					float fAngle = 0;
					if (this->CheckTarget(this, pActor, fDistance, fAngle))
					{
						pNewTarget = pActor;
						fCurDistance = fDistance;
					}		
				}
				//有目标后,进行比较.(此部分功能未完整实现)
				else
				{
					//如果当前已经处于索敌模式.再次索敌被认为是素敌切换
					if (pCurTarget)
					{
						float fDistance = 0;
						float fAngle = 0;
						//根据右摇杆的左/右输入，找出距离当前目标左/右最近的其他目标
						if (pCurTarget != pActor && this->CheckTarget(this, pActor, fDistance, fAngle) && fAxis != 0.0f)
						{
							if (fAxis > 0 && fAngle < 0 && fAngle > fCurAngle)
							{
								pNewTarget = pActor;
								fCurDistance = fDistance;
								fCurAngle = fAngle;
							}
							else if (fAxis < 0 && fAngle > 0 && fAngle < fCurAngle)
							{
								pNewTarget = pActor;
								fCurDistance = fDistance;
								fCurAngle = fAngle;
							}
						}
					}
					//寻找出距离主角最近的目标
					else
					{
						float fDistance = 0;
						float fAngle = 0;
						if (this->CheckTarget(this, pActor, fDistance, fAngle) && fDistance < fCurDistance)
						{
							pNewTarget = pActor;
							fCurDistance = fDistance;
						}
					}
				}
			}
		}
	}
	return pNewTarget;
}

void APlayerCharacter::TurnAtTarget()
{
	if (!HasTarget()) return;
	if (GetTarget()->GetState() == CHARACTER_STATE::CHARACTER_STATE_DIE || GetTarget()->IsPendingKill())
	{
		ClearTarget();
		return;
	}
	FVector distance = GetTarget()->GetActorLocation() - this->GetActorLocation();
	FVector direction = this->GetCapsuleComponent()->GetForwardVector();
	float fAngle = UPandaUtils::VectorAngle(direction, distance);
	if (FMath::Abs(fAngle) < 1.0f) return;
	FRotator ActorRotation = this->GetActorRotation();
	ActorRotation.Yaw -= fAngle;
	ActorRotation.Normalize();
	this->SetActorRotation(ActorRotation);

}

void APlayerCharacter::AcceptQuest(int id)
{
	if (m_QuestHandler)
	{
		m_QuestHandler->Rpc2ServerAccept(id);
	}

}

void APlayerCharacter::UpdateQuest(int taskId)
{
	if (m_QuestHandler)
	{
		m_QuestHandler->Rpc2ServerUpdate(taskId);
	}

}

void APlayerCharacter::CommitQuest(int taskId)
{
	if (m_QuestHandler )
	{
		// 暂时不做判断
		m_QuestHandler->Rpc2ServerCommit(taskId);
	}
}

// 获得奖励
void APlayerCharacter::AcquireQuestReward(int taskId)
{
	if (GGameInstance != nullptr)
	{
		FsTaskInfo* taskInfo = GGameInstance->SafeGetDataManager()->m_FsTaskInfo.Find(taskId);
		taskInfo->RewardEXP;
		taskInfo->RewardGold;
	}
}

void APlayerCharacter::OpenTaskPanel()
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		gameInstance->SafeGetUIManager()->OpenUMGAsset(UMGAssetPath_AcceptTask);
	}
}

void APlayerCharacter::CloseTaskPanel()
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		gameInstance->SafeGetUIManager()->CloseUMGAsset(UMGAssetPath_AcceptTask);
	}
}

void APlayerCharacter::Talk2Npc()
{
	if (TargetNPC == nullptr)
		return;

	//镜头切换
	APlayerController* cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
	UPACameraManager* pac = UPACameraManager::GetCameraManagerInstance();
	pac->PlayTaskCameraAnim(TargetNPC->GetRootComponent());

	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		GetQuestHandler()->FindNPC(TargetNPC->GetNPCId());

		class UPandaWidget_Talk2Npc* NPCTalk;
		if (gameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_NPCTalk) == nullptr)
		{
			gameInstance->SafeGetUIManager()->OpenUMGAsset(UMGAssetPath_NPCTalk);
			NPCTalk = Cast<UPandaWidget_Talk2Npc>(gameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_NPCTalk));
			NPCTalk->InitTalk2NPC(TargetNPC->GetNPCId(), this, TargetNPC);
			GetQuestHandler()->FindNPC(TargetNPC->GetNPCId());

			// 新的读表方式
			//UObject *Object = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(UMGAssetPath_NPCTalk);
			//class UPandaWidget_Talk2Npc* NPCTalk = Cast<UPandaWidget_Talk2Npc>(FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(Object));
		}
		NPCTalk = Cast<UPandaWidget_Talk2Npc>(gameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_NPCTalk));
		if (NPCTalk->GetVisibility() == ESlateVisibility::Visible)
			return;

		NPCTalk->InitTalk2NPC(TargetNPC->GetNPCId(), this,TargetNPC);
		NPCTalk->SetVisibility(ESlateVisibility::Visible);
		NPCTalk->AddToViewport();	
	}
}

void APlayerCharacter::LeaveNpc(int npcId)
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		gameInstance->SafeGetUIManager()->CloseUMGAsset(UMGAssetPath_NPCTalk);
	}
}

bool APlayerCharacter::CanJumpInternal_Implementation() const
{
	const bool bCanHoldToJumpHigher = (GetJumpMaxHoldTime() > 0.0f) && IsJumpProvidingForce();
	return !bIsCrouched && GetCharacterMovement() && (GetCharacterMovement()->IsMovingOnGround() || bCanHoldToJumpHigher) && GetCharacterMovement()->IsJumpAllowed() && !GetCharacterMovement()->bWantsToCrouch;
}

bool APlayerCharacter::IsJumpProvidingForce() const
{
	if(m_emState == CHARACTER_STATE::CHARACTER_STATE_FALLING && (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_JUMP || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_JUMP2))
	{
		if (JumpKeyHoldTime > 0.0f && JumpKeyHoldTime < GetJumpMaxHoldTime())
		{
			return true;
		}
	}
	return false;
}

void APlayerCharacter::OnJump(bool bJump)
{
	if (bJump)
	{
		if (!ChangeStateToJump())
		{
			return;
		}

		if (m_nJumpCount > 0)
		{
			bPressedJump = true;
			JumpKeyHoldTime = 0.0f;
			m_nJumpCount = m_nJumpCount - 1;
		}
		SetJumpHoldTimer();
	}
	else
	{
		bPressedJump = false;
		JumpKeyHoldTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(m_JumpHoldTimerHandle);
	}


}

void APlayerCharacter::SetJumpHoldTimer()
{
	FTimerDelegate HoldTimer;
	HoldTimer.BindUObject(this, &APlayerCharacter::JumpHoldTimerCallback);
	GetWorld()->GetTimerManager().SetTimer(m_JumpHoldTimerHandle, HoldTimer, JumpMaxHoldTime, false);
}

void APlayerCharacter::JumpHoldTimerCallback()
{
	bPressedJump = false;
}

void APlayerCharacter::ClearJumpInput()
{
	if (GetCharacterMovement()->IsFalling())
	{
		//UE_LOG(LogTemp, Warning, TEXT("GetCharacterMovement()->Velocity=%f"), GetCharacterMovement()->Velocity.Z);
		if (m_emState != CHARACTER_STATE::CHARACTER_STATE_FALLING)
		{
			if (m_emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL || m_emState == CHARACTER_STATE::CHARACTER_STATE_STAND || m_emState == CHARACTER_STATE::CHARACTER_STATE_ACTION)
			{
				SetState(CHARACTER_SUB_STATE::SUB_STATE_FALL, CHARACTER_STATE::CHARACTER_STATE_FALLING);
			}
		}

		if (m_emState == CHARACTER_STATE::CHARACTER_STATE_FALLING)
		{
			if (GetCharacterMovement()->Velocity.Z < 5.0f)
			{
				if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_JUMP2)
				{
					GetCharacterMovement()->GravityScale = 20.f;
				}
				else //if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_JUMP)
				{
					GetCharacterMovement()->GravityScale = 8.f;
				}
			}
		}
	}

}

void APlayerCharacter::OnDelayJumpGround()
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_FALLING)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_NORMAL);
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	m_nJumpCount = m_nMaxJumpNum;
	GetCharacterMovement()->GravityScale = 1.f;
	JumpMaxHoldTime = 0.2f;
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	FTimerDelegate DestroyTimer;
	DestroyTimer.BindUObject(this, &APlayerCharacter::OnDelayJumpGround);
	GetWorld()->GetTimerManager().SetTimer(m_JumpGroundTimerHandle, DestroyTimer, 0.3f, false);
}

void APlayerCharacter::SetFightingTimer()
{
	FTimerDelegate FightingTimer;
	FightingTimer.BindUObject(this, &APlayerCharacter::FightingTimerCallback);
	GetWorld()->GetTimerManager().SetTimer(m_FightingTimerHandle, FightingTimer, 6.0f, false);
	m_bFighting = true;
}

void APlayerCharacter::FightingTimerCallback()
{
	m_bFighting = false;
	if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_FIGHTING)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_NORMAL);
	}
}

void APlayerCharacter::SetPoseTimer()
{
	FTimerDelegate PoseTimer;
	PoseTimer.BindUObject(this, &APlayerCharacter::PoseTimerCallback);
	GetWorld()->GetTimerManager().SetTimer(m_PoseTimerHandle, PoseTimer, 20.0f, false);
}

void APlayerCharacter::PoseTimerCallback()
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL)
	{
		float fRand = FMath::FRand();
		CHARACTER_SUB_STATE emPose(CHARACTER_SUB_STATE::SUB_STATE_POSE1);

		if (fRand > 0.5f)
			emPose = CHARACTER_SUB_STATE::SUB_STATE_POSE2;

		SetState(emPose, CHARACTER_STATE::CHARACTER_STATE_STAND);
	}
}

bool APlayerCharacter::ChangeStateToJump()
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL || m_emState == CHARACTER_STATE::CHARACTER_STATE_STAND || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_MOVE)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_JUMP, CHARACTER_STATE::CHARACTER_STATE_FALLING);
		GetCharacterMovement()->GravityScale = 1.5f;
		return true;
	} 
	else if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_JUMP)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_JUMP2, CHARACTER_STATE::CHARACTER_STATE_FALLING);
		GetCharacterMovement()->GravityScale = 1.0f;
		JumpMaxHoldTime = 0.05f;
		GetCharacterMovement()->JumpZVelocity = 800.0f;
		return true;
	}

	return false;
}

bool APlayerCharacter::ChangeStateToMove()
{
	if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_MOVE)
		return true;

	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL || m_emState == CHARACTER_STATE::CHARACTER_STATE_STAND)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_MOVE, CHARACTER_STATE::CHARACTER_STATE_ACTION);
		return true;
	}

	return false;
}

bool APlayerCharacter::ChangeStateToDodge()
{
	return false;
}

bool APlayerCharacter::ChangeStateToDefence()
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL || m_emState == CHARACTER_STATE::CHARACTER_STATE_STAND || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_MOVE)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_DEFENCE, CHARACTER_STATE::CHARACTER_STATE_ACTION);
		return true;
	}
	else if (m_emState == CHARACTER_STATE::CHARACTER_STATE_SKILL && GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		if (GetCurSkill() && GetCurSkill()->IsBeFuse())
		{
			GetCurSkill()->BreakSkill(false);
			SetState(CHARACTER_SUB_STATE::SUB_STATE_DEFENCE, CHARACTER_STATE::CHARACTER_STATE_ACTION);
			return true;
		}
	}

	return false;
}

void APlayerCharacter::ClearDefence()
{
	if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_DEFENCE)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_NORMAL);
	}
}

bool APlayerCharacter::PlaySkillInstance(ASkillIInstance* pSkill)
{
	bool bPlay = Super::PlaySkillInstance(pSkill);
	if (bPlay)
	{
		TurnAtTarget();
		SetFightingTimer();
	}

	return bPlay;
}

void APlayerCharacter::SetPlayerInfo(FsPAPlayerInfo PlayerInfo)
{
	FPlayerDataManager::Instance()->setPlayerInfo(PlayerInfo);
}

FsPAPlayerInfo APlayerCharacter::GetPlayerInfo()
{
	return FPlayerDataManager::Instance()->getPlayerInfo();
}

void APlayerCharacter::SetPlaceInfo(FsPAPlaceInfo PlaceInfo)
{
	FPlayerDataManager::Instance()->setPlaceInfo(PlaceInfo);
}

FsPAPlaceInfo APlayerCharacter::GetPlaceInfo()
{
	return FPlayerDataManager::Instance()->getPlaceInfo();
}

void APlayerCharacter::SetPlayerExtraInfo(FsPAPlayerExtraInfo PlayerExtraInfo)
{
	FPlayerDataManager::Instance()->setPlayerExtraInfo(PlayerExtraInfo);
}

FsPAPlayerExtraInfo APlayerCharacter::GetPlayerExtraInfo()
{
	return FPlayerDataManager::Instance()->getPlayerExtraInfo();
}