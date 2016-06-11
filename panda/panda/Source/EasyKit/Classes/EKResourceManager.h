//
// EKResourceManager.h
//
// ��Ϸ���̹����� ���ڼ�����Դ �� ʵ������Դ��
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

	// ��·��������Դ
	UPackage* LoadResource(FString inPath);
	
	// ʵ��������
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
