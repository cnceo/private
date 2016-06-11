// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_SearchClub.h"
#include "PandaWidget.h"




void UPandaWidget_SearchClub::NativeConstruct()
{
	Super::NativeConstruct();

	//////////////////////////////////////////////////////////////////////////
	// ��������������
	ClubLabellist = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("ClubList"))));
	if (!ClubLabellist)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--ClubList==null"));
		return;
	}

	// ��������б�
	FacilitiesList = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("FacilitiesList"))));
	if (!FacilitiesList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--FacilitiesList==null"));
		return;
	}
}

// ��ʼ���Ի���
void UPandaWidget_SearchClub::InitCreateSearchClub(int inNPCID, APlayerCharacter* inPlayer)
{
	if (inPlayer == nullptr || ClubLabellist == nullptr || FacilitiesList == nullptr)
		return;
	// ��������
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
			// ������Ա����
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
								// �������
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(Club.Value->ClubName);
								text->SynchronizeProperties();
							} 
							else if(item->GetName() == "Level")
							{
								// ��ݵȼ�
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("Lv.1%d"), Club.Value->ClubLevel));
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "Icon")
							{
								// ���ͼ��
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
			// ���ӳ�Ա
			ClubLabellist->AddChild(Label);
		}
	}
	ClubLabellist->SynchronizeProperties();

	SelectSearchClubLabel(0);
}

// ѡ��ĶԻ���
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

//// ���ò㼶�ı�
//void UPandaWidget_ClubMemberMgr::ChanePanelLayerState(ClubPanelState inState)
//{
//
//}

/** Ȧ*/
void UPandaWidget_SearchClub::OnCircle()
{

}

/** ��*/
void UPandaWidget_SearchClub::OnCross()
{
	// �ر����
	Super::OnCross();
}