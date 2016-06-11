// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "GameSystem.h"
#include "EKGameFrame.h"
#include "UnrealType.h"
#include "EKLogManager.h"
#include "Martialclub/MartialclubSystem.h"


//////////////////////////////////////////////////////////////////////////
// ��ݳ�Ա
UGameSystem::UGameSystem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}


FGameSystemManager::FGameSystemManager() 
{ 
	GameSystemMap.Empty(); 
}

// �ȳ�ʼ��ϵͳ ��ϵͳע�ᵽ����
void FGameSystemManager::InitSystem() 
{
	UMartialclubSystem* system = NewObject<UMartialclubSystem>(GGameInstance, TEXT("MartialclubSystem"), RF_MarkAsRootSet);
	GameSystemMap.Add("MartialclubSystem", Cast<UGameSystem>(system));
}

void FGameSystemManager::Init() 
{
	if (GameSystemMap.Num() > 0)
	{
		for (auto system : GameSystemMap)
		{
			system.Value->Init();
		}
	}
}


//template< class* T > FGameSystemManager::GetGameSystem()
//{
//	for (auto system : GameSystemMap)
//	{
//		if (system.Value->GetClass() == T::StaticClass())
//			return Cast<T>(system.Value);
//	}
//}