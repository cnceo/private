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

	// 任务列表
	auto ret1 = Cast<UVerticalBox>(GetWidgetFromName(FName(TEXT("TalkBox"))));
	if (!ret1)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_Talk2Npc--NativeConstruct--TalkBox==null"));
		return;
	}
	TalkBox = ret1;

	// 对话面板文字描述内容
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

	// 对话面板内容
	m_TalkContent->Text = FText::FromString(StringData->strDesc);
	m_TalkContent->SynchronizeProperties();

	// 创建对话
	// 对话条
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
			// 读第二条为对话内容
			FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(NPCData->nDialogeIdList[1]);
			text->Text = FText::FromString(StringData->strDesc);
			text->SynchronizeProperties();
		}
		// 默认选择第一个任务
		if (Widget->GetName() == "Break")
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
		if (Widget->GetName() == "Mask")
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}	
	}

	// 设置当前对话项 是 对话词条
	CurrentLabel = itemWidget;
	TalkBox->AddChild(itemWidget);
	TalkBox->SynchronizeProperties();

	UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(itemWidget->Slot);
	slot->SetHorizontalAlignment(HAlign_Left);
	itemWidget->SynchronizeProperties();
	

	//////////////////////////////////////////////////////////////////////////
	// 
	// 武馆对话
	InitClub2NPC();

	//////////////////////////////////////////////////////////////////////////
	// 
	// 创建任务
	for (int i = 0; i < NPCData->nTaskIdList.Num(); i++)
	{
		// 如果没有任务信息跳过
		FsTaskInfo* TaskInfo = GGameInstance->SafeGetDataManager()->m_FsTaskInfo.Find(NPCData->nTaskIdList[i]);
		if(TaskInfo == nullptr)
			continue;

		if (inPlayer->GetQuestHandler()->CheakTaskFinish(TaskInfo->TaskId) == true)
			continue;

		// 添加到任务列表
		TaskList.Add(TaskInfo);

		//　创建对话条
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
				// 找到任务ID
				bool isFinsh = CheckFinishTask(TaskInfo->TaskId);
				// 对任务名称
				text->Text = FText::FromString(TaskInfo->TaskName);
				// 设置颜色

				text->ColorAndOpacity = Color_Yellow;

				if (isFinsh)
				{
					// 如果完成任务 设置成红色
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
				// 读第武馆相关任务对话条
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
					// 设置颜色 暂时不改变颜色
					text->ColorAndOpacity = Color_Yellow;
					text->SynchronizeProperties();

					// 把原来设置的对话项 改变
					if (CurrentLabel != nullptr)
					{
						TArray<UWidget*> WidgetList;
						CurrentLabel->WidgetTree->GetAllWidgets(WidgetList);
						for (UWidget* Widget : WidgetList)
						{
							if (Widget->GetName() == "Text")
							{
								UTextBlock* text = Cast<UTextBlock>(Widget);
								// 设置颜色
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
					// 设置这个标题 为当前标题
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
	// 设置当前索引为穿进来的
	CurrentSelectTalkLabelIndex = inIndex;

	//设置自动滚动
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
	// 只有第一层才会有操作
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
	// 只有第一层才会有操作
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

		// 对话面板内容
		m_TalkContent->Text = FText::FromString(StringData->strDesc);
		m_TalkContent->SynchronizeProperties();
	}
}

void UPandaWidget_Talk2Npc::OnCircle()
{
	if (TaklLayerState == PanelState_One)
	{
		ChanePanelLayerState(PanelState_Tow);

		// 对话
		if (CurrentSelectTalkLabelIndex == 0)
		{
			FsPANPCBaseData* NPCData = GGameInstance->SafeGetDataManager()->m_FsPANPCBaseData.Find(NPCID);
			FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(NPCData->nDialogeIdList[1]);

			// 对话面板内容
			m_TalkContent->Text = FText::FromString(StringData->strDesc);
			m_TalkContent->SynchronizeProperties();
		}
		// 武馆
		else if ( (CurrentSelectTalkLabelIndex > 0) && (CurrentSelectTalkLabelIndex < (ClubLabelNum + 1)))
		{

			UMartialclubSystem* ClubSystem = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
			UMartialclubData* ClubData = ClubSystem->GetMartialclub(FPlayerDataManager::Instance()->getMartialclubID());

			// 减一是 对话索引
			int SwitchIndex = CurrentSelectTalkLabelIndex - 1;
			switch (SwitchIndex)
			{
			case 0:
			{
				// 关闭面板
				ClosePanel();
				// 没有武馆创建武馆
				if (ClubData == nullptr)
				{
					// 创建武馆面板
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
					// 创建武馆面板
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
					// 关闭面板
					ClosePanel();

					// 进入武馆
					UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
					System->EnterClub(ClubData->ClubID);
				}
			}break;
			case 2:
			{
				if (ClubData)
				{
					// 关闭面板
					ClosePanel();
					// 建筑管理
					UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
					// 创建武馆建筑面板
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
					// 关闭面板
					ClosePanel();
					// 成员管理
					UMartialclubSystem* System = GGameInstance->SafeGetGameSyastemManager()->GetGameSystem<UMartialclubSystem>();
					// 创建武馆成员面板
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
		// 任务对话处理
		else if(CurrentSelectTalkLabelIndex > ClubLabelNum)
		{
			// 减一是 对话索引  减ClubLabelNum是武馆所占索引
			FsTaskInfo * Task = TaskList[CurrentSelectTalkLabelIndex - 1 - ClubLabelNum];

			// 对话面板内容
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
					// 领取任务奖励
					m_Player->CommitQuest(TaskList[CurrentSelectTalkLabelIndex - ClubLabelNum - 1]->TaskId);

					// 关闭面板
					ClosePanel();

					// 完成任务
					UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/CompleteTask.CompleteTask_C"));
					UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
				}
				else
				{
					// 领取任务
					m_Player->AcceptQuest(TaskList[CurrentSelectTalkLabelIndex - ClubLabelNum - 1]->TaskId);
					// 关闭面板
					ClosePanel();

					// 领取任务
					UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/AcctpTask.AcctpTask_C"));
					UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
				
				}
			}
		}
	}
}

// 关闭面板
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

// 检查是否有完成的任务
bool UPandaWidget_Talk2Npc::CheckFinishTask(int inTaskID)
{
	if (m_Player)
	{
		return m_Player->GetQuestHandler()->IsTaskCompleted(inTaskID);
	}

	return false;
}