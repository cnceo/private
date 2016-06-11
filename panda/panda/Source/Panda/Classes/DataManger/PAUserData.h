// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserData.h
//  Panda
//  User Base Data/User Extra Data
//  Created by White.tian on 2016-05-13 14:40:50.
//  Copyright (c) 2016�� White.tian All rights reserved.
//
#include "PAUserData.generated.h"

#pragma once

/* ���������� */
USTRUCT(BlueprintType)
struct FsPAZoneInfo{

public:
	GENERATED_USTRUCT_BODY()

	int32 id;					// ������ID
	int32 version;				// �������汾
	FString ip;					// ������ip
	int32 port;					// �������˿�
	int32 occupied;				// ��������ռ�ж�������
	int32 capacity;				// ����������
	FString desc;				// ����������
	int32 status;				// ������״̬ 0 ������ 1 ͣ��ά����
	int32 timeZone;				// ������ʱ��
	int32 now;					// ��������ǰʱ��   
	int32 openTime;				// ����ʱ��
	int32 maintainStart;		// ά����ʼʱ��
	int32 maintainEnd;			// ά������ʱ��

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

/* �ϴ���Ҵ��ڵ�λ�� */
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

/* �����Ϣ, �÷������µĽ�ɫ��Ϣ, ���û�д�������ɫ���ֶ�Ϊ�� */
USTRUCT(BlueprintType)
struct FsPAPlayerInfo
{
public:
	GENERATED_USTRUCT_BODY()

	int32 id;						// ���ɫID
	FString name;					// ��ɫ��
	int32 level;					// ��ɫ�ȼ�     
	int32 energy;					// ��ɫ��ǰ����
	int32 energyTime;				// ���һ�θ���������ʱ��
	int32 exp;						// ��ҵ�ǰ����
	int32 gold;						// ��ҵ�ǰ��ʯ
	int32 money;					// ��ҵ�ǰ���
	int32 honor;					// ��ҵ�ǰ����
	FsPAPlaceInfo lastPlace;		// �ϴε�λ����Ϣ

	FString CurrentTitle;			// ��ǰ�ƺ�
	FString ArenaRank;				// ����������
	FString ArenaHonor;				// ����������ֵ	
	int32 HuashanRanking;			// ��ɽ�۽�����
	int32 MartialclubID;			// ���ID
	
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

/* ����Ľ�ɫ��Ϣ */
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