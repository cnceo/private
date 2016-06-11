// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "BaseCharacter.h"
#include "SkillIInstance.h"
#include "Net/UnrealNetwork.h"
#include "Utils/PandaUtils.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
	: m_emState(CHARACTER_STATE::CHARACTER_STATE_NORMAL)
	, m_emSubState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL)
	, m_pTargetActor(nullptr)
	, m_pCurSkill(nullptr)
	, m_bDead(false)
	, m_fBeHitFlyTime(0)
	, m_fAngle(0)
	, m_bFighting(false)
	, m_emType(CHARACTER_TYPE::CHARACTER_TYPE_NONE)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	m_DelayImpulseComponent = CreateDefaultSubobject<UDelayImpulseComponent>(TEXT("DelayImpulseComponent"));

}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter,m_emState);
	DOREPLIFETIME(ABaseCharacter,m_tBaseData);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnBeHitFly(DeltaTime);

}

UShapeComponent* ABaseCharacter::GetCollisionComponent(CHARACTER_COLLISION_TYPE emType)
{
	if (emType == CHARACTER_COLLISION_TYPE::COLLISION_WEAPON_L || emType == CHARACTER_COLLISION_TYPE::COLLISION_WEAPON_R)
	{
		if (IsValid(m_CurWeapon))
		{
			TArray<UActorComponent*> arrUShapeComponent = m_CurWeapon->GetComponentsByTag(UShapeComponent::StaticClass(), FName(*FString::Printf(TEXT("Collision_%d"), (int32)emType)));
			if (arrUShapeComponent.Num() > 0)
			{
				return Cast<UShapeComponent>(arrUShapeComponent[0]);
			}
		}
	}
	else
	{
		TArray<UActorComponent*> arrUShapeComponent = GetComponentsByTag(UShapeComponent::StaticClass(), FName(*FString::Printf(TEXT("Collision_%d"), (int32)emType)));
		if (arrUShapeComponent.Num() > 0)
		{
			return Cast<UShapeComponent>(arrUShapeComponent[0]);
		}
	}

	return nullptr;
}

UShapeComponent* ABaseCharacter::GetCheckSphere(FName strTag)
{
	if (!m_CheckSphere)
	{
		TArray<UActorComponent*> arrUShapeComponent = GetComponentsByTag(UShapeComponent::StaticClass(), strTag);
		if (arrUShapeComponent.Num() > 0)
		{
			m_CheckSphere = Cast<UShapeComponent>(arrUShapeComponent[0]);
		}
	}

	return m_CheckSphere;

}

void ABaseCharacter::SetCollisionOverlapEvents(CHARACTER_COLLISION_TYPE emType, bool bEvent)
{
	if (emType == CHARACTER_COLLISION_TYPE::COLLISION_ALL_MAX)
	{
		for (int32 i = 0; i < (int32)CHARACTER_COLLISION_TYPE::COLLISION_ALL_MAX; ++i)
		{
			UShapeComponent* pCollision = GetCollisionComponent((CHARACTER_COLLISION_TYPE)i);
			if (pCollision)
			{
				pCollision->bGenerateOverlapEvents = bEvent;
			}
		}
	}
	else
	{
		UShapeComponent* pCollision = GetCollisionComponent(emType);
		if (pCollision)
		{
			pCollision->bGenerateOverlapEvents = bEvent;
		}
	}
}

void ABaseCharacter::OnAnimBegin_Implementation(float fTime, const FString& AnimName)
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_SKILL && GetCurSkill())
	{
		GetCurSkill()->OnAnimBegin(fTime, AnimName);
	}
}

void ABaseCharacter::OnAnimTick_Implementation(float fTime, const FString& AnimName)
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_SKILL && GetCurSkill())
	{
		GetCurSkill()->OnAnimTick(fTime, AnimName);
	}
}

void ABaseCharacter::OnAnimEnd_Implementation(const FString& AnimName)
{
	if (m_emState == CHARACTER_STATE::CHARACTER_STATE_SKILL && GetCurSkill())
	{
		GetCurSkill()->OnAnimEnd(AnimName);
		return;
	}

	//获取动画对应的角色状态
	FString strName(*AnimName);
	int32 nIndex = strName.Find(TEXT("__"));
	if (nIndex <= 0) return;
	strName.RemoveAt(nIndex, strName.Len() - nIndex);
	CHARACTER_SUB_STATE emSub = CHARACTER_SUB_STATE(FCString::Atoi(*strName));

	//动画播放完毕后状态处理
	if (m_emSubState == emSub)
	{
		//到待机
		if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHIT1 || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHIT2
			|| m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_TUMBLE || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_GETUP
			|| m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_HITFLY_LAND || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_REEL1)
		{
			SetState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_NORMAL);
			RestartAI();
		}
		//到倒地起身
		else if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_TUMBLE || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_HITROLL)
		{
			SetState(CHARACTER_SUB_STATE::SUB_STATE_GETUP, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
		}
		//到漂浮状态
		else if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT1 || m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT2
				|| m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHITFLY)
		{

		}
		//死亡销毁Character
		else if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_DIE_NORMAL)
		{
			if (m_emType != CHARACTER_TYPE::CHARACTER_TYPE_PLAYER)
			{
				Destroy();
			}
		}

	}

}

void ABaseCharacter::OnAnimTick_BP(float fTime, const FString& AnimName)
{
	this->Execute_OnAnimTick(this, fTime, AnimName);
}

void ABaseCharacter::OnAnimBegin_BP(float fTime, const FString& AnimName)
{
	this->Execute_OnAnimBegin(this, fTime, AnimName);
}

void ABaseCharacter::OnAnimEnd_BP(const FString& AnimName)
{
	this->Execute_OnAnimEnd(this, AnimName);
}

bool ABaseCharacter::SetState_Validate(CHARACTER_SUB_STATE emSubState, CHARACTER_STATE emState)
{
	return true;
}

void ABaseCharacter::SetState_Implementation(CHARACTER_SUB_STATE emSubState, CHARACTER_STATE emState)
{
	if (emSubState != CHARACTER_SUB_STATE::SUB_STATE_NONE && m_emSubState != emSubState)
		m_emSubState = emSubState;

	if (emState != CHARACTER_STATE::CHARACTER_STATE_NONE && m_emState != emState)
		m_emState = emState;
}

void ABaseCharacter::OnHit_Implementation(AActor* HitCauser, FsSkillHitResult sHitResult)
{

}

void ABaseCharacter::TurnOnRagDoll(bool bSetValue)
{
	if (bSetValue)
	{
		GetMesh()->SetAnimInstanceClass(nullptr);
	}

	GetMesh()->SetAllBodiesSimulatePhysics(bSetValue);
}

void ABaseCharacter::EquipWeapon( FString ResPath, FName SocketName)
{
	UnequipWeapon();
	
	//load weapon
	FString AssetPath = "/Game/BPInstance/Weapon/testAttachWeapon.testAttachWeapon_C";
	UBlueprintGeneratedClass* ParentClass = UPandaUtils::GetAssetFromPath(AssetPath);

	if (ParentClass != nullptr)
	{
		AAttachWeapon* weapon = GetWorld()->SpawnActor<AAttachWeapon>(ParentClass, GetActorLocation(), GetActorRotation());
		if (weapon != nullptr)
		{
			weapon->Attach2Pawn(this, GetMesh(), SocketName);
			m_CurWeapon = weapon;
			PostEquipWeapon();
		}
	}
}

void ABaseCharacter::UnequipWeapon()
{
	if (m_CurWeapon != nullptr)
	{
		m_CurWeapon->Destroy();
		m_CurWeapon = nullptr;
	}
}

CHARACTER_WEAPON_TYPE ABaseCharacter::GetWeaponType()
{
	if (m_CurWeapon)
	{

	}

	return CHARACTER_WEAPON_TYPE::WEAPON_NONE;
}

void ABaseCharacter::OnSkillHitEvent(CHARACTER_COLLISION_TYPE emType, AActor* pOtherActor, UPrimitiveComponent* pOtherComp, int32 OtherBodyIndex, bool FromSweep, FHitResult SweepResult)
{

}


bool ABaseCharacter::RPCServerDumpPlayers_Validate(){
	return true;
}

void ABaseCharacter::RPCServerDumpPlayers_Implementation(){
	//here execute from server
	m_tBaseData.fHP+=1;
	int n=0;
	for(auto it=GetWorld()->GetPlayerControllerIterator();it;++it){
		n++;
		if(auto pawn=(*it)->GetCharacter()){
			if(auto p=Cast<ABaseCharacter>(pawn))
				UE_LOG(LogTemp,Warning,TEXT("--------players on server uid=%d,hp=%f, state=%d"),pawn->GetUniqueID(),p->m_tBaseData.fHP,(int32)m_emState);
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("--------server players %d"),n);
}

void ABaseCharacter::RPCClientDumpPlayers_Implementation(){
	//here execute at client
	int n=0;
	if(auto me=GetWorld()->GetFirstPlayerController()){
		if(auto pawn=me->GetCharacter()){
			if(auto p=Cast<ABaseCharacter>(pawn))
				UE_LOG(LogTemp,Warning,TEXT("--------my uid=%d,hp=%f, state=%d"),pawn->GetUniqueID(),p->m_tBaseData.fHP,(int32)m_emState);
		}
	}

	UE_LOG(LogTemp,Warning,TEXT("--------server pawns %d"),GetWorld()->GetNumPawns());
	for(auto it=GetWorld()->GetPawnIterator();it;++it){
		if(auto pawn=(*it)){
			auto uid=pawn->GetUniqueID();
			if(auto p=Cast<ABaseCharacter>(pawn))
				UE_LOG(LogTemp,Warning,TEXT("--------pawns on server uid=%d,hp=%f, state=%d"),pawn->GetUniqueID(),p->m_tBaseData.fHP,(int32)m_emState);
		}
	}
}

void ABaseCharacter::OnRep_State(){
	UE_LOG(LogTemp,Warning,TEXT("--------sync state uid=%d,hp=%f, state=%d"),GetUniqueID(),m_tBaseData.fHP,(int32)m_emState);
}

ASkillIInstance* ABaseCharacter::AppendSkill(int32 nID)
{
	ASkillIInstance* pSkill = (ASkillIInstance*)GetWorld()->SpawnActor(ASkillIInstance::StaticClass());
	if (pSkill)
	{ 
		pSkill->SetOwner(this);
		pSkill->InitByID(nID);
		return pSkill;
	}

	return nullptr;
}

bool ABaseCharacter::PlaySkillInstance(ASkillIInstance* pSkill)
{
	if (pSkill)
	{
		//当前如果有使用中的其他技能
		if (GetCurSkill())
		{
			if (pSkill != GetCurSkill())
			{	
				//判断技能动作是否可融合
				if (GetCurSkill()->IsBeFuse())
				{
					bool bPlay = pSkill->PlaySkill();
					//中断原技能,并播放新技能
					if (bPlay)
					{
						GetCurSkill()->BreakSkill(false);
						SetCurSkill(pSkill);
						pSkill->OnAnimInstanceEvent();
						return true;
					}
				}
			}

			return false;
		}

		bool bPlay = pSkill->PlaySkill();
		if (bPlay)
		{
			SetCurSkill(pSkill);
			pSkill->OnAnimInstanceEvent();
			return true;
		}
	}

	return false;

}

UAnimMontage* ABaseCharacter::GetCurSkillMontage()
{
	if (m_pCurSkill)
	{
		return m_pCurSkill->GetCurAtomMontage();
	}

	return nullptr;
}

UAnimSequence* ABaseCharacter::GetCurSkillSequence()
{
	if (m_pCurSkill)
	{
		return m_pCurSkill->GetCurAtomSequence();
	}

	return nullptr;
}

void ABaseCharacter::PlayBeHitFly(AActor* HitCauser)
{
	m_fAngle = UPandaUtils::VectorAngle(GetCapsuleComponent()->GetForwardVector(), HitCauser->GetActorLocation() - GetActorLocation());
	m_fAngle += m_fAngle > 0 ? 360 : -360;
}

void ABaseCharacter::OnBeHitFly(float DeltaSeconds)
{
	if (m_fAngle != 0)
	{
		if (m_emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHITFLY)
		{
			float fMaxTime = 0.5f;
			float fCurAngle = 0;
			if (m_fBeHitFlyTime + DeltaSeconds > fMaxTime)
			{
				DeltaSeconds = fMaxTime - m_fBeHitFlyTime;
				fCurAngle = DeltaSeconds / fMaxTime*m_fAngle;
				m_fBeHitFlyTime = 0;
				m_fAngle = 0;
			}
			else
			{
				m_fBeHitFlyTime += DeltaSeconds;
				fCurAngle = DeltaSeconds / fMaxTime*m_fAngle;
			}

			FRotator ActorRotator = GetActorRotation();
			ActorRotator.Yaw -= fCurAngle;
			ActorRotator.Normalize();
			SetActorRotation(ActorRotator);
		}
		else
		{
			m_fBeHitFlyTime = 0;
			m_fAngle = 0;
		}
	}

}

void ABaseCharacter::DelayImpulse(float fDelayTime, FVector vDirection, int32 nForce)
{
	if (m_DelayImpulseComponent)
		m_DelayImpulseComponent->DelayImpulse(this, fDelayTime, vDirection, nForce, m_emSubState);
}

void ABaseCharacter::TurnAtActor(AActor *pActor)
{
	if (!pActor) return;
	FVector distance = pActor->GetActorLocation() - GetActorLocation();
	FVector direction = GetCapsuleComponent()->GetForwardVector();
	float fAngle = UPandaUtils::VectorAngle(direction, distance);
	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw -= fAngle;
	ActorRotation.Normalize();
	SetActorRotation(ActorRotation);

}