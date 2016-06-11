// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "MonsterBaseCharacter.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PandaUtils.h"

AMonsterBaseCharacter::AMonsterBaseCharacter()
{
	// Create monster base data component
	BaseDataComponent = CreateDefaultSubobject<UPAMonsterHeroBaseData>(TEXT("MonsterBaseDataComponent"));
	
	// Init
	InitCapsuleCollsionData();

	// ...
}

void AMonsterBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Skill
	LoadSkill();

	// parse
	//ParseBaseDataComponent();

	// check
	bool bHadAIComponent = this->CheckAIParamComponentExist();
	bool bCreateTaskUI = this->CheckNeedToCreateTaskUI();

	// if create true, init_capsule_size and building beginOverlap event
	if (bCreateTaskUI)
	{
		GetCapsuleComponent()->SetCapsuleSize(80.0, 80.0);
		// Ensure delegate is bound (just once)
		GetCapsuleComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &AMonsterBaseCharacter::OnBeginOverlap);
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonsterBaseCharacter::OnBeginOverlap);
		GetCapsuleComponent()->OnComponentEndOverlap.RemoveDynamic(this, &AMonsterBaseCharacter::OnEndOverlap);
		GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMonsterBaseCharacter::OnEndOverlap);
	}
}

void AMonsterBaseCharacter::LoadSkill()
{
	// Add Skill
	m_mapBaseSkill.Add(PLAYER_SKILL_TYPE::PLAYER_SKILL_ATTACK, AppendSkill(3));
}

// Called to bind functionality to input
void AMonsterBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMonsterBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMonsterBaseCharacter::OnAnimTick_BP(float fTime, const FString& AnimName)
{
	Execute_OnAnimTick(this, fTime, AnimName);
}

void AMonsterBaseCharacter::OnAnimBegin_BP(float fTime, const FString& AnimName)
{
	fCurrentAnimTime = fTime;

	//// Need to Pause AI When Have NotifyState Anim
	//UPandaUtils::PauseAI(fTime, this, this);

	Execute_OnAnimBegin(this, fTime, AnimName);
}

void AMonsterBaseCharacter::OnAnimEnd_BP(const FString& AnimName)
{
	fCurrentAnimTime = 0;
	Execute_OnAnimEnd(this, AnimName);
}

float AMonsterBaseCharacter::GetCurrentAnimationTime()
{
	return fCurrentAnimTime;
}

void AMonsterBaseCharacter::InitCapsuleCollsionData()
{
	/*TouchingActorEntryPosition = FVector::ZeroVector;*/
}

void AMonsterBaseCharacter::OnBeginOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other != NULL && OtherComp != NULL)
	{
		auto OtherName = Other->GetClass();
		if (OtherName->GetName() == "Player_Blueprint_C")
		{
			// do once
			// static bool bUIExsit = true;
			Cast<APlayerCharacter>(Other)->TargetNPC = this;
		}
		//UCapsuleComponent* const TouchingActorCapsule = Cast<UCapsuleComponent>(OtherComp);
		//if (TouchingActorCapsule && GetCapsuleComponent())
		//{
		//	const FVector CenterToTouching = FVector(TouchingActorCapsule->Bounds.Origin.X, TouchingActorCapsule->Bounds.Origin.Y, GetCapsuleComponent()->Bounds.Origin.Z) - GetCapsuleComponent()->Bounds.Origin;
		//	// Keep track of the first position on the collision cylinder that the touching actor intersected
		//	//@todo - need to handle multiple touching actors
		//	TouchingActorEntryPosition = GetRootComponent()->Bounds.Origin + CenterToTouching.GetSafeNormal() * GetCapsuleComponent()->GetScaledCapsuleRadius();
		//}
		//// Bring this actor out of stasis so that it gets ticked now that a force has been applied
		//SetActorTickEnabled(true);
	}
}

void AMonsterBaseCharacter::OnEndOverlap(AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other != NULL && OtherComp != NULL)
	{
		auto OtherName = Other->GetClass();
		if (OtherName->GetName() == "Player_Blueprint_C")
		{
			// do once
			// static bool bUIExsit = true;
			Cast<APlayerCharacter>(Other)->TargetNPC = nullptr;
		}
	}
}

bool AMonsterBaseCharacter::CheckAIParamComponentExist()
{
	if (!m_AIStaticParamComponent)
	{
		m_AIStaticParamComponent = Cast<UAIStaticParamComponent>(GetComponentByClass(UAIStaticParamComponent::StaticClass()));
		if (m_AIStaticParamComponent)
		{
			return true;
		}
		return false;
	}
	return true;
}

bool AMonsterBaseCharacter::CheckHaveTaskId()
{
	if (CheckBNPC() && GetNPCId() > 0 && GetTaskId() > 0)
	{
		return true;
	}
	return false;
}

bool AMonsterBaseCharacter::CheckNeedToCreateTaskUI()
{
	if (CheckHaveTaskId())
	{
		return true;
	}
	return false;
}

bool AMonsterBaseCharacter::CheckBNPC()
{
	if (m_AIStaticParamComponent)
	{
		bool bNpcTemp = m_AIStaticParamComponent->bNPC;
		return bNpcTemp;
	}
	return false;
}

bool AMonsterBaseCharacter::CheckBMonster()
{
	if (m_AIStaticParamComponent)
	{
		bool bMonsterTemp = m_AIStaticParamComponent->bMonster;
		return bMonsterTemp;
	}
	return false;
}

int32 AMonsterBaseCharacter::GetTaskId()
{
	if (m_AIStaticParamComponent)
	{
		return m_AIStaticParamComponent->nTaskId;
	}
	return 0;
}

int32 AMonsterBaseCharacter::GetNPCId()
{
	if (m_AIStaticParamComponent)
	{
		return m_AIStaticParamComponent->nNPCId;
	}
	return 0;
}

void AMonsterBaseCharacter::ParseBaseDataComponent()
{
	ParseType();
}

void AMonsterBaseCharacter::ParseType()
{
	switch (BaseDataComponent->UnrealCurrentData.nType)
	{
	case 1:
	case 2:
	case 3:
		//1ÆÕÍ¨
		//2¾«Ó¢
		//3BOSS
		{
			CheckAIParamComponentExist();
			if (m_AIStaticParamComponent)
			{
				// set NPC data	false
				m_AIStaticParamComponent->bNPC = false;

				// set Monster data true
				m_AIStaticParamComponent->bMonster = true;
				m_AIStaticParamComponent->SpawnPoint = FVector::ZeroVector;
				m_AIStaticParamComponent->PatrolRadius = BaseDataComponent->UnrealCurrentData.PatrolRadius;
				m_AIStaticParamComponent->PatrolPaths.Reset(0);
				m_AIStaticParamComponent->WanderDistance = BaseDataComponent->UnrealCurrentData.WanderDistance;
				m_AIStaticParamComponent->HearingRadius = BaseDataComponent->UnrealCurrentData.HearingRadius;
				m_AIStaticParamComponent->BehaviorTree = BaseDataComponent->GetBehaviorTree();
				//m_AIStaticParamComponent->BehaviorTree = BaseDataComponent->UnrealCurrentData.fstrAITree;
				m_AIStaticParamComponent->ChaseRadius = BaseDataComponent->UnrealCurrentData.ChaseRadius;
				m_AIStaticParamComponent->SprintRadius = BaseDataComponent->UnrealCurrentData.SprintRadius;
				m_AIStaticParamComponent->Direction = 0.f;
				m_AIStaticParamComponent->TargetActor = nullptr;
				m_AIStaticParamComponent->TargetActorArr.Reset(0);
				switch (BaseDataComponent->UnrealCurrentData.nType)
				{
				case 3:
					m_AIStaticParamComponent->Monster_type = CHARACTER_TYPE::CHARACTER_TYPE_BOSS;
					break;
				case 1:
				case 2:
				default:
					m_AIStaticParamComponent->Monster_type = CHARACTER_TYPE::CHARACTER_TYPE_MONSTER;
					break;
				}				
			}
		}
		break;
	case 4:
		//4NPC
		{
			CheckAIParamComponentExist();
			if (m_AIStaticParamComponent)
			{
				// set Monster data false
				m_AIStaticParamComponent->bMonster = false;
				// set NPC data	true
				m_AIStaticParamComponent->bNPC = true;
				m_AIStaticParamComponent->nTaskId = BaseDataComponent->UnrealCurrentData.nTaskID;
				m_AIStaticParamComponent->nNPCId = BaseDataComponent->UnrealCurrentData.nNPCId;

				// set monster type = npc
			}
		}
		break;
	case 5:
		//5»ï°é
		break;
	default:
		break;
	}
}

bool AMonsterBaseCharacter::ChangeStateToJump()
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_NORMAL || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_MOVE)
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

bool AMonsterBaseCharacter::ChangeStateToMove()
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

bool AMonsterBaseCharacter::ChangeStateToDodge()
{
	return true;
}

bool AMonsterBaseCharacter::ChangeStateToDefence()
{
	return true;
}

/*
*	Battle Model: Monster Attack
*/
bool AMonsterBaseCharacter::PlaySkillInstanceNextAtom(ASkillIInstance* pSkill)
{
	if (GetCurSkill() == nullptr || (pSkill != nullptr && pSkill != GetCurSkill()))
		return false;

	return GetCurSkill()->PlayNextSkill();

}

ASkillIInstance* AMonsterBaseCharacter::GetBaseSkill(PLAYER_SKILL_TYPE emType)
{
	auto pSkill = m_mapBaseSkill.Find(emType);
	if (pSkill)
		return *pSkill;

	return nullptr;
}

void AMonsterBaseCharacter::PauseAI()
{
	UPandaUtils::PauseAI(60, this, this);
	//const FString str = TEXT("PauseAI !!!");
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, str);
}

void AMonsterBaseCharacter::RestartAI()
{
	UPandaUtils::PauseAI(0, this, this);
	//const FString str = TEXT("RestartAI !!!");
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, str);
}