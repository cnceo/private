//
// CombatAsset.h
//
// 游戏技能系统数据
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "CombatAsset.generated.h"


/** Base class for a simple asset containing data */
UCLASS()
class EASYKIT_API UCombatAsset : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	virtual UObject* GetOwner()
	{
		return this;
	}

	// Begin UCurveBase interface
	/** 
	*	Create curve from CSV style comma-separated string. 
	*	@return	Set of problems encountered while processing input
	*/
	TArray<FString> CreateComboFromCSVString(const FString& InString);

	virtual void ModifyOwner();
	virtual void MakeTransactional();

	// UObject interface
#if WITH_EDITORONLY_DATA
	virtual void Serialize(FArchive& Ar) override;
#endif
	// End of UObject interface
};