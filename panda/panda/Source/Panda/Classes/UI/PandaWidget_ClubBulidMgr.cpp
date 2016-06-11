// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_ClubBulidMgr.h"
#include "MartialclubSystem.h"
#include "PlayerDataManager.h"


void UPandaWidget_ClubBulidMgr::NativeConstruct()
{
	Super::NativeConstruct();

	//////////////////////////////////////////////////////////////////////////
	// ������ݽ����б�
	SandbagList = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("SandbagList"))));
	if (!SandbagList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--SandbagList==null"));
		return;
	}

	// ��������
	BulidDescribe = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("BulidDescribe"))));
	if (!SandbagList)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_CreateClub--NativeConstruct--BulidDescribe==null"));
		return;
	}
}

// ��ʼ���Ի���
void UPandaWidget_ClubBulidMgr::InitCreateClubBulid(int inNPCID, APlayerCharacter* inPlayer)
{
	if (inPlayer == nullptr || SandbagList == nullptr)
		return;
	// ��������
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
			// ������Ա����
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
								// ��������
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(Build->BuildName);
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "Level")
							{
								// �����ȼ�
								UTextBlock* text = Cast<UTextBlock>(item);
								text->Text = FText::FromString(FString::Printf(TEXT("Lv.1%d"), Build->BuildLevel));
								text->SynchronizeProperties();
							}
							else if (item->GetName() == "State")
							{
								// ����״̬
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
							//		text->Text = FText::FromString(TEXT("��Ա"));
							//	}break;
							//	}
							//	text->SynchronizeProperties();
							//}

						}
					}
				}
			}
			// ���ӳ�Ա
			SandbagList->AddChild(Label);
		}
	}
}

// ѡ��ĶԻ���
void UPandaWidget_ClubBulidMgr::SelectTalkLabel(int inIndex)
{

}

//// ���ò㼶�ı�
//void UPandaWidget_ClubBulidMgr::ChanePanelLayerState(ClubPanelState inState)
//{
//
//}

/** Ȧ*/
void UPandaWidget_ClubBulidMgr::OnCircle()
{

}

/** ��*/
void UPandaWidget_ClubBulidMgr::OnCross()
{
	// �ر����
	Super::OnCross();
}