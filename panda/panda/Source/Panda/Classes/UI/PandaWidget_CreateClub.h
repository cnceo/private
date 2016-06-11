// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_CreateClub.generated.h"

#define UMGAssetPath_CreatClub  FString(TEXT("/Game/UI/UMG/MartialClub/CreatClub.CreatClub_C"))

// 面板状态
UENUM()
enum ClubPanelState
{
	Create_Condition,
	Create_Artst,
};
/**
 * 创建武馆的面板  
 */
UCLASS()
class PANDA_API UPandaWidget_CreateClub : public UPandaWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	//////////////////////////////////////////////////////////////////////////
	// Create
	UCanvasPanel* CreateCondition;
	// 条件列表
	UScrollBox* ConditionList;
	//////////////////////////////////////////////////////////////////////////
	// Artst
	UCanvasPanel* CreateArtst;
	// 创建武馆的名字
	UEditableTextBox* InputName;
	// Icon列表
	UScrollBox* ClubIconList;

public:
	// 初始化对话框
	void InitCreateClub(int inNPCID, APlayerCharacter* inPlayer);
	// 初始化对话框
	void InitClubArtst();

	// 选择的对话项
	void SelectTalkLabel(int inIndex);
	// 设置层级改变
	void ChanePanelLayerState(ClubPanelState inState);

	/** 圈*/
	virtual void OnCircle() override;
	/** 叉*/
	virtual void OnCross() override;

private:
	// 可以创建
	bool CanCreateClub;
	// 选择的IconIndex
	int SelectIconIndex;
	ClubPanelState PanelState;
};
