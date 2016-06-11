// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "SkillAtomBase.h"


// Sets default values
ASkillAtomBase::ASkillAtomBase()
	: m_fMaxTime(0)
	, m_fCurTime(0)
	, m_fFuseTime(0)
	, m_bNext(false)
	, m_bNextCheck(false)
	, m_CurHitCount(0)
	, m_pAnimMontage(nullptr)
	, m_pAnimSequence(nullptr)
	, m_pReviseTarget(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASkillAtomBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillAtomBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASkillAtomBase::InitByData(FsAtomExtendTable TableData)
{
	m_sAtomExtendData = TableData;

	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		auto EffectSelf = gameInstance->SafeGetDataManager()->m_AtomEffectTable.Find(m_sAtomExtendData.nEffectSelf);
		if (EffectSelf)
		{
			m_sSelfEffectTable = *EffectSelf;
		}

		auto EffectFriend = gameInstance->SafeGetDataManager()->m_AtomEffectTable.Find(m_sAtomExtendData.nEffectFriend);
		if (EffectFriend)
		{
			m_sFriendEffectTable = *EffectFriend;
		}

		auto EffectEnemy = gameInstance->SafeGetDataManager()->m_AtomEffectTable.Find(m_sAtomExtendData.nEffectEnemy);
		if (EffectEnemy)
		{
			m_sEnemyEffectTable = *EffectEnemy;
		}
	}
}

void  ASkillAtomBase::SetBaseTable(FsAtomBaseTable AtomData)
{ 
	m_sBaseAtomData = AtomData;

	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		auto TableData = gameInstance->SafeGetDataManager()->m_ResourcesTable.Find(m_sBaseAtomData.nResourcesID);
		if (TableData)
		{
			m_sResources = *TableData;
		}
	}

	//SetAtomAnim();
}

ABaseCharacter* ASkillAtomBase::GetCharacter()
{
	return Cast<ABaseCharacter>(GetOwner()->GetOwner());
}

bool ASkillAtomBase::PlaySkillAtom(ABaseCharacter* pReviseTarget)
{
	ABaseCharacter* pPlayer = GetCharacter();
	if (!pPlayer) return false;

	if (pReviseTarget)
	{
		m_pReviseTarget = pReviseTarget;
	}
	else
	{
		if (!CheckPlaySkillAtom()) 
			return false;
	}

	if (m_sSelfEffectTable.nID != 0)
	{
		pPlayer->SetState(CHARACTER_SUB_STATE(m_sSelfEffectTable.nSubState), CHARACTER_STATE(m_sSelfEffectTable.nState));

		if (m_sSelfEffectTable.nMode != 0)
		{
			pPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode(m_sSelfEffectTable.nMode));
		}
		
	}
	
	SetAtomAnim();
	return true;
}

bool ASkillAtomBase::CheckPlaySkillAtom()
{
	if (GetCharacter())
	{
		ABaseCharacter* pCharacter = nullptr;
		//属性检测
		if (GetCharacter()->m_emType == CHARACTER_TYPE::CHARACTER_TYPE_PLAYER)
		{
			auto pPlayer = Cast<APlayerCharacter>(GetCharacter());
			//自身属性检测
			if (m_sBaseAtomData.nHP > pPlayer->BaseDataComponent->GetHP()
				|| m_sBaseAtomData.nMP > pPlayer->BaseDataComponent->GetMP()
				|| m_sBaseAtomData.nPower > pPlayer->BaseDataComponent->GetPower())
			{
				return false;
			}
			pCharacter = pPlayer;
		}
		else
		{
			auto pMonster = Cast<AMonsterCharacter>(GetCharacter());
			if (m_sBaseAtomData.nHP > pMonster->BaseDataComponent->GetHP()
				|| m_sBaseAtomData.nMP > pMonster->BaseDataComponent->GetMP()
				|| m_sBaseAtomData.nPower > pMonster->BaseDataComponent->GetPower())
			{
				return false;
			}
			pCharacter = pMonster;
		}

		//自身状态检测
		bool bHas = false;
		for (int32 i = 0; i < m_sBaseAtomData.arrCharacterState.Num(); ++i)
		{
			if ((int32)pCharacter->GetState() == m_sBaseAtomData.arrCharacterState[i])
			{
				bHas = true;
				break;
			}
		}
		if (m_sBaseAtomData.arrCharacterState.Num() > 0 && !bHas) return false;

		//自身子状态检测
		bHas = false;
		for (int32 i = 0; i < m_sBaseAtomData.arrCharacterSubState.Num(); ++i)
		{
			if ((int32)pCharacter->GetSubState() == m_sBaseAtomData.arrCharacterSubState[i])
			{
				bHas = true;
				break;
			}
		}
		if (m_sBaseAtomData.arrCharacterSubState.Num() > 0 && !bHas) return false;

		//自身CharacterMovementMode检测
		bHas = false;
		for (int32 i = 0; i < m_sBaseAtomData.arrMovementMode.Num(); ++i)
		{
			if ((int32)pCharacter->GetCharacterMovement()->MovementMode == m_sBaseAtomData.arrMovementMode[i])
			{
				bHas = true;
				break;
			}
		}
		if (m_sBaseAtomData.arrMovementMode.Num() > 0 && !bHas) return false;

		//自身BUFF检测
		//bHas = false;
		//for (int32 i = 0; i < m_sBaseAtomData.arrBUFF.Num(); ++i)
		//{
		//	if (m_sBaseAtomData.arrBUFF[i])
		//	{
		//		bHas = true;
		//		break;
		//	}
		//}
		//if (m_sBaseAtomData.arrBUFF.Num() > 0 && !bHas) return false;

		//目标相关检测
		if (m_sBaseAtomData.bTarget)
		{
			auto pTarget = pCharacter->GetTarget();
			if (!pTarget || pCharacter->GetDistanceTo(pTarget) > m_sBaseAtomData.nDistance)
			{
				return false;

			}

			//目标状态检测
			bool bTargetHas = false;
			for (int32 i = 0; i < m_sBaseAtomData.arrTargetState.Num(); ++i)
			{
				if ((int32)pTarget->GetState() == m_sBaseAtomData.arrTargetState[i])
				{
					bTargetHas = true;
					break;
				}
			}
			if (m_sBaseAtomData.arrTargetState.Num() > 0 && !bTargetHas) return false;

			//目标子状态检测
			bTargetHas = false;
			for (int32 i = 0; i < m_sBaseAtomData.arrTargetSubState.Num(); ++i)
			{
				if ((int32)pTarget->GetSubState() == m_sBaseAtomData.arrTargetSubState[i])
				{
					bTargetHas = true;
					break;
				}
			}
			if (m_sBaseAtomData.arrTargetSubState.Num() > 0 && !bTargetHas) return false;

			//目标CharacterMovementMode检测
			bTargetHas = false;
			for (int32 i = 0; i < m_sBaseAtomData.arrTargetMovementMode.Num(); ++i)
			{
				if ((int32)pTarget->GetCharacterMovement()->MovementMode == m_sBaseAtomData.arrTargetMovementMode[i])
				{
					bTargetHas = true;
					break;
				}
			}
			if (m_sBaseAtomData.arrTargetMovementMode.Num() > 0 && !bTargetHas) return false;

			//目标BUFF检测
			//bTargetHas = false;
			//for (int32 i = 0; i < m_sBaseAtomData.arrTargetBUFF.Num(); ++i)
			//{
			//	if (m_sBaseAtomData.arrTargetBUFF[i])
			//	{
			//		bTargetHas = true;
			//		break;
			//	}
			//}
			//if (m_sBaseAtomData.arrTargetBUFF.Num() > 0 && !bTargetHas) return false;
		}

	}

	return true;

}

void ASkillAtomBase::SetAtomAnim()
{
	if (!m_sResources.strPath.IsEmpty() && !m_sResources.strName.IsEmpty())
	{
		if (m_sResources.strName.Find(TEXT("Montage")))
		{
			m_pAnimMontage = UPandaUtils::LoadResource<UAnimMontage>(m_sResources.strPath);
		}
		else
		{
			m_pAnimSequence = UPandaUtils::LoadResource<UAnimSequence>(m_sResources.strPath);
		}
	}

}

void ASkillAtomBase::ResetAtom()
{
	m_fMaxTime = 0;
	m_fCurTime = 0;
	m_fFuseTime = 0;
	m_bNext = false;
	m_bNextCheck = false;
	m_pAnimMontage = nullptr;
	m_pAnimSequence = nullptr;
	m_pReviseTarget = nullptr;
}

ASkillIInstance* ASkillAtomBase::GetSkillIInstance()
{
	return Cast<ASkillIInstance>(GetOwner());
}

void ASkillAtomBase::OnAnimBegin(float fTime, const FString& AnimName)
{
	if (m_sResources.strName != AnimName) return;
	m_fMaxTime = fTime;
	if (m_pReviseTarget)
	{
		GetCharacter()->TurnAtActor(m_pReviseTarget);
	}

}

bool ASkillAtomBase::OnAnimTick(float fTime, const FString& AnimName)
{
	if (m_sResources.strName != AnimName) return true;

	m_fCurTime += fTime;

	if (m_sBaseAtomData.nType == (int32)SKILL_ATOM_TYPE::SKILL_ATOM_HIT)
	{
		if (!m_bNext && m_fCurTime > m_sBaseAtomData.fFuseTime)
		{
			m_bNext = true;
			if (GetSkillIInstance())
				GetSkillIInstance()->OnBeFuseEvent();
		}
	}

	if (m_bNext && !m_bNextCheck)
	{
		m_fFuseTime += fTime;

		if (ATOM_NEXT_TYPE(m_sAtomExtendData.nNextType) == ATOM_NEXT_TYPE::ATOM_NEXT_TIME && m_fFuseTime > m_sAtomExtendData.fNextTime)
		{
			m_bNextCheck = true;
			auto pSkill = Cast<ASkillIInstance>(GetOwner());
			if (pSkill)
			{
				return pSkill->PlayNextSkill();
			}
		}

	}

	return false;

}

void ASkillAtomBase::OnAnimEnd(const FString& AnimName)
{
	if (m_sResources.strName != AnimName) return;

	auto pSkill = Cast<ASkillIInstance>(GetOwner());
	if (pSkill)
	{
		pSkill->PlayAtomEnd();
	}

}