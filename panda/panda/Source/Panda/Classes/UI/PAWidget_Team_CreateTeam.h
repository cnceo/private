// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAWidget_Team_CreateTeam.h
//  Panda
//  PA Create Team UI DATA Pool
//  Created by White.tian on 2016-05-18 14:21:27
//  Copyright (c) 2016Äê White.tian All rights reserved.
//

#pragma once

#include "UI/PandaWidget.h"
#include "PAWidget_Team_CreateTeam.generated.h"

/**
 *	#define UI_CREATE_TEAM  TEXT("/Game/UI/UMG/Team/CreateTeam.CreateTeam_C")
 */
UCLASS()
class PANDA_API UPAWidget_Team_CreateTeam : public UPandaWidget
{
	GENERATED_BODY()

public:
	UPAWidget_Team_CreateTeam();
	~UPAWidget_Team_CreateTeam();

public:
	virtual void NativeConstruct() override;
	virtual void UpdateSelf(float deltaTime) override;

	// Exit
	virtual void OnCross() override;
	virtual void OnCircle() override;
};