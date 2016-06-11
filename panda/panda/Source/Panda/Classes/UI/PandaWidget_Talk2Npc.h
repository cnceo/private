// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_Talk2Npc.generated.h"

#define ClubLabelNum 4

UENUM()
enum PanelLayerState
{
	PanelState_One = 0,
	PanelState_Tow,
	PanelState_Three,
};

/**
 *
 */
UCLASS()
class PANDA_API UPandaWidget_Talk2Npc : public UPandaWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void UpdateSelf(float deltaTime) override;

public:	

	UTextBlock*   m_TalkContent;
	UVerticalBox*   TalkBox;
	TArray<UImage*>  m_Imgs;
	int  m_TalkIndex;

	FOnInputAction OnNPCInputDown;

	void TalkNPC();
	void GetSelectTask();

public:
	// 初始化对话框
	void InitTalk2NPC(int inNPCID, APlayerCharacter* inPlayer, AMonsterBaseCharacter* targetNpc);
	// 初始化武馆
	void InitClub2NPC();
	// 选择的对话项
	void SelectTalkLabel(int inIndex);
	// 设置层级改变
	void ChanePanelLayerState(PanelLayerState inState);
	// 检查是否有完成的任务
	bool CheckFinishTask(int inTaskID);

	virtual void OnUp() override;
	virtual void OnDown();
	// 取消
	virtual void OnCross() override;
	virtual void OnCircle() override;

	// 关闭面板
	void ClosePanel();

	TArray<FsTaskInfo*> TaskList;
	// 选择对话项的索引
	int CurrentSelectTalkLabelIndex;

	UUserWidget* CurrentLabel;
	PanelLayerState TaklLayerState;
	AMonsterBaseCharacter* m_currNpc;
	int32 NPCID;
};
