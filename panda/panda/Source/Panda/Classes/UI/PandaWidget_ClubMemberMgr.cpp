// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_ClubMemberMgr.h"
#include "PandaWidget.h"




void UPandaWidget_ClubMemberMgr::NativeConstruct()
{
	Super::NativeConstruct();

	//////////////////////////////////////////////////////////////////////////
	// 创建武馆成员面板
	Memberlist = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("Memberlist"))));
	if (!Memberlist)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--Memberlist==null"));
		return;
	}

	// 成员总数
	MemberMaxNum = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("MemberMaxNum"))));
	if (!MemberMaxNum)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--MemberMaxNum==null"));
		return;
	}
}

// 初始化对话框
void UPandaWidget_ClubMemberMgr::InitCreateClubMemver(int inNPCID, APlayerCharacter* inPlayer)
{
	if (inPlayer == nullptr || Memberlist == nullptr)
		return;
	// 重置数据
	m_Player = inPlayer;
	Memberlist->ClearChildren();

	UMartialclubSystem* ClubSystem = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
	UMartialclubData* ClubData = ClubSystem->GetMartialclub(FPlayerDataManager::Instance()->getMartialclubID());

	if (ClubData == nullptr)
		return;

	UObject *MemberLabel = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(UMGAssetPath_MemberLabel);
	if (MemberLabel == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read MemberLabel BP");
		return;
	}

	if (ClubData->MartialclubMemberList.Num() != 0)
	{
		for (auto member : ClubData->MartialclubMemberList)
		{
			// 创建成员词条
			UUserWidget *Label = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(MemberLabel);
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
								// 成员名字
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(member->MemberName);
								text->SynchronizeProperties();
							} 
							else if(item->GetName() == "Level")
							{
								// 成员等级
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("Lv.1%d"), member->MemberLevel));
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "Num")
							{
								// 成员竞技场积分
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("%d"), member->MemberJJCNum));
							}
							else if (item->GetName() == "Status")
							{
								UTextBlock* text = Cast<UTextBlock>(item);
								switch (member->MemberRestrict)
								{
								case 0:
								{
									text->Text = FText::FromString(TEXT("VIP"));
								}break;
								case 1:
								{
									text->Text = FText::FromString(TEXT("成员"));
								}break;
								}
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "Online")
							{
								UTextBlock* text = Cast<UTextBlock>(item);
								if (member->MemberOnline)
								{
									text->Text = FText::FromString(TEXT("Online"));
								}
								else
								{
									text->Text = FText::FromString(TEXT("Outline"));
								}
								text->SynchronizeProperties();
							}
						}
					}
				}
			}
			// 增加成员
			Memberlist->AddChild(Label);
		}
	}

	int OnlineNum = 0;
	for (auto member : ClubData->MartialclubMemberList)
	{
		/*UMartialclubMember*/
		if (member->MemberOnline == true)
			OnlineNum++;
	}
	
	MemberMaxNum->Text = FText::FromString(FString::Printf(TEXT("%d/%d"), OnlineNum, ClubData->ClubLevel * 50));
	MemberMaxNum->SynchronizeProperties();

}

// 选择的对话项
void UPandaWidget_ClubMemberMgr::SelectTalkLabel(int inIndex)
{

}

//// 设置层级改变
//void UPandaWidget_ClubMemberMgr::ChanePanelLayerState(ClubPanelState inState)
//{
//
//}

/** 圈*/
void UPandaWidget_ClubMemberMgr::OnCircle()
{

}

/** 叉*/
void UPandaWidget_ClubMemberMgr::OnCross()
{
	// 关闭面板
	Super::OnCross();
}