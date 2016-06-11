// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_SearchClub.generated.h"

#define UMGAssetPath_SearchClub  FString(TEXT("/Game/UI/UMG/MartialClub/SearchClub.SearchClub_C"))
#define UMGAssetPath_SearchClubLabel  FString(TEXT("/Game/UI/UMG/MartialClub/ManageItem.ManageItem_C"))
/**
 * 
 */
UCLASS()
class PANDA_API UPandaWidget_SearchClub : public UPandaWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	//////////////////////////////////////////////////////////////////////////
	// 武馆列表
	UScrollBox* ClubLabellist;
	// 武馆描述列表
	UScrollBox* FacilitiesList;
	// 武馆图标
	UImage*		BannerIcon;

public:
	// 初始化武馆搜索
	void InitCreateSearchClub(int inNPCID, APlayerCharacter* inPlayer);

	// 选择的对话项
	void SelectSearchClubLabel(int inIndex);
	// 设置层级改变
//	void ChanePanelLayerState(ClubPanelState inState);

	/** 圈*/
	virtual void OnCircle() override;
	/** 叉*/
	virtual void OnCross() override;

private:
	// 选择的对话
	UWidget* CurrentLabel;
	// 选择的IconIndex
	int SelectIconIndex;
	ClubPanelState PanelState;
};
