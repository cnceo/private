// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "SkillIInstance.h"
#include "PandaGameInstance.h"

// Sets default values
ASkillIInstance::ASkillIInstance()
	: m_nCurAtomIndex(0)
	, m_nCurArrIndex(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ASkillIInstance::InitByID(int32 nID)
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		auto TableData = gameInstance->SafeGetDataManager()->m_SkillTable.Find(nID);
		if (TableData)
		{
			m_sTableData = *TableData;

			for (int32 i = 0; i < m_sTableData.arrAtomExtend.Num(); ++i)
			{
				TArray<FString> arrAtomID;
				TArray<ASkillAtomBase*> arrAtom;
				m_sTableData.arrAtomExtend[i].ParseIntoArray(arrAtomID, TEXT("_"));

				for (int32 n = 0; n < arrAtomID.Num(); ++n)
				{
					auto AtomExtend = gameInstance->SafeGetDataManager()->m_AtomExtendTable.Find(FCString::Atoi(*arrAtomID[n]));
					if (AtomExtend)
					{
						switch (AtomExtend->nType)
						{
						case 1:
						{
							ASkillAtomHit* pAtom = (ASkillAtomHit*)GetWorld()->SpawnActor(ASkillAtomHit::StaticClass());
							pAtom->SetOwner(this);
							pAtom->InitByData(*AtomExtend);
							arrAtom.Add(pAtom);
						}
						break;

						case 2:
						{
							ASkillAtomChase* pAtom = (ASkillAtomChase*)GetWorld()->SpawnActor(ASkillAtomChase::StaticClass());
							pAtom->SetOwner(this);
							pAtom->InitByData(*AtomExtend);
							arrAtom.Add(pAtom);
						}
						break;

						default:
							break;
						}
					}

				}

				m_arrAtomInstance.Add(arrAtom);

			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SkillIInstance Init Faled! nID=%d"), nID);
		}
	}
}

// Called when the game starts or when spawned
void ASkillIInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillIInstance::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

ABaseCharacter* ASkillIInstance::GetCharacter()
{
	return Cast<ABaseCharacter>(GetOwner());
}

void ASkillIInstance::ResetInstance()
{
	m_nCurArrIndex = 0;
	m_nCurAtomIndex = 0;
}

bool ASkillIInstance::PlaySkill()
{
	if (m_arrAtomInstance.Num() <= 0 || m_arrAtomInstance[0].Num() <= 0) return false;
	AActor* pTarget = nullptr;
	int32 nIndex = GetAngleReviseIndex(0, pTarget);
	bool bPlay = false;
	if (nIndex < 0)
	{
		bPlay = m_arrAtomInstance[0][0]->PlaySkillAtom();
	}
	else
	{
		bPlay = m_arrAtomInstance[0][nIndex]->PlaySkillAtom(Cast<ABaseCharacter>(pTarget));
		m_nCurAtomIndex = nIndex;
	}

	if (bPlay && GetCharacter())
	{
		GetCharacter()->PauseAI();
	}
	return bPlay;
}

void ASkillIInstance::OnAnimInstanceEvent()
{
	ABaseCharacter* pPlayer = GetCharacter();
	if (!pPlayer) return;

	auto pAnimInstance = Cast<UBaseAnimInstance>(pPlayer->GetMesh()->GetAnimInstance());
	if (pAnimInstance)
	{
		pAnimInstance->OnPlaySkill();
	}
}

//��õ�ǰԭ�ӵ���̫��
UAnimMontage* ASkillIInstance::GetCurAtomMontage()
{
	if (m_nCurArrIndex > m_arrAtomInstance.Num() || m_nCurAtomIndex > m_arrAtomInstance[m_nCurArrIndex].Num()) return nullptr;
	return m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_pAnimMontage;
}

//��õ�ǰԭ�ӵĶ�������
UAnimSequence* ASkillIInstance::GetCurAtomSequence()
{
	if (m_nCurArrIndex > m_arrAtomInstance.Num() || m_nCurAtomIndex > m_arrAtomInstance[m_nCurArrIndex].Num()) return nullptr;
	return m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_pAnimSequence;
}

//���ý�ɫ���״̬����
void ASkillIInstance::ResetCharacterData(bool bChangeState)
{
	auto pCharacter = GetCharacter();
	if (pCharacter)
	{
		pCharacter->ClearCurSkill();
		if (bChangeState && pCharacter->GetState() == CHARACTER_STATE::CHARACTER_STATE_SKILL)
		{
			pCharacter->SetState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_NORMAL);
			pCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}

}

//��ɫ����֪ͨ
void ASkillIInstance::OnAnimBegin(float fTime, const FString& AnimName)
{
	if (m_nCurArrIndex > m_arrAtomInstance.Num() || m_nCurAtomIndex > m_arrAtomInstance[m_nCurArrIndex].Num()) return;
	m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->OnAnimBegin(fTime, AnimName);
}

//��ɫ����֪ͨ
void ASkillIInstance::OnAnimTick(float fTime, const FString& AnimName)
{
	if (m_nCurArrIndex > m_arrAtomInstance.Num() || m_nCurAtomIndex > m_arrAtomInstance[m_nCurArrIndex].Num()) return;
	m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->OnAnimTick(fTime, AnimName);
}

//��ɫ����֪ͨ
void ASkillIInstance::OnAnimEnd(const FString& AnimName)
{
	if (m_nCurArrIndex > m_arrAtomInstance.Num() || m_nCurAtomIndex > m_arrAtomInstance[m_nCurArrIndex].Num()) return;
	m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->OnAnimEnd(AnimName);
}

//������밴���Ƿ񴥷���������.���������±�
int32 ASkillIInstance::CheckPlayNextByInputKey(bool arrbPressedKey[PLAYER_KEY::PLAYER_KEY_MAX], PLAYER_KEY emCurKey)
{
	if (m_nCurArrIndex > m_arrAtomInstance.Num() || m_nCurAtomIndex > m_arrAtomInstance[m_nCurArrIndex].Num()) return 0;

	if (ATOM_NEXT_TYPE(m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.nNextType) == ATOM_NEXT_TYPE::ATOM_NEXT_INPUT && m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_bNext)
	{
		auto arr = m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.arrInput;
		for (int32 i = 0; i < arr.Num(); ++i)
		{
			if ((arr[i].nKey_1 == 0 || arrbPressedKey[arr[i].nKey_1])
				&& (arr[i].nKey_2 == 0 || arrbPressedKey[arr[i].nKey_2])
				&& (arr[i].nKey_1 == (int32)emCurKey || arr[i].nKey_2 == (int32)emCurKey)
				)
			{
				return arr[i].nNextIndex;
			}

		}
	}

	return 0;
}

//���ż�������
bool ASkillIInstance::PlayNextSkill(int32 nNextIndex)
{
	if (nNextIndex == 0)
	{
		nNextIndex = m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.nNextIndex;
	}

	if (m_arrAtomInstance.Num() > nNextIndex && nNextIndex != 0)
	{
		AActor* pTarget = nullptr;
		int32 nIndex = GetAngleReviseIndex(nNextIndex, pTarget);
		bool bPlay = false;
		if (nIndex < 0)
		{
			bPlay = m_arrAtomInstance[nNextIndex][0]->PlaySkillAtom();
			if (bPlay)
			{
				m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->ResetAtom();
				m_nCurArrIndex = nNextIndex;
				m_nCurAtomIndex = 0;
				if (GetCharacter())
					GetCharacter()->PauseAI();
				OnAnimInstanceEvent();
			}
		}
		else
		{
			bPlay = m_arrAtomInstance[nNextIndex][nIndex]->PlaySkillAtom(Cast<ABaseCharacter>(pTarget));
			if (bPlay)
			{
				m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->ResetAtom();
				m_nCurArrIndex = nNextIndex;
				m_nCurAtomIndex = nIndex;
				if (GetCharacter())
					GetCharacter()->PauseAI();
				OnAnimInstanceEvent();
			}
		}

		return bPlay;

	}

	return false;
}

void ASkillIInstance::PlayAtomEnd()
{
	if (ATOM_NEXT_TYPE(m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.nNextType) == ATOM_NEXT_TYPE::ATOM_NEXT_BEEND && m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.nNextIndex != 0)
	{
		bool bPlay = PlayNextSkill(m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.nNextIndex);
		if (bPlay) return;
	}

	BreakSkill();

}

void ASkillIInstance::OnBeFuseEvent()
{
	if (GetCharacter())
		GetCharacter()->RestartAI();
}

bool ASkillIInstance::IsBeFuse()
{
	return m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_bNext;
}

bool ASkillIInstance::IsBeCounterattack()
{
	if (IsBeFuse())
	{
		if (ATOM_NEXT_TYPE(m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_sAtomExtendData.nNextType) == ATOM_NEXT_TYPE::ATOM_NEXT_BEHIT)
			return true;
	}

	return false;
}

void ASkillIInstance::BreakSkill(bool bChangeState)
{
	//ֹͣ��ǰ���ŵ���̫��
	if (m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_pAnimMontage)
	{
		ABaseCharacter* pPlayer = GetCharacter();
		if (pPlayer)
		{
			pPlayer->GetMesh()->GetAnimInstance()->Montage_Stop(0, m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_pAnimMontage);
		}
	}

	//ֹͣ��ǰ���ŵļ��ܶ���
	if (m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->m_pAnimSequence)
	{
		ABaseCharacter* pPlayer = GetCharacter();
		if (pPlayer)
		{
			//pPlayer->GetMesh()->GetAnimInstance()->Montage_Stop(0, m_arrAtomInstance[m_nCurAtomIndex]->m_pAnimMontage);
		}
	}

	m_arrAtomInstance[m_nCurArrIndex][m_nCurAtomIndex]->ResetAtom();
	ResetInstance();
	ResetCharacterData(bChangeState);
}

int32 ASkillIInstance::GetAngleReviseIndex(int32 arrIndex, AActor*& pOutTarget)
{
	if (GetCharacter() && GetCharacter()->GetCheckSphere() 
		&& !GetCharacter()->GetTarget() && m_arrAtomInstance[arrIndex][0]->m_sAtomExtendData.bAutoAngle)
	{
		TArray<AActor*> arrActor;
		TMap<float, AActor*> mapActor;

		//��ü�����е�ȫ����ɫ
		GetCharacter()->GetCheckSphere()->GetOverlappingActors(arrActor, ABaseCharacter::StaticClass());
		for (int32 i = 0; i < arrActor.Num(); ++i)
		{
			//ֻ�����ж�Ŀ��
			if (GetCharacter() != arrActor[i])
			{
				mapActor.Add(FMath::Abs(GetCharacter()->GetDistanceTo(arrActor[i])), arrActor[i]);
			}
		}

		//��������ɽ���Զ����
		mapActor.KeySort([](float a, float b) { return b > a; });

		//����Ŀ������
		for (auto ActorIt = mapActor.CreateConstIterator(); ActorIt; ++ActorIt)
		{
			ActorIt.Key();
			AActor* pActor = ActorIt.Value();
			for (int32 i = 0; i < m_arrAtomInstance[arrIndex].Num(); ++i)
			{
				if (m_arrAtomInstance[arrIndex][i]->m_sAtomExtendData.bAutoAngle)
				{
					//���ܵ����ĽǶȼ��
					FVector distance = pActor->GetActorLocation() - GetCharacter()->GetActorLocation();
					FVector direction = GetCharacter()->GetCapsuleComponent()->GetForwardVector();
					float fAngle = UPandaUtils::VectorAngle(direction, distance);
					for (int32 n = 0; n < m_arrAtomInstance[arrIndex][i]->m_sAtomExtendData.arrHitAngle.Num(); ++n)
					{
						float fBegin = m_arrAtomInstance[arrIndex][i]->m_sAtomExtendData.arrHitAngle[n].fBegin;
						float fEnd = m_arrAtomInstance[arrIndex][i]->m_sAtomExtendData.arrHitAngle[n].fEnd;
						if (fAngle >= fBegin && fAngle <= fEnd)
						{
							//�ҵ��Ƕ��������ϲ��������ͷ������ļ���
							if (m_arrAtomInstance[arrIndex][i]->CheckPlaySkillAtom())
							{
								pOutTarget = pActor;
								return i;
							}
						}
					}

				}

			}
		}


	}

	return -1;
}