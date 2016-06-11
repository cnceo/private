// Copyright 1998-2014 xishanju Games, Inc. All Rights Reserved.

#include "panda.h"
#include "PandaDataPool.h"
#include "EKGameFrame.h"
#include "GameData.h"
#include "HUDTableData.h"
#include "SelectCharacterTableData.h"



FPandaDataPool* FPandaDataPool::pDataPool = nullptr;


FPandaDataPool::FPandaDataPool()
{
	FHUDTableData* HUDTable = new FHUDTableData();
	mDataPoolMap.Add(DataPool::DATA_HUDTable, HUDTable);

	FSelectCharacterTableData* SelectCharTable = new FSelectCharacterTableData();
	mDataPoolMap.Add(DataPool::DATA_SelectChar, SelectCharTable);
}

FPandaDataPool::~FPandaDataPool()
{
	if (pDataPool)
	{
		delete pDataPool;
		pDataPool = nullptr;
	}
}

FPandaDataPool* FPandaDataPool::Instance()
{
	if (pDataPool == NULL)
	{
		pDataPool = new FPandaDataPool();
		UE_LOG(LogScript, Warning, TEXT(" Panda Data Pool Created !! "));
	}

	return pDataPool;
}

void FPandaDataPool::Init()
{
	for (auto data : mDataPoolMap)
	{
		data.Value->Init();
	}
}

void FPandaDataPool::Serialize()
{
	for (auto &data : mDataPoolMap)
	{
		data.Value->Serialize();
	}
}


FGameData* FPandaDataPool::GetData(DataPool::DataType inType)
{
	return *(mDataPoolMap.Find(inType));
}
