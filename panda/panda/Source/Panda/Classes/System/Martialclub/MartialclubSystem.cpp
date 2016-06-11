// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "MartialclubSystem.h"
#include "EKGameFrame.h"
#include "UnrealType.h"
#include "EKLogManager.h"


//////////////////////////////////////////////////////////////////////////
// ��ݳ�Ա
UMartialclubMember::UMartialclubMember(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

//-----replicated
void UMartialclubMember::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_TaskId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_ConditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_PreconditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_emTaskProgress, COND_OwnerOnly);

	//DOREPLIFETIME(UQuestComponent, m_TaskContainer);

}

//////////////////////////////////////////////////////////////////////////
// ��ݽ���
UMartialclubBuild::UMartialclubBuild(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

//-----replicated
void UMartialclubBuild::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_TaskId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_ConditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_PreconditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_emTaskProgress, COND_OwnerOnly);

	//DOREPLIFETIME(UQuestComponent, m_TaskContainer);

}

//////////////////////////////////////////////////////////////////////////
// �������
UMartialclubData::UMartialclubData(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

//-----replicated
void UMartialclubData::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_TaskId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_ConditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_PreconditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_emTaskProgress, COND_OwnerOnly);

	//DOREPLIFETIME(UQuestComponent, m_TaskContainer);

}

void UMartialclubData::AddClubMember(UMartialclubMember* inMember)
{
	if (MartialclubMemberList.Num() == 0)
	{
		MartialclubMemberList.Add(inMember);
	}
	else if (MartialclubMemberList.Find(inMember) == INDEX_NONE)
	{
		MartialclubMemberList.Add(inMember);
	}
}

void UMartialclubData::AddClubBuild(UMartialclubBuild* inBuild)
{
	if (MartialclubBuildList.Num() == 0)
	{
		MartialclubBuildList.Add(inBuild);
	}
	if (MartialclubBuildList.Find(inBuild) == INDEX_NONE)
	{
		MartialclubBuildList.Add(inBuild);
	}
}

UMartialclubSystem::UMartialclubSystem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ClubList.Empty();
}


void UMartialclubSystem::InitDefaults()
{
	// ����
}

bool UMartialclubSystem::IsSupportedForNetworking() const
{
	bool ret = Super::IsSupportedForNetworking();
	return true;
}

// ϵͳ��ʼ��
void UMartialclubSystem::Init()
{
	// �������� ��������
}

// �������
void UMartialclubSystem::EnterClub(int inClubID)
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_Club);
}

// �������
UMartialclubData* UMartialclubSystem::CreateClub(class APlayerCharacter* inPlayer, FString inClubName)
{
	int ClubNum = ClubList.Num();
	UMartialclubData* clubdata = NewObject<UMartialclubData>(this, *FString::Printf(TEXT("Club_%d"), ClubNum), RF_MarkAsRootSet);
	
	// ���ID
	clubdata->ClubID = ClubNum;
	clubdata->ClubName = inClubName;
	clubdata->ClubLevel = 1;

	// ��������
	UMartialclubBuild* clubbulid1 = NewObject<UMartialclubBuild>(clubdata, TEXT("ClubBuild_����"), RF_MarkAsRootSet);
	clubbulid1->BuildName = TEXT("����");
	clubbulid1->BuildLevel = 1;
	clubbulid1->BuildState = 0;
	clubdata->AddClubBuild(clubbulid1);
	UMartialclubBuild* clubbulid2 = NewObject<UMartialclubBuild>(clubdata, TEXT("ClubBuild_ľ��׮"), RF_MarkAsRootSet);
	clubbulid2->BuildName = TEXT("ľ��׮");
	clubbulid2->BuildLevel = 1;
	clubbulid2->BuildState = 0;
	clubdata->AddClubBuild(clubbulid2);
	UMartialclubBuild* clubbulid3 = NewObject<UMartialclubBuild>(clubdata, TEXT("ClubBuild_ɳ��"), RF_MarkAsRootSet);
	clubbulid3->BuildName = TEXT("ɳ��");
	clubbulid3->BuildLevel = 1;
	clubbulid3->BuildState = 0;
	clubdata->AddClubBuild(clubbulid3);

	// ������Ա
	UMartialclubMember* clubmembr = NewObject<UMartialclubMember>(clubdata,  *inPlayer->GetName(), RF_MarkAsRootSet);
	clubmembr->MemberName = inPlayer->GetName();
	clubmembr->MemberLevel;
	clubmembr->MemberOnline = true;
	clubdata->AddClubMember(clubmembr);

	// ���ӵ�����б�
	ClubList.Add(ClubNum, clubdata);

	FPlayerDataManager::Instance()->setMartialclubID(ClubNum);

	return clubdata;
}

UMartialclubData* UMartialclubSystem::GetMartialclub(int inClubID)
{
	if (ClubList.Num() == 0)
		return nullptr;

	return *ClubList.Find(inClubID);
}

//-----replicated
void UMartialclubSystem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_TaskId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_ConditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_PreconditionId, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UMartialclubSystem, m_emTaskProgress, COND_OwnerOnly);

	//DOREPLIFETIME(UQuestComponent, m_TaskContainer);

}