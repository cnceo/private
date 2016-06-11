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
	// �����б�
	auto ret1 = Cast<UScrollBox>(GetWidgetFromName(FName(TEXT("TaskListHorizontal"))));
	if (!ret1)
	{
		UE_LOG(LogTemp, Error, TEXT("UPandaWidget_AcceptTask--NativeConstruct--TaskListHorizontalBox==null"));
		return;
	}

	TaskListHorizontalBox = ret1;

	TaskListHorizontalBox->ClearChildren();
	TaskIDList.Empty();

	// Ĭ��ѡ���һ��
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
		// �С���ʼ��
		UHorizontalBox* ScrollBox = nullptr;
		UUserWidget* List = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(TaskList);
		TArray<UWidget*> WidgetList;
		List->WidgetTree->GetAllWidgets(WidgetList);
		// �ҵ� �е�����
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetClass() == UHorizontalBox::StaticClass())
			{
				ScrollBox = Cast<UHorizontalBox>(Widget);
			}
		}

		// �� ��ʼ��
		for (int j = 0; j < Default_Columns; ++j)
		{
			// ��������
			UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);
			if (itemObj == nullptr)
			{
				FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read TaskItem BP");
				return;
			}
			TArray<UWidget*> WidgetList;
			itemWidget->WidgetTree->GetAllWidgets(WidgetList);

			// ����Item�µ����пؼ�
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Taskname")
				{
					UTextBlock *Taskname = Cast<UTextBlock>(Widget);
					if (Taskname != nullptr)
					{
						// ������������
						Taskname->Text = FText::FromString("");
						Taskname->SynchronizeProperties();
					}
				}	
				else if (Widget->GetName() == "TaskLock")
				{
					UImage *TaskLock = Cast<UImage>(Widget);
					if (TaskLock != nullptr)
					{
						// ������������
						TaskLock->ColorAndOpacity = FLinearColor(0,0,0,1);
						TaskLock->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskEmpty")
				{
					UImage *TaskEmpty = Cast<UImage>(Widget);
					if (TaskEmpty != nullptr)
					{
						// ������������
						TaskEmpty->ColorAndOpacity = FLinearColor(0, 0, 0, 1);
						TaskEmpty->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Taskdesc")
				{
					UTextBlock *Taskdesc = Cast<UTextBlock>(Widget);
					if (Taskdesc != nullptr)
					{
						// ������������
						Taskdesc->Text = FText::FromString("");
						Taskdesc->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskAwardList")
				{
					UHorizontalBox *TaskAwardList = Cast<UHorizontalBox>(Widget);
					if (TaskAwardList != nullptr)
					{
						// ����������
					
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


	// ��õ�һ��
	UHorizontalBox* Horizontal = Cast<UHorizontalBox>(TaskListHorizontalBox->GetChildAt(Row));
	if(Horizontal != nullptr)
	{
		// ��õ�һ�� �ĵ�һ��
		UUserWidget* itemWidget = Cast<UUserWidget>(Horizontal->GetChildAt(Column));
		if (itemWidget != nullptr)
		{
			TArray<UWidget*> WidgetList;
			itemWidget->WidgetTree->GetAllWidgets(WidgetList);

			// ����Item�µ����пؼ�
			for (UWidget* Widget : WidgetList)
			{
				if (Widget->GetName() == "Taskname")
				{
					// ��������
					UTextBlock *Taskname = Cast<UTextBlock>(Widget);
					if (Taskname != nullptr)
					{
						Taskname->Text = FText::FromString(infoTemp.TaskName);
						Taskname->SynchronizeProperties();
					}
				}
				if (Widget->GetName() == "TaskLock")
				{
					// ȥ��ͼ��
					UImage *TaskLock = Cast<UImage>(Widget);
					if (TaskLock != nullptr)
					{
						// ������
						TaskLock->SetVisibility(ESlateVisibility::Hidden);
						TaskLock->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskEmpty")
				{
					// ȥ��ͼ��
					UImage *TaskEmpty = Cast<UImage>(Widget);
					if (TaskEmpty != nullptr)
					{
						// ȥ��X
						TaskEmpty->SetVisibility(ESlateVisibility::Hidden);
						TaskEmpty->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Gold_Text")
				{
					// ȥ��ͼ��
					UTextBlock *Gold_Text = Cast<UTextBlock>(Widget);
					if (Gold_Text != nullptr)
					{
						// ��ʾ���
						// jingyan
						Gold_Text->Text = FText::FromString(*FString::Printf(TEXT("Gold : %d"), infoTemp.RewardGold));
						Gold_Text->SetVisibility(ESlateVisibility::Visible);
						Gold_Text->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Exp_Text")
				{
					// ��ʾ����
					UTextBlock *Exp_Text = Cast<UTextBlock>(Widget);
					if (Exp_Text != nullptr)
					{
						// ������������

						// jingyan
						Exp_Text->Text = FText::FromString( *FString::Printf(TEXT("Exp : %d"), infoTemp.RewardEXP) );
						Exp_Text->SetVisibility(ESlateVisibility::Visible);
						Exp_Text->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "Taskdesc")
				{
					// ��������
					UTextBlock *Taskdesc = Cast<UTextBlock>(Widget);
					if (Taskdesc != nullptr)
					{
						// ������������
						FsStringTable* StringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(infoTemp.DescriptionID);
						Taskdesc->Text = FText::FromString(StringData->strDesc);
						Taskdesc->SynchronizeProperties();
					}
				}
				else if (Widget->GetName() == "TaskAwardList")
				{
					// ����������
					UHorizontalBox *TaskAwardList = Cast<UHorizontalBox>(Widget);
					if (TaskAwardList != nullptr)
					{
						// ����������
						if (itemObj != nullptr)
						{
							// ���ӽ��� ����
							UUserWidget* itemWidget = Cast<UUserWidget>(itemObj);
							if (itemWidget != nullptr)
							{
								TArray<UWidget*> WidgetList;
								itemWidget->WidgetTree->GetAllWidgets(WidgetList);

								// ����Item�µ����пؼ�
								for (UWidget* Widget : WidgetList)
								{
									if ( Widget->GetName() == "AwardIcon")
									{
										// ����ͼ��
										UImage* AwardIcon = Cast<UImage>(Widget);
										if(AwardIcon)
										{
											// ȥ���߱��ҵ��� �� ��ʾͼ��
											//AwardIcon->Brush.GetResourceObject(infoTemp.RewardItemId);
										}
									}
									else if (Widget->GetName() == "Num")
									{
										// ��������
										UTextBlock* Num = Cast<UTextBlock>(Widget);
										if (Num)
										{
											// �����������Ϊ0��
											if (true)
											{
												Num->Text = FText::FromString(FString::Printf(TEXT("%s"), ""));
											}

										}
									}
								}
							}
						}

						// ���ӵ���
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

			// ����Item�µ����пؼ�
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

				// ����Item�µ����пؼ�
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
			// ���õ�ǰ��ѡ�������
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