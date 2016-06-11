// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "PandaPlayerState.generated.h"

/**
 * �������ݳ־û�
 */
UCLASS()
class PANDA_API APandaPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	//////////////////////////////////////////////////////////////////////////
	// ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	int32 MartialclubID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	class UMartialclubData*  Martialclub;
};
