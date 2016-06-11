//
// HUDTableData.h
//
// UIµƒ≈‰÷√±Ì
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "GameData.h"


class FHUDTableData : public FGameData
{

public:

	FHUDTableData();
	~FHUDTableData();

	virtual void Init() override;
	virtual void Serialize() override;

	TArray<class FUMGPanel*>& GetHUDTableData();

private:

	TArray<class FUMGPanel*> HUDTableTArray;
};


