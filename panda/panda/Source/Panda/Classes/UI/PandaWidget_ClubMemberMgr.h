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
	// ��Ա�б�
	UScrollBox* Memberlist;
	// ��Ա����
	UTextBlock* MemberMaxNum;


public:
	// ��ʼ���Ի���
	void InitCreateClubMemver(int inNPCID, APlayerCharacter* inPlayer);

	// ѡ��ĶԻ���
	void SelectTalkLabel(int inIndex);
	// ���ò㼶�ı�
//	void ChanePanelLayerState(ClubPanelState inState);

	/** Ȧ*/
	virtual void OnCircle() override;
	/** ��*/
	virtual void OnCross() override;

private:
	// ���Դ���
	bool CanCreateClub;
	// ѡ���IconIndex
	int SelectIconIndex;
//	ClubPanelState PanelState;
};
