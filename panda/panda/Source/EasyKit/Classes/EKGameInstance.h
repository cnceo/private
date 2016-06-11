// Copyright 1995-2014 ��ɽ��. All Rights Reserved.
// Created by ��ǫ on Oct 20, 2014

/*=============================================================================
The main manager module for the specific game.
=============================================================================*/

#pragma once

#include "Engine/GameInstance.h"
#include "EKGameInstance.generated.h"


UCLASS()
class EASYKIT_API UEKGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()
public:
	
	/**
	 * This Init function is before the first game world initialization
	 * It is the "PreInit" function for the InitGameProcess func, i.e. before GWorld.
	 */
	virtual void Init() override;

	/**
	 * This Init function is after GWorld has been init.
	 * All objects that required GWorld to init should be place in this func.
	 * ���õ�һ������
	 */
	virtual void PostInit();

	/**
	 * Init network modules
	 */
	virtual void InitNetwork();

	/**
	 * Init All game logic procedures and scenes.
	 * �������ʼ���������̺ͳ���
	 */
	virtual void InitGameProcedure();

	virtual void SpawnPawn(){};
	virtual void SpawnController(){};

};