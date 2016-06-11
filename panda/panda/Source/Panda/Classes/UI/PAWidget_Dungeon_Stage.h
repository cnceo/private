// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAWidget_Dungeon_Stage.h
//  Panda
//  Scene Stage UI.
//  Created by White.tian on 2016-05-18 17:28:46
//  Copyright (c) 2016Äê White.tian All rights reserved.
//

#pragma once

#include "UI/PandaWidget.h"
#include "PAWidget_Dungeon_Stage.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API UPAWidget_Dungeon_Stage : public UPandaWidget
{
	GENERATED_BODY()
	
public:
	UPAWidget_Dungeon_Stage();
	~UPAWidget_Dungeon_Stage();

public:
	virtual void NativeConstruct() override;
	virtual void UpdateSelf(float deltaTime) override;

	// Exit
	virtual void OnCross() override;
	virtual void OnCircle() override;
};
