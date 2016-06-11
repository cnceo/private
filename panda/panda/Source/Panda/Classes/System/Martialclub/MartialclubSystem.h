// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSystem.h"
#include "MartialclubSystem.generated.h"


/** 武馆成员*/
UCLASS()
class PANDA_API UMartialclubMember : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	//	玩家角色ID
	UPROPERTY(Replicated)
	int32 PlayerID;
	// 成员名字
	UPROPERTY(Replicated)
	FString MemberName;
	// 成员等级
	UPROPERTY(Replicated)
	int32 MemberLevel;
	// 成员竞技场积分
	UPROPERTY(Replicated)
	int32 MemberJJCNum;
	////	成员级别
	//UPROPERTY(Replicated)
	//int32 MemberState;
	//	成员权限
	UPROPERTY(Replicated)
	int32 MemberRestrict;
	//	是否在线
	UPROPERTY(Replicated)
	bool MemberOnline;
};

/** 武馆建筑*/
UCLASS()
class PANDA_API UMartialclubBuild : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	// 建筑名字
	UPROPERTY(Replicated)
	FString BuildName;
	// 建筑等级
	UPROPERTY(Replicated)
	int32 BuildLevel;
	// 建筑类型
	UPROPERTY(Replicated)
	int32 BuildType;
	// 建筑状态
	UPROPERTY(Replicated)
	int32 BuildState;
};

/** 武馆数据*/
UCLASS()
class PANDA_API UMartialclubData : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	// 武馆ID
	UPROPERTY(Replicated)
	int32 ClubID;
	// 武馆名字
	UPROPERTY(Replicated)
	FString ClubName;
	// 武馆等级
	UPROPERTY(Replicated)
	int32 ClubLevel;
	// 武馆图标ID
	UPROPERTY(Replicated)
	int32 ClubIconID;
	// 武馆状态
	UPROPERTY(Replicated)
	int32 ClubState;

	// 建筑列表
	TArray<class UMartialclubBuild*> MartialclubBuildList;
	// 建筑列表
	TArray<class UMartialclubMember*> MartialclubMemberList;
	// 增加成员
	void AddClubMember(class UMartialclubMember* inMember);
	// 增加建筑
	void AddClubBuild(class UMartialclubBuild* inBuild);
};

/**
 *
 */
UCLASS()
class PANDA_API UMartialclubSystem : public UGameSystem
{
	GENERATED_UCLASS_BODY()
public:
	// 等级限制
	UPROPERTY(Replicated)
	int  LevelLimit;


public:
	void InitDefaults(/*int TaskId*/);
	virtual void Init() override;
	// 进入武馆
	void EnterClub(int inClubID);
	// 创建武馆
	UMartialclubData* CreateClub(class APlayerCharacter* inPlayer, FString inClubName="无");

	UMartialclubData* GetMartialclub(int inClubID);

public:

	virtual bool IsSupportedForNetworking() const override;

	TMap<int32, class UMartialclubData*> ClubList;
};
