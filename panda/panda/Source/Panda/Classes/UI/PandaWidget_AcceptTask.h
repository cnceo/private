// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************
//* Desc. 
//*
//* Created by ZP
//************************************************************************
#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_AcceptTask.generated.h"

#define  Default_Rows 2  // 默认行　可以添加
#define  Default_Columns 4 //默认列　不能添加

/**
 *
 */
UCLASS()
class PANDA_API UPandaWidget_AcceptTask : public UPandaWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	
	virtual void UpdateSelf(float deltaTime) override;

	// 任务列表
	UScrollBox* TaskListHorizontalBox;

	UScrollBox* m_TaskScrollBox;

	// 选择任务的索引 UI中用的
	int32 SelectTaskIndex;

	// 当前选择的任务
	UUserWidget* CurrentSelectTask;

public:

	UFUNCTION(BlueprintCallable, Category = "AcceptTask")
	void addRowTask(int rows = 1);

	// 初始化任务面板
	void InitTaskPanel();

	// 增加一个任务到面板
	void AddTaskToPanel(class UTask* inTask);
	// 改变选择的任务
	void ChangeSelectTask(int inIndex);

	// 初始化任务面板
	void InitAcceptTask();

	virtual void OnRight() override;
	virtual void OnLeft() override;
	virtual void OnUp() override;
	virtual void OnDown() override;

	// 取消
	virtual void OnCross() override;
	virtual void OnCircle() override;

	class UQuestComponent*   m_QuestPtr;

	TArray<int32> TaskIDList;

};
