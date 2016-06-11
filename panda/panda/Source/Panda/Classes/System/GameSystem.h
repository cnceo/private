// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "GameSystem.generated.h"

/**
 *
 */
UCLASS()
class PANDA_API UGameSystem : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	// ϵͳ�Ƿ����ʹ��
	virtual bool CanUseSystem() { return true; };
	// ϵͳ��ʼ��
	virtual void Init() {};

public:

};

class PANDA_API FGameSystemManager
{
	
public:
	FGameSystemManager();

public:
	// �ȳ�ʼ��ϵͳ ��ϵͳע�ᵽ����
	void InitSystem();

	bool CanUseSystem();
	void Init();

	UGameSystem* GetGameSystem(UClass* Class)
	{
		for (auto system : GameSystemMap)
		{
			if (system.Value->GetClass() == Class)
				return system.Value;
		}
		return nullptr;
	}

	// �õ�ϵͳ
	template< class T >
	T* GetGameSystem()
	{
		return Cast<T>(GetGameSystem(T::StaticClass()));	
	}

private:

	TMap<FString, class UGameSystem*> GameSystemMap;
};

