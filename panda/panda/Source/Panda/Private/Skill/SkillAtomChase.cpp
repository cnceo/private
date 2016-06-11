// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "SkillAtomChase.h"

ASkillAtomChase::ASkillAtomChase()
	: m_pTarget(nullptr)
	, m_nRadius(0)
	, m_bFinish(false)
{

}

void ASkillAtomChase::InitByData(FsAtomExtendTable TableData)
{
	Super::InitByData(TableData);
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		auto AtomHitData = UPandaGameInstance::Instance()->SafeGetDataManager()->m_AtomChaseTable.Find(TableData.nAtomID);
		if (AtomHitData)
		{
			m_TableData = *AtomHitData;
			SetBaseTable(m_TableData);
		}
	}
}

void ASkillAtomChase::ResetAtom()
{
	Super::ResetAtom();
	m_pTarget = nullptr;
	m_nRadius = 0;
	m_bFinish = false;
	GetWorld()->GetTimerManager().ClearTimer(m_FlyHandle);
}

bool ASkillAtomChase::PlaySkillAtom(ABaseCharacter* pReviseTarget)
{
	if (Super::PlaySkillAtom(pReviseTarget))
	{
		ABaseCharacter* pPlayer = GetCharacter();
		if (pPlayer && pPlayer->GetTarget())
		{
			m_pTarget = pPlayer->GetTarget();
			pPlayer->GetCharacterMovement()->Velocity = FVector::ZeroVector;
			m_nRadius = pPlayer->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
			return true;
		}
	}

	return false;

}

bool ASkillAtomChase::OnAnimTick(float fTime, const FString& AnimName)
{
	if (Super::OnAnimTick(fTime, AnimName)) return true;

	ABaseCharacter* pPlayer = GetCharacter();
	if (!m_bNext && pPlayer && m_pTarget)
	{
		//向量计算
		FVector pPlayerLocation = pPlayer->GetActorLocation();
		FVector pTargetLocation = m_pTarget->GetActorLocation();
		auto TempVector_1 = (pTargetLocation - pPlayerLocation);
		TempVector_1.Normalize();

		//计算是否已完成追击
		int32 nActgorDistance = m_pTarget->GetDistanceTo(pPlayer);
		if ((nActgorDistance < m_nRadius + m_TableData.nSpace + 100) && pPlayerLocation.Z > pTargetLocation.Z-20)
		{
			m_bNext = true;
			if (GetSkillIInstance())
				GetSkillIInstance()->OnBeFuseEvent();
			FTimerDelegate FlyTimer;
			FlyTimer.BindUObject(this, &ASkillAtomChase::OnFlyCallBack);
			GetWorld()->GetTimerManager().SetTimer(m_FlyHandle, FlyTimer, m_TableData.fFlyTime, false);

			//到达目标后,最后给一次小的加速度运动
			auto TempVector_2 = pTargetLocation - (TempVector_1 * m_nRadius);
			TempVector_2.Z = pTargetLocation.Z;
			auto TempVector_3 = TempVector_2 - pPlayerLocation;
			TempVector_3.Normalize();
			pPlayer->GetCharacterMovement()->Velocity = pPlayer->GetCharacterMovement()->Velocity = TempVector_3 * 300;
			return true;
		}

		//加速度计算
		auto TempVector_2 = pTargetLocation - (TempVector_1 * (m_nRadius + m_TableData.nSpace));
		TempVector_2.Z = pTargetLocation.Z;
		auto TempVector_3 = TempVector_2 - pPlayerLocation;
		TempVector_3.Normalize();
		auto CurVelocity = TempVector_3 * (m_fCurTime * m_TableData.nSpeed);
		pPlayer->GetCharacterMovement()->Velocity.X += CurVelocity.X;
		pPlayer->GetCharacterMovement()->Velocity.Y += CurVelocity.Y;
		pPlayer->GetCharacterMovement()->Velocity.Z += CurVelocity.Z;

	}

	return true;
}

void ASkillAtomChase::OnFlyCallBack()
{
	auto pSkill = Cast<ASkillIInstance>(GetOwner());
	if (pSkill)
	{
		pSkill->PlayAtomEnd();
	}
}