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
	// �����б�
	UScrollBox* SandbagList;
	// ��������
	UTextBlock* BulidDescribe;

public:
	// ��ʼ���Ի���
	void InitCreateClubBulid(int inNPCID, APlayerCharacter* inPlayer);

	// ѡ��ĶԻ���
	void SelectTalkLabel(int inIndex);
	// ���ò㼶�ı�
	//void ChanePanelLayerState(ClubPanelState inState);

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
