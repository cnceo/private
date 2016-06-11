//
// EKResourceManager.h
//
// 游戏流程管理器 用于加载资源 和 实例化资源用
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "Engine.h"
#include "Object.h"
#include "EKResourceManager.generated.h"

/**
 * 
 */
UCLASS()
class EASYKIT_API UEKResourceManager : public UObject
{
public:

	GENERATED_UCLASS_BODY()

	// 从路径加载资源
	UPackage* LoadResource(FString inPath);
	
	// 实例化对象
	class AActor* Instance(UObject* inAsset);
	class AActor* Instance(UObject* inAsset, FVector& inVect, FRotator& inRotat);

	void InstancePackag(UPackage* inPackag, FVector& inVect, FRotator& inRotat);

	void InstanceAllObjcet(TArray<UObject*> inObjects, FVector& inVect, FRotator& inRotat);

	void init();

public:

	UObject * GetEKObject(const FString &);

	// This input must be TEXT("xxx/xxx.xxx_C")
	UBlueprintGeneratedClass * GetEKBlueprintClass(const FString &);

	TArray<class UEasyKit_ActorFactory*> m_ActorFactories;
};
