// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_CreateClub.h"
#include "PandaWidget.h"
#include "PlayerCharacter.h"
#include "System/Martialclub/MartialclubSystem.h"



#define Color_Green  FLinearColor(0.102f, 0.93f, 0.031f, 1.0f) 
#define Color_DarkOrange  FLinearColor(0.617f, 0.034f, 0.0f, 1.0f);


void UPandaWidget_CreateClub::NativeConstruct()
{
	Super::NativeConstruct();

	//////////////////////////////////////////////////////////////////////////
	// 创建条件面板
	CreateCondition = Cast<UCanvasPanel>(GetWidgetFromName(FName(TEXT("CreateCondition"))));
	if (!CreateCondition)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--CreateClub==null"));
		return;
	}

	ConditionList = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("ConditionList"))));
	if (!ConditionList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--ConditionList==null"));
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// 创建设置
	CreateArtst = Cast<UCanvasPanel>(GetWidgetFromName(FName(TEXT("CreatArtst"))));
	if (!CreateArtst)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--CreatArtst==null"));
		return;
	}

	InputName = Cast<UEditableTextBox>(GetWidgetFromName(FName(TEXT("InputName"))));
	if (!InputName)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--InputName==null"));
		return;
	}

	ClubIconList = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("ClubIconList"))));
	if (!ClubIconList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--ClubIconList==null"));
		return;
	}


	CanCreateClub = true;
	PanelState = Create_Condition;

}

// 初始化对话框
void UPandaWidget_CreateClub::InitCreateClub(int inNPCID, APlayerCharacter* inPlayer)
{
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	// 重置数据
	SelectIconIndex = 0;
	CanCreateClub = true;
	PanelState = Create_Condition;
	m_Player = inPlayer;

	//////////////////////////////////////////////////////////////////////////
	if (CreateCondition != nullptr )
	{
		if (ConditionList != nullptr && m_Player!= nullptr)
		{
			for (int i = 0; i < ConditionList->GetChildrenCount(); i++)
			{
				UTextBlock* Label = Cast<UTextBlock>(ConditionList->GetChildAt(i));
				
				if (Label->GetName() == "Level")
				{
					// 判断等级
					if (/*m_Player->GetLevel() > 10*/true)
					{
						Label->ColorAndOpacity = Color_Green;
					}
					else
					{
						Label->ColorAndOpacity = Color_DarkOrange;
						CanCreateClub = false;
					}
				}
				else if (Label->GetName() == "Arena")
				{
					// 判断竞技场积分
					if (true)
					{
						Label->ColorAndOpacity = Color_Green;
					}
					else
					{
						Label->ColorAndOpacity = Color_DarkOrange;
						CanCreateClub = false;
					}
				}
				else if (Label->GetName() == "VisitSeven")
				{
					// 判断拜访 宗师的人数达到7人
					if (true)
					{
						Label->ColorAndOpacity = Color_Green;
					}
					else
					{
						Label->ColorAndOpacity = Color_DarkOrange;
						CanCreateClub = false;
					}
				}
				else if(Label->GetName() == "Realm")
				{
					// 判断武术境界 中极
					if (true)
					{
						Label->ColorAndOpacity = Color_Green;
					}
					else
					{
						Label->ColorAndOpacity = Color_DarkOrange;
						CanCreateClub = false;
					}
				}
				// 更新文字信息
				Label->SynchronizeProperties();
			}	
		}
	}
}

// 初始化对话框
void UPandaWidget_CreateClub::InitClubArtst()
{
	if (CreateArtst != nullptr)
	{
		if (ClubIconList != nullptr && m_Player != nullptr)
		{
			for (int i = 0; i < ClubIconList->GetChildrenCount(); i++)
			{
				UImage* Icon = Cast<UImage>(ConditionList->GetChildAt(i));
				//Icon->Brush.GetResourceObject();
				Icon->SynchronizeProperties();
			}
		}
	}
}

// 选择的对话项
void UPandaWidget_CreateClub::SelectTalkLabel(int inIndex)
{

}

// 设置层级改变
void UPandaWidget_CreateClub::ChanePanelLayerState(ClubPanelState inState)
{
	if (CreateCondition == nullptr || CreateArtst == nullptr)
		return;

	if (PanelState == Create_Condition)
	{
		CreateCondition->SetVisibility(ESlateVisibility::Hidden);
		CreateArtst->SetVisibility(ESlateVisibility::Visible);
	}
	else if (PanelState == Create_Artst)
	{
		CreateCondition->SetVisibility(ESlateVisibility::Visible);
		CreateArtst->SetVisibility(ESlateVisibility::Hidden);
	}

	PanelState = inState;
}

/** 圈*/
void UPandaWidget_CreateClub::OnCircle()
{
	if (PanelState == Create_Condition)
	{
		// 满足创建条件
		if (CanCreateClub == true)
		{
			ChanePanelLayerState(Create_Artst);
		}
	}
	else if (PanelState == Create_Artst)
	{
		if (m_Player != nullptr)
		{
			// 成员管理
			UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
			// 创建武馆
			UMartialclubData* clubdata = System->CreateClub(m_Player, InputName->GetText().ToString());

			if (clubdata)
			{
				// 完成创建武馆
				UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/MartialClub/CompleteClub.CompleteClub_C"));
				UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
			}

			Super::OnCross();
		}
	}

}

/** 叉*/
void UPandaWidget_CreateClub::OnCross()
{
	if (PanelState == Create_Condition)
	{
		Super::OnCross();
	}
	else if (PanelState == Create_Artst)
	{
		Super::OnCross();
	}

}