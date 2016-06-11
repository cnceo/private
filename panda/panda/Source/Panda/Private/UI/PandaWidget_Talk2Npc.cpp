// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaGameInstance.h"
#include "PANPCBaseData.h"
#include "PlayerCharacter.h"
#include "System/GameSystem.h"
#include "PandaWidget_Talk2Npc.h"
#include "PandaWidget_CreateClub.h"
#include "PandaWidget_ClubMemberMgr.h"
#include "PandaWidget_ClubBulidMgr.h"


#define Color_Yellow  FLinearColor(0.991f, 0.658f, 0.095f, 1.0f) 
#define Color_Orange  FLinearColor(0.863f, 0.144f, 0.031f, 1.0f);




void UPandaWidget_Talk2Npc::NativeConstruct()
{
	Super::NativeConstruct();

	//DpadLeft
	//OnNPCInputDown.BindUFunction(this, FName(TEXT("OnNPCDown")));
	//ListenForInputAction(FName(TEXT("DpadDown")), IE_Pressed, 1, OnNPCInputDown);

	// �����б�
	auto ret1 = Cast<UVerticalBox>(GetWidgetFromName(FName(TEXT("TalkBox"))));
	if (!ret1)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_Talk2Npc--NativeConstruct--TalkBox==null"));
		return;
	}
	TalkBox = ret1;

	// �Ի����������������
	auto ret2 = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("TalkdisplayText"))));
	if (!ret2)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_Talk2Npc--NativeConstruct--TalkContent==null"));
		return;
	}
	m_TalkContent = ret2;

	CurrentSelectTalkLabelIndex = 0;
	TaklLayerState = PanelState_One;
}

void UPandaWidget_Talk2Npc::InitTalk2NPC(int inNPCID, APlayerCharacter* inPlayer, AMonsterBaseCharacter* targetNpc)
{
	m_currNpc = targetNpc;
	m_TalkContent->Text = FText::FromString("");
	m_Player = inPlayer;
	NPCID = inNPCID;
	TalkBox->ClearChildren();
	CurrentSelectTalkLabelIndex = 0;
	TaklLayerState = PanelState_One;

	FsPANPCBaseData* NPCData = GGameInstance->SafeGetDataManager()->m_FsPANPCBaseData.Find(inNPCID);
	FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(NPCData->nDialogeIdList[0]);

	// �Ի��������
	m_TalkContent->Text = FText::FromString(StringData->strDesc);
	m_TalkContent->SynchronizeProperties();

	// �����Ի�
	// �Ի���
	UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/NPC/TalkLabel.TalkLabel_C"));
	UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
	if (itemObj == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read TalkLabel BP");
		return;
	}


	TArray<UWidget*> WidgetList;
	itemWidget->WidgetTree->GetAllWidgets(WidgetList);
	for (UWidget* Widget : WidgetList)
	{
		if (Widget->GetName() == "Text")
		{
			UTextBlock* text = Cast<UTextBlock>(Widget);
			// ���ڶ���Ϊ�Ի�����
			FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(NPCData->nDialogeIdList[1]);
			text->Text = FText::FromString(StringData->strDesc);
			text->SynchronizeProperties();
		}
		// Ĭ��ѡ���һ������
		if (Widget->GetName() == "Break")
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
		if (Widget->GetName() == "Mask")
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}	
	}

	// ���õ�ǰ�Ի��� �� �Ի�����
	CurrentLabel = itemWidget;
	TalkBox->AddChild(itemWidget);
	TalkBox->SynchronizeProperties();

	UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(itemWidget->Slot);
	slot->SetHorizontalAlignment(HAlign_Left);
	itemWidget->SynchronizeProperties();
	

	//////////////////////////////////////////////////////////////////////////
	// 
	// ��ݶԻ�
	InitClub2NPC();

	//////////////////////////////////////////////////////////////////////////
	// 
	// ��������
	for (int i = 0; i < NPCData->nTaskIdList.Num(); i++)
	{
		// ���û��������Ϣ����
		FsTaskInfo* TaskInfo = GGameInstance->SafeGetDataManager()->m_FsTaskInfo.Find(NPCData->nTaskIdList[i]);
		if(TaskInfo == nullptr)
			continue;

		if (inPlayer->GetQuestHandler()->CheakTaskFinish(TaskInfo->TaskId) == true)
			continue;

		// ��ӵ������б�
		TaskList.Add(TaskInfo);

		//�������Ի���
		UUserWidget *TaskItem = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
		if (itemObj == nullptr)
		{
			FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read TalkLabel BP");
			return;
		}

		TArray<UWidget*> WidgetList;
		TaskItem->WidgetTree->GetAllWidgets(WidgetList);
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetName() == "Text")
			{
				UTextBlock* text = Cast<UTextBlock>(Widget);
				// �ҵ�����ID
				bool isFinsh = CheckFinishTask(TaskInfo->TaskId);
				// ����������
				text->Text = FText::FromString(TaskInfo->TaskName);
				// ������ɫ

				text->ColorAndOpacity = Color_Yellow;

				if (isFinsh)
				{
					// ���������� ���óɺ�ɫ
					text->ColorAndOpacity = Color_Orange;
				}

				text->SynchronizeProperties();
			}
		}

		TalkBox->AddChild(TaskItem);
		TalkBox->SynchronizeProperties();
		TalkBox->SetVisibility(ESlateVisibility::Visible);

		UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(TaskItem->Slot);
		slot->SetHorizontalAlignment(HAlign_Left);
		TaskItem->SynchronizeProperties();
	}
}

void UPandaWidget_Talk2Npc::InitClub2NPC()
{
	UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/NPC/TalkLabel.TalkLabel_C"));

	for (int i = 0; i < ClubLabelNum; i++)
	{
		UUserWidget *MartialclubWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
		TArray<UWidget*> WidgetList;
		MartialclubWidget->WidgetTree->GetAllWidgets(WidgetList);
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetName() == "Text")
			{
				UTextBlock* text = Cast<UTextBlock>(Widget);
				// ��������������Ի���
				//FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(10001+i);
				//text->Text = FText::FromString(StringData->strDesc);
				FString str = FString::Printf( TEXT("Club_%d"),i );
				text->Text = FText::FromString(str);
				text->SynchronizeProperties();
			}
		}

		TalkBox->AddChild(MartialclubWidget);
		TalkBox->SynchronizeProperties();

		UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(MartialclubWidget->Slot);
		slot->SetHorizontalAlignment(HAlign_Left);
		MartialclubWidget->SynchronizeProperties();
	}

}

void UPandaWidget_Talk2Npc::SelectTalkLabel(int inIndex)
{
	if (CurrentSelectTalkLabelIndex == inIndex)
		return;

	UWidget* widget = TalkBox->GetChildAt(inIndex);
	if (widget != nullptr)
	{
		UUserWidget* Label = Cast<UUserWidget>(widget);
		if (Label != nullptr)
		{
			TArray<UWidget*> WidgetList;
			Label->WidgetTree->GetAllWidgets(WidgetList);
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Text")
				{
					UTextBlock* text = Cast<UTextBlock>(Widget);
					// ������ɫ ��ʱ���ı���ɫ
					text->ColorAndOpacity = Color_Yellow;
					text->SynchronizeProperties();

					// ��ԭ�����õĶԻ��� �ı�
					if (CurrentLabel != nullptr)
					{
						TArray<UWidget*> WidgetList;
						CurrentLabel->WidgetTree->GetAllWidgets(WidgetList);
						for (UWidget* Widget : WidgetList)
						{
							if (Widget->GetName() == "Text")
							{
								UTextBlock* text = Cast<UTextBlock>(Widget);
								// ������ɫ
								text->ColorAndOpacity = Color_Yellow;
								text->SynchronizeProperties();
							}
							else if (Widget->GetName() == "Mask")
							{
								Widget->SetVisibility(ESlateVisibility::Hidden);
							}
							else if (Widget->GetName() == "Break")
							{
								Widget->SetVisibility(ESlateVisibility::Visible);
							}
						}
					}
					// ����������� Ϊ��ǰ����
					CurrentLabel = Label;
				}
				else if (Widget->GetName() == "Mask")
				{
					Widget->SetVisibility(ESlateVisibility::Visible);
				}
				else if (Widget->GetName() == "Break")
				{
					Widget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
	// ���õ�ǰ����Ϊ��������
	CurrentSelectTalkLabelIndex = inIndex;

	//�����Զ�����
	//TalkBox;

	//int row = (m_uitems.Num()) / 3;
	//int rem = (m_uitems.Num()) % 3;

	//rem = ((m_itemIndex + 1) % 3);
	//row = (m_itemIndex + 1) / 3;
	//if (rem > 0)
	//{
	//	row += 1;
	//}
	//if (row > m_rollPos.Y)
	//{
	//	ScrollBox_213->SetScrollOffset(ScrollBox_213->GetScrollOffset() + 153);
	//	m_rollPos.X += 1;
	//	m_rollPos.Y += 1;
	//}
	//else if (row < m_rollPos.X)
	//{
	//	ScrollBox_213->SetScrollOffset(ScrollBox_213->GetScrollOffset() - 153);
	//	m_rollPos.X -= 1;
	//	m_rollPos.Y -= 1;
	//}
}

void UPandaWidget_Talk2Npc::ChanePanelLayerState(PanelLayerState inState)
{
	if (TalkBox == nullptr)
		return;

	if (inState != PanelState_One)
	{
		TalkBox->SetVisibility(ESlateVisibility::Hidden);

	}
	else
	{
		TalkBox->SetVisibility(ESlateVisibility::Visible);
	}
	TaklLayerState = inState;
}

void UPandaWidget_Talk2Npc::UpdateSelf(float deltaTime)
{

}

void UPandaWidget_Talk2Npc::OnUp()
{
	// ֻ�е�һ��Ż��в���
	if (TaklLayerState != PanelState_One)
		return;

	if (CurrentSelectTalkLabelIndex <= 0)
	{
		return;
	}

	SelectTalkLabel(CurrentSelectTalkLabelIndex - 1);
}

void UPandaWidget_Talk2Npc::OnDown()
{
	// ֻ�е�һ��Ż��в���
	if (TaklLayerState != PanelState_One)
		return;

	if ((CurrentSelectTalkLabelIndex + 1) > (ClubLabelNum + TaskList.Num()))
	{
		return;
	}

	SelectTalkLabel(CurrentSelectTalkLabelIndex + 1);
}

void UPandaWidget_Talk2Npc::OnCross()
{

	if (TaklLayerState == PanelState_One)
	{
		ClosePanel();
	}
	else if (TaklLayerState == PanelState_Tow)
	{
		ChanePanelLayerState(PanelState_One);
		FsPANPCBaseData* NPCData = GGameInstance->SafeGetDataManager()->m_FsPANPCBaseData.Find(NPCID);
		FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(NPCData->nDialogeIdList[0]);

		// �Ի��������
		m_TalkContent->Text = FText::FromString(StringData->strDesc);
		m_TalkContent->SynchronizeProperties();
	}
}

void UPandaWidget_Talk2Npc::OnCircle()
{
	if (TaklLayerState == PanelState_One)
	{
		ChanePanelLayerState(PanelState_Tow);

		// �Ի�
		if (CurrentSelectTalkLabelIndex == 0)
		{
			FsPANPCBaseData* NPCData = GGameInstance->SafeGetDataManager()->m_FsPANPCBaseData.Find(NPCID);
			FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(NPCData->nDialogeIdList[1]);

			// �Ի��������
			m_TalkContent->Text = FText::FromString(StringData->strDesc);
			m_TalkContent->SynchronizeProperties();
		}
		// ���
		else if ( (CurrentSelectTalkLabelIndex > 0) && (CurrentSelectTalkLabelIndex < (ClubLabelNum + 1)))
		{

			UMartialclubSystem* ClubSystem = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
			UMartialclubData* ClubData = ClubSystem->GetMartialclub(FPlayerDataManager::Instance()->getMartialclubID());

			// ��һ�� �Ի�����
			int SwitchIndex = CurrentSelectTalkLabelIndex - 1;
			switch (SwitchIndex)
			{
			case 0:
			{
				// �ر����
				ClosePanel();
				// û����ݴ������
				if (ClubData == nullptr)
				{
					// ����������
					UPandaWidget_CreateClub* panel = Cast<UPandaWidget_CreateClub>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_CreatClub));
					if (panel == nullptr)
					{
						GGameInstance->SafeGetUIManager()->OpenUMGAsset(UMGAssetPath_CreatClub);
						panel = Cast<UPandaWidget_CreateClub>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_CreatClub));
						panel->InitCreateClub(NPCID, m_Player);
					}
					else
					{
						panel->SetVisibility(ESlateVisibility::Visible);
						panel->AddToViewport();
						panel->InitCreateClub(NPCID, m_Player);
					}
				}
				else
				{
					// ����������
					UPandaWidget_SearchClub* panel = Cast<UPandaWidget_SearchClub>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_SearchClub));
					if (panel == nullptr)
					{
						GGameInstance->SafeGetUIManager()->OpenUMGAsset(UMGAssetPath_SearchClub);
						panel = Cast<UPandaWidget_SearchClub>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_SearchClub));
						panel->InitCreateSearchClub(NPCID, m_Player);
					}
					else
					{
						panel->SetVisibility(ESlateVisibility::Visible);
						panel->AddToViewport();
						panel->InitCreateSearchClub(NPCID, m_Player);
					}
				}

			}break;
			case 1:
			{
				if (ClubData)
				{
					// �ر����
					ClosePanel();

					// �������
					UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
					System->EnterClub(ClubData->ClubID);
				}
			}break;
			case 2:
			{
				if (ClubData)
				{
					// �ر����
					ClosePanel();
					// ��������
					UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
					// ������ݽ������
					UPandaWidget_ClubBulidMgr* panel = Cast<UPandaWidget_ClubBulidMgr>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_ClubBulid));
					if (panel == nullptr)
					{
						GGameInstance->SafeGetUIManager()->OpenUMGAsset(UMGAssetPath_ClubBulid);
						panel = Cast<UPandaWidget_ClubBulidMgr>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_ClubBulid));
						panel->InitCreateClubBulid(NPCID, m_Player);
					}
					else
					{
						panel->SetVisibility(ESlateVisibility::Visible);
						panel->AddToViewport();
						panel->InitCreateClubBulid(NPCID, m_Player);
					}
					
				}
			}break;
			case 3:
			{
				if (ClubData)
				{
					// �ر����
					ClosePanel();
					// ��Ա����
					UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
					// ������ݳ�Ա���
					UPandaWidget_ClubMemberMgr* panel = Cast<UPandaWidget_ClubMemberMgr>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_ClubMember));
					if (panel == nullptr)
					{
						GGameInstance->SafeGetUIManager()->OpenUMGAsset(UMGAssetPath_ClubMember);
						panel = Cast<UPandaWidget_ClubMemberMgr>(GGameInstance->SafeGetUIManager()->FindInWidgetCache(UMGAssetPath_ClubMember));
						panel->InitCreateClubMemver(NPCID, m_Player);
					}
					else
					{
						panel->SetVisibility(ESlateVisibility::Visible);
						panel->AddToViewport();
						panel->InitCreateClubMemver(NPCID, m_Player);
					}
					
				}
			}break;
			}
		} 
		// ����Ի�����
		else if(CurrentSelectTalkLabelIndex > ClubLabelNum)
		{
			// ��һ�� �Ի�����  ��ClubLabelNum�������ռ����
			FsTaskInfo * Task = TaskList[CurrentSelectTalkLabelIndex - 1 - ClubLabelNum];

			// �Ի��������
			FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(Task->DescriptionID);
			m_TalkContent->Text = FText::FromString(StringData->strDesc);
			m_TalkContent->SynchronizeProperties();
		}
	}
	else if (TaklLayerState == PanelState_Tow)
	{
		if ((CurrentSelectTalkLabelIndex - ClubLabelNum) > 0)
		{
			if (m_Player)
			{
				bool isFinish = m_Player->GetQuestHandler()->IsTaskCompleted(TaskList[CurrentSelectTalkLabelIndex - ClubLabelNum - 1]->TaskId);
				if (isFinish)
				{
					// ��ȡ������
					m_Player->CommitQuest(TaskList[CurrentSelectTalkLabelIndex - ClubLabelNum - 1]->TaskId);

					// �ر����
					ClosePanel();

					// �������
					UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/CompleteTask.CompleteTask_C"));
					UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
				}
				else
				{
					// ��ȡ����
					m_Player->AcceptQuest(TaskList[CurrentSelectTalkLabelIndex - ClubLabelNum - 1]->TaskId);
					// �ر����
					ClosePanel();

					// ��ȡ����
					UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/AcctpTask.AcctpTask_C"));
					UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
				
				}
			}
		}
	}
}

// �ر����
void UPandaWidget_Talk2Npc::ClosePanel()
{
	Super::OnCross();

	if (m_currNpc)
	{
		APlayerController* cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
		UPACameraManager* pac = UPACameraManager::GetCameraManagerInstance();
		pac->StopTaskCameraAnim(cont->GetPawn()->GetRootComponent());
	}
}

// ����Ƿ�����ɵ�����
bool UPandaWidget_Talk2Npc::CheckFinishTask(int inTaskID)
{
	if (m_Player)
	{
		return m_Player->GetQuestHandler()->IsTaskCompleted(inTaskID);
	}

	return false;
}