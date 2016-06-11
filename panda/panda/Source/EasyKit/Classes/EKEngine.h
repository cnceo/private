//
// EKEngine.h
//
// 游戏引擎或启动游戏入口类
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "Engine/GameEngine.h"
#include "EKEngine.generated.h"


/**
 * 
 */
UCLASS()
class EASYKIT_API UEKEngine : public UGameEngine
{
private:

	GENERATED_UCLASS_BODY()

	UPROPERTY(config)
	bool bUseNetwork;

	UPROPERTY(config)
	int32 nPort;

	UPROPERTY(config)
	FString sIP;

	/**
	 * The init func that create GameInstance and init the first GWorld/Map.
	 * Init first/default game logic EKProcedure and EKScene.
	 */
	virtual void Init(class IEngineLoop* InEngineLoop) override;

	virtual bool LoadMap(FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error) override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;

	class FEKGameFrame* EKGame;
	class UEKGameInstance* EKGameInstance;
};


