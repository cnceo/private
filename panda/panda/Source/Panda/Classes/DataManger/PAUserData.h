// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserData.h
//  Panda
//  User Base Data/User Extra Data
//  Created by White.tian on 2016-05-13 14:40:50.
//  Copyright (c) 2016年 White.tian All rights reserved.
//
#include "PAUserData.generated.h"

#pragma once

/* 服务器数据 */
USTRUCT(BlueprintType)
struct FsPAZoneInfo{

public:
	GENERATED_USTRUCT_BODY()

	int32 id;					// 服务器ID
	int32 version;				// 服务器版本
	FString ip;					// 服务器ip
	int32 port;					// 服务器端口
	int32 occupied;				// 服务器已占有多少用量
	int32 capacity;				// 服务器容量
	FString desc;				// 服务器描述
	int32 status;				// 服务器状态 0 运行中 1 停机维护中
	int32 timeZone;				// 服务器时区
	int32 now;					// 服务器当前时间   
	int32 openTime;				// 开服时间
	int32 maintainStart;		// 维护开始时间
	int32 maintainEnd;			// 维护结束时间

	FsPAZoneInfo()
		: id(0)
		, version(0)
		, ip(TEXT(""))
		, port(0.f)
		, occupied(0.f)
		, capacity(0.f)
		, desc(TEXT(""))
		, status(0)
		, timeZone(0)
		, now(0)
		, openTime(0)
		, maintainStart(0)
		, maintainEnd(0)
	{

	}
};

/* 上次玩家处于的位置 */
USTRUCT(BlueprintType)
struct FsPAPlaceInfo
{
public:
	GENERATED_USTRUCT_BODY()

	int32 zid;					// zone
	int32 nMapId;				// mapid
	float x;					// x
	float y;					// y
	float z;					// z
	int32 orientation;			// in degree

	FsPAPlaceInfo()
		: zid(0)
		, nMapId(0)
		, x(0.f)
		, y(0.f)
		, z(0.f)
		, orientation(0)
	{

	}
};

/* 玩家信息, 该服务器下的角色信息, 如果没有创建过角色该字段为空 */
USTRUCT(BlueprintType)
struct FsPAPlayerInfo
{
public:
	GENERATED_USTRUCT_BODY()

	int32 id;						// 多角色ID
	FString name;					// 角色名
	int32 level;					// 角色等级     
	int32 energy;					// 角色当前体力
	int32 energyTime;				// 最近一次更新体力的时间
	int32 exp;						// 玩家当前经验
	int32 gold;						// 玩家当前钻石
	int32 money;					// 玩家当前金币
	int32 honor;					// 玩家当前荣誉
	FsPAPlaceInfo lastPlace;		// 上次的位置信息

	FString CurrentTitle;			// 当前称号
	FString ArenaRank;				// 竞技场军衔
	FString ArenaHonor;				// 竞技场荣誉值	
	int32 HuashanRanking;			// 华山论剑排名
	int32 MartialclubID;			// 武馆ID
	
	FsPAPlayerInfo()
		: id(0)
		, name(TEXT(""))
		, level(0)
		, energy(0)
		, energyTime(0)
		, exp(0)
		, gold(0)
		, money(0)
		, honor(0)
		/*, lastPlace(nullptr)*/
		, CurrentTitle(TEXT(""))
		, ArenaRank(TEXT(""))
		, ArenaHonor(TEXT(""))
		, HuashanRanking(0)
		{

		}
};

/* 额外的角色信息 */
USTRUCT(BlueprintType)
struct FsPAPlayerExtraInfo
{
public:
	GENERATED_USTRUCT_BODY()

	FsPAPlayerExtraInfo()
	{

	}
	//...
};


/**
 * 
 */
class PANDA_API PAUserData
{
public:
	PAUserData();
	~PAUserData();
};