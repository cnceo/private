// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_CreateClub.generated.h"

#define UMGAssetPath_CreatClub  FString(TEXT("/Game/UI/UMG/MartialClub/CreatClub.CreatClub_C"))

// ���״̬
UENUM()
enum ClubPanelState
{
	Create_Condition,
	Create_Artst,
};
/**
 * ������ݵ����  
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
	// �����б�
	UScrollBox* ConditionList;
	//////////////////////////////////////////////////////////////////////////
	// Artst
	UCanvasPanel* CreateArtst;
	// ������ݵ�����
	UEditableTextBox* InputName;
	// Icon�б�
	UScrollBox* ClubIconList;

public:
	// ��ʼ���Ի���
	void InitCreateClub(int inNPCID, APlayerCharacter* inPlayer);
	// ��ʼ���Ի���
	void InitClubArtst();

	// ѡ��ĶԻ���
	void SelectTalkLabel(int inIndex);
	// ���ò㼶�ı�
	void ChanePanelLayerState(ClubPanelState inState);

	/** Ȧ*/
	virtual void OnCircle() override;
	/** ��*/
	virtual void OnCross() override;

private:
	// ���Դ���
	bool CanCreateClub;
	// ѡ���IconIndex
	int SelectIconIndex;
	ClubPanelState PanelState;
};
