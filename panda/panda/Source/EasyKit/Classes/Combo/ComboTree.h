// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once


#include "Engine/Blueprint.h"
#include "Combo/ComboData.h"
#include "ComboTree.generated.h"

UCLASS(BlueprintType)
class EASYKIT_API UComboTree : public UObject
{
	GENERATED_UCLASS_BODY()

	///** root node of loaded tree */
	//UPROPERTY()
	//class UBTCompositeNode* RootNode;

#if WITH_EDITORONLY_DATA

	/** Graph for Behavior Tree */
	UPROPERTY()
	class UEdGraph*	BTComboGraph;

	/** Info about the graphs we last edited */
	UPROPERTY()
		TArray<FEditedDocumentInfo> LastEditedDocuments;

#endif

	/** ComboData asset for this tree */
	UPROPERTY()
	class UComboData* ComboDataAsset;

	///** root level decorators, used by subtrees */
	//UPROPERTY()
	//TArray<class UBTDecorator*> RootDecorators;

	///** logic operators for root level decorators, used by subtrees  */
	//UPROPERTY()
	//TArray<FBTDecoratorLogic> RootDecoratorOps;

	/** memory size required for instance of this tree */
	uint16 InstanceMemorySize;
};
