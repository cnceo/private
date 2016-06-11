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
	// 系统是否可以使用
	virtual bool CanUseSystem() { return true; };
	// 系统初始化
	virtual void Init() {};

public:

};

class PANDA_API FGameSystemManager
{
	
public:
	FGameSystemManager();

public:
	// 先初始化系统 把系统注册到里面
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

	// 得到系统
	template< class T >
	T* GetGameSystem()
	{
		return Cast<T>(GetGameSystem(T::StaticClass()));	
	}

private:

	TMap<FString, class UGameSystem*> GameSystemMap;
};

