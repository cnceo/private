// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_ClubMemberMgr.generated.h"

#define UMGAssetPath_ClubMember  FString(TEXT("/Game/UI/UMG/MartialClub/MemberManage.MemberManage_C"))
#define UMGAssetPath_MemberLabel  FString(TEXT("/Game/UI/UMG/MartialClub/MemberItem.MemberItem_C"))
/**
 * 
 */
UCLASS()
class PANDA_API UPandaWidget_ClubMemberMgr : public UPandaWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	//////////////////////////////////////////////////////////////////////////
	// 成员列表
	UScrollBox* Memberlist;
	// 成员总数
	UTextBlock* MemberMaxNum;


public:
	// 初始化对话框
	void InitCreateClubMemver(int inNPCID, APlayerCharacter* inPlayer);

	// 选择的对话项
	void SelectTalkLabel(int inIndex);
	// 设置层级改变
//	void ChanePanelLayerState(ClubPanelState inState);

	/** 圈*/
	virtual void OnCircle() override;
	/** 叉*/
	virtual void OnCross() override;

private:
	// 可以创建
	bool CanCreateClub;
	// 选择的IconIndex
	int SelectIconIndex;
//	ClubPanelState PanelState;
};
