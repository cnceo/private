//
// TitanDataPool.h
//
// 单例 数据池. 表现跟数据分开
//
// Created by  EasyKit Team's Geometry Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#define MAX_TYPEID_PLAYER 1000
#define MIN_TYPEID_PLAYER 0

#define MAX_Z 99999
#define MIN_Z -99999

namespace DataPool
{
	enum DataType
	{
		DATA_SelectChar,
		DATA_PayerData,
		DATA_HUDTable,
		DATA_Tree,
		DATA_ObjectPool,
		DATA_Resource
	};
}



class FPandaDataPool 
{
	static FPandaDataPool* pDataPool;

public:

	virtual void Init();
	virtual void Serialize();

	static FPandaDataPool* Instance();

	class FGameData* GetData(DataPool::DataType inType);

	class UGameDataTable* GetDataTable() { return gameDataTable; }

private:

	FPandaDataPool();
	virtual ~FPandaDataPool();

	TMap<DataPool::DataType, class FGameData*> mDataPoolMap;

	class UGameDataTable* gameDataTable;

	// 数据持久化
	//TArray<>
};


