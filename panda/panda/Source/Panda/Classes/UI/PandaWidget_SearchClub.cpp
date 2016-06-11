// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_SearchClub.h"
#include "PandaWidget.h"




void UPandaWidget_SearchClub::NativeConstruct()
{
	Super::NativeConstruct();

	//////////////////////////////////////////////////////////////////////////
	// 创建搜索武馆面板
	ClubLabellist = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("ClubList"))));
	if (!ClubLabellist)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--ClubList==null"));
		return;
	}

	// 武馆描述列表
	FacilitiesList = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("FacilitiesList"))));
	if (!FacilitiesList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--FacilitiesList==null"));
		return;
	}
}

// 初始化对话框
void UPandaWidget_SearchClub::InitCreateSearchClub(int inNPCID, APlayerCharacter* inPlayer)
{
	if (inPlayer == nullptr || ClubLabellist == nullptr || FacilitiesList == nullptr)
		return;
	// 重置数据
	m_Player = inPlayer;
	ClubLabellist->ClearChildren();
	FacilitiesList->ClearChildren();

	UMartialclubSystem* ClubSystem = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
	if (ClubSystem == nullptr)
		return;

	UObject *ClubLabel = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(UMGAssetPath_SearchClubLabel);
	if (ClubLabel == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read ClubLabel BP");
		return;
	}

	if (ClubSystem->ClubList.Num() != 0)
	{
		for (auto Club : ClubSystem->ClubList)
		{
			// 创建成员词条
			UUserWidget *Label = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(ClubLabel);
			TArray<UWidget*> WidgetList;
			Label->WidgetTree->GetAllWidgets(WidgetList);
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "List")
				{
					UHorizontalBox* Listbox = Cast<UHorizontalBox>(Widget);
					if (Listbox)
					{
						for (int i = 0; i < Listbox->GetChildrenCount(); i++)
						{
							UWidget* item = Listbox->GetChildAt(i);
							if (item->GetName() == "Name")
							{
								// 武馆名字
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(Club.Value->ClubName);
								text->SynchronizeProperties();
							} 
							else if(item->GetName() == "Level")
							{
								// 武馆等级
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("Lv.1%d"), Club.Value->ClubLevel));
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "Icon")
							{
								// 武馆图标
								//UTextBlock* text = Cast<UTextBlock>(item);
								//text->Text = FText::FromString(FString::Printf(TEXT("%d"), member->MemberJJCNum));
							}
							else if (item->GetName() == "Status")
							{
								UTextBlock* text = Cast<UTextBlock>(item);
								switch (Club.Value->ClubState)
								{
								case 0:
								{
									text->Text = FText::FromString(TEXT("T"));
								}break;
								case 1:
								{
									text->Text = FText::FromString(TEXT("Online"));
								}break;
								}
								text->SynchronizeProperties();
							}
						}
					}
				}
			}
			// 增加成员
			ClubLabellist->AddChild(Label);
		}
	}
	ClubLabellist->SynchronizeProperties();

	SelectSearchClubLabel(0);
}

// 选择的对话项
void UPandaWidget_SearchClub::SelectSearchClubLabel(int inIndex)
{
	if (CurrentLabel != nullptr)
	{
		CurrentLabel->SetVisibility(ESlateVisibility::Hidden);
	}

	CurrentLabel = ClubLabellist->GetChildAt(inIndex);
	CurrentLabel->SetVisibility(ESlateVisibility::Visible);

	SelectIconIndex = inIndex;
}

//// 设置层级改变
//void UPandaWidget_ClubMemberMgr::ChanePanelLayerState(ClubPanelState inState)
//{
//
//}

/** 圈*/
void UPandaWidget_SearchClub::OnCircle()
{

}

/** 叉*/
void UPandaWidget_SearchClub::OnCross()
{
	// 关闭面板
	Super::OnCross();
}