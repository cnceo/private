// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "CombatAsset.h"

UCombatAsset::UCombatAsset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}
//
//UClass* UCombatAsset::GetPrivateStaticClass(wchar_t const *)
//{
//	return nullptr;
//}

#if WITH_EDITORONLY_DATA
void UCombatAsset::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsLoading() && (Ar.UE4Ver() < VER_UE4_ADD_TRANSACTIONAL_TO_DATA_ASSETS))
	{
		SetFlags(RF_Transactional);
	}
}
#endif

void UCombatAsset::ModifyOwner()
{
	Modify(true);
}

void UCombatAsset::MakeTransactional()
{
	SetFlags(GetFlags() | RF_Transactional);
}



TArray<FString> UCombatAsset::CreateComboFromCSVString(const FString& InString)
{
	// Array used to store problems about curve import
	TArray<FString> OutProblems;


	Modify(true);
	return OutProblems;
}

