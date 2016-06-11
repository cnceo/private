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
	// ����б�
	UScrollBox* ClubLabellist;
	// ��������б�
	UScrollBox* FacilitiesList;
	// ���ͼ��
	UImage*		BannerIcon;

public:
	// ��ʼ���������
	void InitCreateSearchClub(int inNPCID, APlayerCharacter* inPlayer);

	// ѡ��ĶԻ���
	void SelectSearchClubLabel(int inIndex);
	// ���ò㼶�ı�
//	void ChanePanelLayerState(ClubPanelState inState);

	/** Ȧ*/
	virtual void OnCircle() override;
	/** ��*/
	virtual void OnCross() override;

private:
	// ѡ��ĶԻ�
	UWidget* CurrentLabel;
	// ѡ���IconIndex
	int SelectIconIndex;
	ClubPanelState PanelState;
};
