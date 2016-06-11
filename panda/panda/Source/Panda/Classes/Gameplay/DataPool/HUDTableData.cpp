// Copyright 1998-2014 xishanju Games, Inc. All Rights Reserved.

#include "panda.h"
#include "GameData.h"
#include "EKHUDManager.h"
#include "HUDTableData.h"
#include "UMGPanel.h"



FHUDTableData::FHUDTableData()
{

};

void FHUDTableData::Init()
{
	//////////////////////////////////////////////////////////////////////////
	// 临时测试  请填充表数据
	FUMGPanel* CreateCharwindos = new FUMGPanel();

	CreateCharwindos->sWidgetName = TEXT("CreateChar");
	CreateCharwindos->sWidgetPath = TEXT("/Game/UI/UMG/CreateChar/CreateChar.CreateChar_C");
	CreateCharwindos->bAotoGC = true;
	CreateCharwindos->nMutexLevel = 1;

	HUDTableTArray.Add(CreateCharwindos);

	//////////////////////////////////////////////////////////////////////////
	// 临时测试  请填充表数据
	FUMGPanel* SelectCharWindos = new FUMGPanel();

	SelectCharWindos->sWidgetName = TEXT("SelectChar");
	SelectCharWindos->sWidgetPath = TEXT("/Game/UI/UMG/SelectChar/SelectChar.SelectChar_C");
	SelectCharWindos->bAotoGC = true;
	SelectCharWindos->nMutexLevel = 1;

	HUDTableTArray.Add(SelectCharWindos);
}

void FHUDTableData::Serialize()
{

}

TArray<FUMGPanel*>& FHUDTableData::GetHUDTableData()
{
	return HUDTableTArray;
}
