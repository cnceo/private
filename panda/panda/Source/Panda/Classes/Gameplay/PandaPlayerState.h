// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "PandaPlayerState.generated.h"

/**
 * 人物数据持久化
 */
UCLASS()
class PANDA_API APandaPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	//////////////////////////////////////////////////////////////////////////
	// 武馆相关
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	int32 MartialclubID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	class UMartialclubData*  Martialclub;
};
