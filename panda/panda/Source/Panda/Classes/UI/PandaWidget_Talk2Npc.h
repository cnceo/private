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
	// ��ʼ���Ի���
	void InitTalk2NPC(int inNPCID, APlayerCharacter* inPlayer, AMonsterBaseCharacter* targetNpc);
	// ��ʼ�����
	void InitClub2NPC();
	// ѡ��ĶԻ���
	void SelectTalkLabel(int inIndex);
	// ���ò㼶�ı�
	void ChanePanelLayerState(PanelLayerState inState);
	// ����Ƿ�����ɵ�����
	bool CheckFinishTask(int inTaskID);

	virtual void OnUp() override;
	virtual void OnDown();
	// ȡ��
	virtual void OnCross() override;
	virtual void OnCircle() override;

	// �ر����
	void ClosePanel();

	TArray<FsTaskInfo*> TaskList;
	// ѡ��Ի��������
	int CurrentSelectTalkLabelIndex;

	UUserWidget* CurrentLabel;
	PanelLayerState TaklLayerState;
	AMonsterBaseCharacter* m_currNpc;
	int32 NPCID;
};
