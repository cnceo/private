// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSystem.h"
#include "MartialclubSystem.generated.h"


/** ��ݳ�Ա*/
UCLASS()
class PANDA_API UMartialclubMember : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	//	��ҽ�ɫID
	UPROPERTY(Replicated)
	int32 PlayerID;
	// ��Ա����
	UPROPERTY(Replicated)
	FString MemberName;
	// ��Ա�ȼ�
	UPROPERTY(Replicated)
	int32 MemberLevel;
	// ��Ա����������
	UPROPERTY(Replicated)
	int32 MemberJJCNum;
	////	��Ա����
	//UPROPERTY(Replicated)
	//int32 MemberState;
	//	��ԱȨ��
	UPROPERTY(Replicated)
	int32 MemberRestrict;
	//	�Ƿ�����
	UPROPERTY(Replicated)
	bool MemberOnline;
};

/** ��ݽ���*/
UCLASS()
class PANDA_API UMartialclubBuild : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	// ��������
	UPROPERTY(Replicated)
	FString BuildName;
	// �����ȼ�
	UPROPERTY(Replicated)
	int32 BuildLevel;
	// ��������
	UPROPERTY(Replicated)
	int32 BuildType;
	// ����״̬
	UPROPERTY(Replicated)
	int32 BuildState;
};

/** �������*/
UCLASS()
class PANDA_API UMartialclubData : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	// ���ID
	UPROPERTY(Replicated)
	int32 ClubID;
	// �������
	UPROPERTY(Replicated)
	FString ClubName;
	// ��ݵȼ�
	UPROPERTY(Replicated)
	int32 ClubLevel;
	// ���ͼ��ID
	UPROPERTY(Replicated)
	int32 ClubIconID;
	// ���״̬
	UPROPERTY(Replicated)
	int32 ClubState;

	// �����б�
	TArray<class UMartialclubBuild*> MartialclubBuildList;
	// �����б�
	TArray<class UMartialclubMember*> MartialclubMemberList;
	// ���ӳ�Ա
	void AddClubMember(class UMartialclubMember* inMember);
	// ���ӽ���
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
	// �ȼ�����
	UPROPERTY(Replicated)
	int  LevelLimit;


public:
	void InitDefaults(/*int TaskId*/);
	virtual void Init() override;
	// �������
	void EnterClub(int inClubID);
	// �������
	UMartialclubData* CreateClub(class APlayerCharacter* inPlayer, FString inClubName="��");

	UMartialclubData* GetMartialclub(int inClubID);

public:

	virtual bool IsSupportedForNetworking() const override;

	TMap<int32, class UMartialclubData*> ClubList;
};
