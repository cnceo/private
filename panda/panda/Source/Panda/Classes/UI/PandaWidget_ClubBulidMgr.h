// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_ClubBulidMgr.generated.h"

#define UMGAssetPath_ClubBulid  FString(TEXT("/Game/UI/UMG/MartialClub/Facilities.Facilities_C"))
#define UMGAssetPath_ClubBulidItem  FString(TEXT("/Game/UI/UMG/MartialClub/FacilitiesItem.FacilitiesItem_C"))
/**
 * 
 */
UCLASS()
class PANDA_API UPandaWidget_ClubBulidMgr : public UPandaWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	//////////////////////////////////////////////////////////////////////////
	// 建筑列表
	UScrollBox* SandbagList;
	// 建筑描述
	UTextBlock* BulidDescribe;

public:
	// 初始化对话框
	void InitCreateClubBulid(int inNPCID, APlayerCharacter* inPlayer);

	// 选择的对话项
	void SelectTalkLabel(int inIndex);
	// 设置层级改变
	//void ChanePanelLayerState(ClubPanelState inState);

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
