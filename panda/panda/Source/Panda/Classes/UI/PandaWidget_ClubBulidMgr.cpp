// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_ClubBulidMgr.h"
#include "MartialclubSystem.h"
#include "PlayerDataManager.h"


void UPandaWidget_ClubBulidMgr::NativeConstruct()
{
	Super::NativeConstruct();

	//////////////////////////////////////////////////////////////////////////
	// 创建武馆建筑列表
	SandbagList = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("SandbagList"))));
	if (!SandbagList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--SandbagList==null"));
		return;
	}

	// 建筑描述
	BulidDescribe = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("BulidDescribe"))));
	if (!SandbagList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--BulidDescribe==null"));
		return;
	}
}

// 初始化对话框
void UPandaWidget_ClubBulidMgr::InitCreateClubBulid(int inNPCID, APlayerCharacter* inPlayer)
{
	if (inPlayer == nullptr || SandbagList == nullptr)
		return;
	// 重置数据
	m_Player = inPlayer;
	SandbagList->ClearChildren();

	UMartialclubSystem* ClubSystem =GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
	UMartialclubData* ClubData = ClubSystem->GetMartialclub(FPlayerDataManager::Instance()->getMartialclubID());
	if (ClubData == nullptr)
		return;

	UObject *BulidLabel = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(UMGAssetPath_ClubBulidItem);
	if (BulidLabel == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read MemberLabel BP");
		return;
	}

	if (ClubData->MartialclubBuildList.Num() != 0)
	{
		for (auto Build : ClubData->MartialclubBuildList)
		{
			// 创建成员词条
			UUserWidget *Label = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(BulidLabel);
			TArray<UWidget*> WidgetList;
			Label->WidgetTree->GetAllWidgets(WidgetList);
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Lsit")
				{
					UHorizontalBox* Listbox = Cast<UHorizontalBox>(Widget);
					if (Listbox)
					{
						for (int i = 0; i < Listbox->GetChildrenCount(); i++)
						{
							UWidget* item = Listbox->GetChildAt(i);
							if (item->GetName() == "Name")
							{
								// 建筑名字
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(Build->BuildName);
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "Level")
							{
								// 建筑等级
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("Lv.1%d"), Build->BuildLevel));
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "State")
							{
								// 建筑状态
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("%d"), Build->BuildType));
							}
							//else if (item->GetName() == "Status")
							//{
							//	UTextBlock* text = Cast<UTextBlock>(item);
							//	switch (Build->BuildState)
							//	{
							//	case 0:
							//	{
							//		text->Text = FText::FromString(TEXT("VIP"));
							//	}break;
							//	case 1:
							//	{
							//		text->Text = FText::FromString(TEXT("成员"));
							//	}break;
							//	}
							//	text->SynchronizeProperties();
							//}

						}
					}
				}
			}
			// 增加成员
			SandbagList->AddChild(Label);
		}
	}
}

// 选择的对话项
void UPandaWidget_ClubBulidMgr::SelectTalkLabel(int inIndex)
{

}

//// 设置层级改变
//void UPandaWidget_ClubBulidMgr::ChanePanelLayerState(ClubPanelState inState)
//{
//
//}

/** 圈*/
void UPandaWidget_ClubBulidMgr::OnCircle()
{

}

/** 叉*/
void UPandaWidget_ClubBulidMgr::OnCross()
{
	// 关闭面板
	Super::OnCross();
}