// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ComboData.generated.h"


//////////////////////////////////////////////////////////////////////////

/**
 * Defines a curve of interpolated points to evaluate over a given range
 */
UCLASS()
class EASYKIT_API UComboData : public UObject
{
	GENERATED_UCLASS_BODY()

	/** The filename imported to create this object. Relative to this object's package, BaseDir() or absolute */
	UPROPERTY()
	FString ImportPath;

	/** Get the time range across all curves */
	UFUNCTION(BlueprintCallable, Category="Math|Comboes")
	void GetTimeRange(float& MinTime, float& MaxTime) const;

	/** Get the value range across all curves */
	UFUNCTION(BlueprintCallable, Category="Math|Comboes")
	void GetValueRange(float& MinValue, float& MaxValue) const;

public:

	virtual TArray<UComboData> GetUCombo() 
	{
		TArray<UComboData> Curves;
		return Curves;
	}

	virtual UObject* GetOwner() 
	{
		return this;
	}

	virtual void ModifyOwner();
	virtual void MakeTransactional();
	// End FCurveOwnerInterface

	// Begin UCurveBase interface
	/** 
	 *	Create curve from CSV style comma-separated string. 
	 *	@return	Set of problems encountered while processing input
	 */
	TArray<FString> CreateComboFromCSVString(const FString& InString);
	
	/** blackboard keys */

	// End UCurveBase interface

};
