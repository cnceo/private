// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "SkillAtomHit.h"

ASkillAtomHit::ASkillAtomHit()
{

}

void ASkillAtomHit::InitByData(FsAtomExtendTable TableData)
{
	Super::InitByData(TableData);
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		auto AtomHitData = gameInstance->SafeGetDataManager()->m_AtomHitTable.Find(TableData.nAtomID);
		if (AtomHitData)
		{
			m_TableData = *AtomHitData;
			SetBaseTable(m_TableData);
		}
	}
}

void ASkillAtomHit::ResetAtom()
{
	Super::ResetAtom();
	m_mapTarget.Reset();
}

bool ASkillAtomHit::PlaySkillAtom(ABaseCharacter* pReviseTarget)
{
	return Super::PlaySkillAtom(pReviseTarget);
}

bool ASkillAtomHit::OnAnimTick(float fTime, const FString& AnimName)
{
	if (Super::OnAnimTick(fTime, AnimName)) return true;

	for (int32 i = 0; i < m_TableData.arrHitCount.Num(); ++i)
	{
		//����Ƿ����˺��ж��׶�
		if (m_fCurTime > m_TableData.arrHitCount[i].fBegin && m_fCurTime < m_TableData.arrHitCount[i].fEnd)
		{
			if (m_TableData.arrCollision.Num() > i)
			{
				TArray<FString> arrCollision;
				int32 nIndex = m_TableData.arrCollision[i].ParseIntoArray(arrCollision, TEXT("_"));
				CheckCollision(i + 1, arrCollision);
			}
		}
	}

	return true;

}

void ASkillAtomHit::CheckCollision(int32 nHitCount, TArray<FString> arrCollision)
{
	ABaseCharacter* pPlayer = GetCharacter();

	if (pPlayer)
	{
		//����Ч����ײ�������ײ���
		for (int32 i = 0; i < arrCollision.Num(); ++i)
		{
			CHARACTER_COLLISION_TYPE emCollisionType = CHARACTER_COLLISION_TYPE(FCString::Atoi(*arrCollision[i]));
			//�����ײ��
			UShapeComponent* pComponent = pPlayer->GetCollisionComponent(emCollisionType);
			if (pComponent)
			{
				TArray<UPrimitiveComponent*> arrComponents;
				pComponent->GetOverlappingComponents(arrComponents);
				//������ײ������ײ�����
				for (int32 index = 0; index < arrComponents.Num(); ++index)
				{
					IActiveActorInterface* pActor = Cast<IActiveActorInterface>(arrComponents[index]->GetOwner());

					//�ҳ����Ա����е�Ŀ��Actor(����ȱ�ٵ��ҷ��ж�)
					auto pCharacter = Cast<ABaseCharacter>(pActor);
					if (pActor && pActor != GetCharacter() && pCharacter && GetCharacter()->m_emType != pCharacter->m_emType)
					{
						auto HitResult = m_mapTarget.Find(pActor);
						//����Ѿ��������б��ڣ��������д����ж�
						if (HitResult)
						{
							if ((*HitResult).nCurHitCount == nHitCount)
							{
								continue;
							}
						}

						auto gameInstance = UPandaGameInstance::Instance();
						if (gameInstance)
						{
							float fHP = 0;
							float fMP = 0;
							float fPower = 0;
							USkillFormula* pHP = gameInstance->SafeGetDataManager()->GetSkillFormula(m_sEnemyEffectTable.nHPBP);
							if (pHP)
							{
								fHP = pHP->GetResult(GetCharacter(), Cast<AActor>(pActor), m_sEnemyEffectTable.fHPNum);
							}
							USkillFormula* pMP = gameInstance->SafeGetDataManager()->GetSkillFormula(m_sEnemyEffectTable.nMPBP);
							if (pMP)
							{
								fMP = pMP->GetResult(GetCharacter(), Cast<AActor>(pActor), m_sEnemyEffectTable.fMPNum);
							}
							USkillFormula* pPower = gameInstance->SafeGetDataManager()->GetSkillFormula(m_sEnemyEffectTable.nPowerBP);
							if (pPower)
							{
								fPower = pPower->GetResult(GetCharacter(), Cast<AActor>(pActor), m_sEnemyEffectTable.fPowerNum);
							}
							FsSkillHitResult sHitResult(m_sEnemyEffectTable, nHitCount, arrComponents[index], fHP, fMP, fPower);
							m_mapTarget.Add(pActor, sHitResult);
							pActor->Execute_OnHit(Cast<AActor>(pActor), GetCharacter(), sHitResult);
						}

					}
				}
			}
		}

	}

}