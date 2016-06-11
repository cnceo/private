//
// EKItemObject.h
//
// 所有物品基类
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
// 

#pragma once


#include "GameFramework/Actor.h"
#include "EKItemObject.generated.h"

/**
 * 
 */
UCLASS()
class EASYKIT_API AEKItemObject : public AActor
{
	GENERATED_UCLASS_BODY()

	/** GUID  Server Crate ID */
	UPROPERTY()
	int32 ItemID;

	/** Item Icon ID */
	UPROPERTY()
	int32 ItemIconID;

	/** Item is Name */
	UPROPERTY()
	FString ItemName;
	
};
