// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PlayerCharacter.h"
#include "PandaWidget_AcceptTask.h"
#include "PandaGameInstance.h"
#include "CommonDefine.h"


void UPandaWidget_AcceptTask::NativeConstruct()
{
	Super::NativeConstruct();

	auto player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (player)
	{
		m_QuestPtr = player->GetQuestHandler();
	}

	//TArray<UPanelSlot*> slotlist = Cast<UPanelWidget>(GetRootWidget())->GetSlots();

	//for (auto slot : slotlist)
	//{
	//	if (slot->Content->GetName() == "TaskListHorizontal")
	//	{
	//		TaskListHorizontalBox = Cast<UHorizontalBox>(slot->Content);
	//	}
	//}
	// 任务列表
	auto ret1 = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("TaskListHorizontal"))));
	if (!ret1)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_AcceptTask--NativeConstruct--TaskListHorizontalBox==null"));
		return;
	}

	TaskListHorizontalBox = ret1;

	TaskListHorizontalBox->ClearChildren();
	TaskIDList.Empty();

	// 默认选择第一个
	SelectTaskIndex = 0;
	InitTaskPanel();
}

void UPandaWidget_AcceptTask::InitAcceptTask()
{
	// 
}

void UPandaWidget_AcceptTask::UpdateSelf(float deltaTime)
{
	Super::UpdateSelf(deltaTime);

	//if (!m_QuestPtr)
	//	return;
}

void UPandaWidget_AcceptTask::addRowTask(int rows /*= 1*/)
{
	//if (!m_TaskRowTemp || !m_TaskScrollBox)
	//	return;

	//if (rows <= 0 || rows > 99)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("addRowTask-RowsLimited"));
	//	return;
	//}
}

void UPandaWidget_AcceptTask::InitTaskPanel()
{
	UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/TaskItem.TaskItem_C"));
	UObject *TaskList = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/TaskList.TaskList_C"));

	for (int i = 0; i < Default_Rows; i++)
	{
		// 行　初始化
		UHorizontalBox* ScrollBox = nullptr;
		UUserWidget* List = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(TaskList);
		TArray<UWidget*> WidgetList;
		List->WidgetTree->GetAllWidgets(WidgetList);
		// 找到 行的容器
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetClass() == UHorizontalBox::StaticClass())
			{
				ScrollBox = Cast<UHorizontalBox>(Widget);
			}
		}

		// 列 初始化
		for (int j = 0; j < Default_Columns; ++j)
		{
			// 创建技能
			UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
			if (itemObj == nullptr)
			{
				FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read TaskItem BP");
				return;
			}
			TArray<UWidget*> WidgetList;
			itemWidget->WidgetTree->GetAllWidgets(WidgetList);

			// 遍历Item下的所有控件
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Taskname")
				{
					UTextBlock *Taskname = Cast<UTextBlock>(Widget);
					if (Taskname != nullptr)
					{
						// 设置任务名字
						Taskname->Text = FText::FromString("");
						Taskname->SynchronizeProperties();
					}
				}	
				else if (Widget->GetName() == "TaskLock")
				{
					UImage *TaskLock = Cast<UImage>(Widget);
					if (TaskLock != nullptr)
					{
						// 设置任务描述
						TaskLock->ColorAndOpacity = FLinearColor(0,0,0,1);
						TaskLock->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskEmpty")
				{
					UImage *TaskEmpty = Cast<UImage>(Widget);
					if (TaskEmpty != nullptr)
					{
						// 设置任务描述
						TaskEmpty->ColorAndOpacity = FLinearColor(0, 0, 0, 1);
						TaskEmpty->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Taskdesc")
				{
					UTextBlock *Taskdesc = Cast<UTextBlock>(Widget);
					if (Taskdesc != nullptr)
					{
						// 设置任务描述
						Taskdesc->Text = FText::FromString("");
						Taskdesc->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskAwardList")
				{
					UHorizontalBox *TaskAwardList = Cast<UHorizontalBox>(Widget);
					if (TaskAwardList != nullptr)
					{
						// 设置任务奖励
					
					}
				}
			}

			ScrollBox->AddChild(itemWidget);
			ScrollBox->SynchronizeProperties();
		}

		TaskListHorizontalBox->AddChild(ScrollBox);
		TaskListHorizontalBox->SynchronizeProperties();
		UScrollBoxSlot* Slot = Cast<UScrollBoxSlot>(ScrollBox->Slot);
		if (Slot != nullptr)
		{
			Slot->HorizontalAlignment = EHorizontalAlignment(HAlign_Fill);
			Slot->SynchronizeProperties();
		}
	}

	if (m_QuestPtr->m_CurrentTaskContainer.Num())
	{
		for (auto& task : m_QuestPtr->m_CurrentTaskContainer)
		{
			TaskIDList.Add(task.Value->m_TaskId);
			AddTaskToPanel(task.Value);
		}
		return;
	}
}

void UPandaWidget_AcceptTask::AddTaskToPanel(class UTask* inTask)
{
	FsTaskInfo infoTemp;
	FsTaskInfo* pinfo = m_QuestPtr->m_TaskInfo.Find(inTask->m_TaskId);

	if (pinfo)
	{
		infoTemp = *pinfo;
	}

	UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/Task/AwardItem.AwardItem_C"));

	int Row = TaskIDList.Num() / 4;
	int Column = TaskIDList.Num() & 4;


	// 获得第一行
	UHorizontalBox* Horizontal = Cast<UHorizontalBox>(TaskListHorizontalBox->GetChildAt(Row));
	if(Horizontal != nullptr)
	{
		// 获得第一行 的第一列
		UUserWidget* itemWidget = Cast<UUserWidget>(Horizontal->GetChildAt(Column));
		if (itemWidget != nullptr)
		{
			TArray<UWidget*> WidgetList;
			itemWidget->WidgetTree->GetAllWidgets(WidgetList);

			// 遍历Item下的所有控件
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Taskname")
				{
					// 任务名字
					UTextBlock *Taskname = Cast<UTextBlock>(Widget);
					if (Taskname != nullptr)
					{
						Taskname->Text = FText::FromString(infoTemp.TaskName);
						Taskname->SynchronizeProperties();
					}
				}
				if (Widget->GetName() == "TaskLock")
				{
					// 去掉图标
					UImage *TaskLock = Cast<UImage>(Widget);
					if (TaskLock != nullptr)
					{
						// 设置锁
						TaskLock->SetVisibility(ESlateVisibility::Hidden);
						TaskLock->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskEmpty")
				{
					// 去掉图标
					UImage *TaskEmpty = Cast<UImage>(Widget);
					if (TaskEmpty != nullptr)
					{
						// 去掉X
						TaskEmpty->SetVisibility(ESlateVisibility::Hidden);
						TaskEmpty->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Gold_Text")
				{
					// 去掉图标
					UTextBlock *Gold_Text = Cast<UTextBlock>(Widget);
					if (Gold_Text != nullptr)
					{
						// 显示金币
						// jingyan
						Gold_Text->Text = FText::FromString(*FString::Printf(TEXT("Gold : %d"), infoTemp.RewardGold));
						Gold_Text->SetVisibility(ESlateVisibility::Visible);
						Gold_Text->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Exp_Text")
				{
					// 显示经验
					UTextBlock *Exp_Text = Cast<UTextBlock>(Widget);
					if (Exp_Text != nullptr)
					{
						// 设置任务描述

						// jingyan
						Exp_Text->Text = FText::FromString( *FString::Printf(TEXT("Exp : %d"), infoTemp.RewardEXP) );
						Exp_Text->SetVisibility(ESlateVisibility::Visible);
						Exp_Text->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Taskdesc")
				{
					// 任务描述
					UTextBlock *Taskdesc = Cast<UTextBlock>(Widget);
					if (Taskdesc != nullptr)
					{
						// 设置任务描述
						FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(infoTemp.DescriptionID);
						Taskdesc->Text = FText::FromString(StringData->strDesc);
						Taskdesc->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskAwardList")
				{
					// 增加任务奖励
					UHorizontalBox *TaskAwardList = Cast<UHorizontalBox>(Widget);
					if (TaskAwardList != nullptr)
					{
						// 设置任务奖励
						if (itemObj != nullptr)
						{
							// 增加奖励 道具
							UUserWidget* itemWidget = Cast<UUserWidget>(itemObj);
							if (itemWidget != nullptr)
							{
								TArray<UWidget*> WidgetList;
								itemWidget->WidgetTree->GetAllWidgets(WidgetList);

								// 遍历Item下的所有控件
								for (UWidget* Widget : WidgetList)
								{
									if ( Widget->GetName() == "AwardIcon")
									{
										// 道具图标
										UImage* AwardIcon = Cast<UImage>(Widget);
										if(AwardIcon)
										{
											// 去道具表找道具 的 显示图标
											//AwardIcon->Brush.GetResourceObject(infoTemp.RewardItemId);
										}
									}
									else if (Widget->GetName() == "Num")
									{
										// 道具数量
										UTextBlock* Num = Cast<UTextBlock>(Widget);
										if (Num)
										{
											// 如果奖励数量为0则
											if (true)
											{
												Num->Text = FText::FromString(FString::Printf(TEXT("%s"), ""));
											}

										}
									}
								}
							}
						}

						// 增加道具
						TaskAwardList->AddChild(Widget);
						TaskAwardList->SynchronizeProperties();
						UHorizontalBoxSlot* Slot = Cast<UHorizontalBoxSlot>(Widget->Slot);
						if (Slot != nullptr)
						{
							Slot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
							Slot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
							Widget->SynchronizeProperties();
						}
					}
				}
			}
		}
		
	}
	

	ChangeSelectTask(SelectTaskIndex);
}

void UPandaWidget_AcceptTask::ChangeSelectTask(int inIndex)
{
	int Row = inIndex / Default_Columns;
	int Column = inIndex % Default_Columns;

	UHorizontalBox* HorizontalBox = Cast<UHorizontalBox>(TaskListHorizontalBox->GetChildAt(Row));
	UUserWidget* itemWidget = Cast<UUserWidget>(HorizontalBox->GetChildAt(Column));
	if (itemWidget)
	{
		if (itemWidget != nullptr)
		{
			TArray<UWidget*> WidgetList;
			itemWidget->WidgetTree->GetAllWidgets(WidgetList);

			// 遍历Item下的所有控件
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Background")
				{
					Widget->SetVisibility(ESlateVisibility::Hidden);
				}
				if (Widget->GetName() == "BackgroundOn")
				{
					Widget->SetVisibility(ESlateVisibility::Visible);
				}
			}

			if (CurrentSelectTask != nullptr)
			{
				TArray<UWidget*> WidgetList;
				CurrentSelectTask->WidgetTree->GetAllWidgets(WidgetList);

				// 遍历Item下的所有控件
				for (UWidget* Widget : WidgetList)
				{
					if (Widget->GetName() == "Background")
					{
						Widget->SetVisibility(ESlateVisibility::Visible);
					}
					if (Widget->GetName() == "BackgroundOn")
					{
						Widget->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
			// 设置当前的选择的任务
			CurrentSelectTask = itemWidget;
		}
	}
}

void UPandaWidget_AcceptTask::OnLeft()
{
	SelectTaskIndex++;

	ChangeSelectTask(SelectTaskIndex);
}

void UPandaWidget_AcceptTask::OnRight()
{
	if (SelectTaskIndex == 0)
		return;
	
	SelectTaskIndex--;

	ChangeSelectTask(SelectTaskIndex);
}

void UPandaWidget_AcceptTask::OnUp()
{
	if (SelectTaskIndex == 0)
		return;

	SelectTaskIndex -= 3;


	ChangeSelectTask(SelectTaskIndex);
}

void UPandaWidget_AcceptTask::OnDown()
{
	if (m_QuestPtr == nullptr)
		return;

	SelectTaskIndex += 3;

	if (SelectTaskIndex >= m_QuestPtr->m_CurrentTaskContainer.Num())
	{
		SelectTaskIndex = m_QuestPtr->m_CurrentTaskContainer.Num() - 1;
	}

	ChangeSelectTask(SelectTaskIndex);
}

void UPandaWidget_AcceptTask::OnCross()
{
	Super::OnCross();
}

void UPandaWidget_AcceptTask::OnCircle()
{
	
}