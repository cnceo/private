// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************
//* Desc. 
//*
//* Created by ZP
//************************************************************************
#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_AcceptTask.generated.h"

#define  Default_Rows 2  // Ĭ���С��������
#define  Default_Columns 4 //Ĭ���С��������

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

	// �����б�
	UScrollBox* TaskListHorizontalBox;

	UScrollBox* m_TaskScrollBox;

	// ѡ����������� UI���õ�
	int32 SelectTaskIndex;

	// ��ǰѡ�������
	UUserWidget* CurrentSelectTask;

public:

	UFUNCTION(BlueprintCallable, Category = "AcceptTask")
	void addRowTask(int rows = 1);

	// ��ʼ���������
	void InitTaskPanel();

	// ����һ���������
	void AddTaskToPanel(class UTask* inTask);
	// �ı�ѡ�������
	void ChangeSelectTask(int inIndex);

	// ��ʼ���������
	void InitAcceptTask();

	virtual void OnRight() override;
	virtual void OnLeft() override;
	virtual void OnUp() override;
	virtual void OnDown() override;

	// ȡ��
	virtual void OnCross() override;
	virtual void OnCircle() override;

	class UQuestComponent*   m_QuestPtr;

	TArray<int32> TaskIDList;

};
