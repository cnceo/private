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


class FSelectCharacterTableData : public FGameData
{

public:

	FSelectCharacterTableData();
	~FSelectCharacterTableData();

	virtual void Init() override;
	virtual void Serialize() override;

	TArray<class FProfession*>& GetProfessionDataList();
	TArray<class FRace*>& GetRaceDataList();

private:

	TArray<class FProfession*> ProfessionDataList;
	TArray<class FRace*> RaceDataList;
};


