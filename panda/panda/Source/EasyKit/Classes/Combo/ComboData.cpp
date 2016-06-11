// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "ComboData.h"


//////////////////////////////////////////////////////////////////////////
// UCurveBase

UComboData::UComboData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UComboData::GetTimeRange(float& MinTime, float& MaxTime) const
{

}

void UComboData::GetValueRange(float& MinValue, float& MaxValue) const
{

}

void UComboData::ModifyOwner()
{
	Modify(true);
}

void UComboData::MakeTransactional()
{
	SetFlags(GetFlags() | RF_Transactional);
}



TArray<FString> UComboData::CreateComboFromCSVString(const FString& InString)
{
	// Array used to store problems about curve import
	TArray<FString> OutProblems;


	Modify(true);
	return OutProblems;
}
