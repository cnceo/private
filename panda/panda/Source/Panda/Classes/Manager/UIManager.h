// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************
//* Desc. UMG asset management
//*
//* Created by ZP
//************************************************************************
#pragma once
#include "Object.h"
#include "PandaWidget.h"
#include "UIManager.generated.h"

#define UMGAssetPath_AcceptTask  FString(TEXT("/Game/UI/UMG/Task/AcceptTask.AcceptTask_C"))
#define UMGAssetPath_NPCTalk  FString(TEXT("/Game/UI/UMG/NPC/NpcTalk.NpcTalk_C"))

enum UMGAssetName
{
	UAN_None,
	UAN_Max
};
/**
 *
 */
UCLASS()
class PANDA_API UIManager : public UObject
{
	GENERATED_BODY()
public:
	void Init();

public:
	//Asyn load asset from AssetPath
	void OpenUMGAsset(FString AssetPath);
	//Hidden specified Asset
	void CloseUMGAsset(FString AssetPath , bool bDestory = false );
	//call this in openUMGAsset first
	UPandaWidget* FindInWidgetCache(FString AssetPath);
private:
	bool CreateFromAsset(FStringAssetReference StringRef);
	//show asset 
	void OnAsynLoadNotify(FStringAssetReference StringRef);

public:
	UPROPERTY(transient)
	FStreamableManager	StreamableManager;
	UPROPERTY()
	TArray<UPandaWidget*>   m_WidgetCache;


};
