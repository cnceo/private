// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>
#include "Engine/GameInstance.h"
#include "EKGameInstance.h"
#include "Manager/QuestManager.h"
#include "Manager/DataManager.h"
#include "UIManager.h"
#include "ItemManager.h"
#include "PACameraManager.h"
#include "PandaGameInstance.generated.h"

/**
 * 
 */
extern class UPandaGameInstance* GGameInstance;
class PandaNetProxy;

namespace GeometrySpace
{
	enum Procedure
	{
		PT_None,
		PT_Login,			// 登录
		PT_CreaterChar,		// 创建
		PT_SelectChar,		// 选择
		PT_Lobby,			// 大厅
		PT_Room,			// 房间
		PT_Character,		// 选角色
		PT_World,			// 世界,现在为副本的概念
		PT_Home,			// 回家
		PT_Club,			// 武馆
		PT_MainCity,		// 主城
		PT_CenterArea,		// 中间区域
	};

	enum Scene
	{
		SC_SCENE1,
		SC_SCENE2
	};
}

UCLASS(Blueprintable)
class PANDA_API UPandaGameInstance : public UEKGameInstance
{
	GENERATED_BODY()

public:
	UPandaGameInstance();
	~UPandaGameInstance();

	virtual void Init() override;
	virtual void StartGameInstance() override;
	virtual void InitProcedure();
	virtual void InitHUD();
	virtual void InitDataPool();

	virtual void InitNetwork();
	static UPandaGameInstance* Instance();
public:

	DataManager* SafeGetDataManager();
	UIManager* SafeGetUIManager();
	UItemManager* SafeGetItemManager();

	UPACameraManager* SafeGetCameraManager();
	std::shared_ptr<PandaNetProxy> pandanet;

	FTimerHandle PerfCounterHandler;
	void PerfCounter();
	void SetupPerfCounter();
	class FGameSystemManager* SafeGetGameSyastemManager();

private:
	UQuestManager* m_QuestManager;
	DataManager* m_DataManager;
	UIManager* m_UIManager;
	UItemManager* m_itemManager;
	UPACameraManager* m_PACameraManager;
	class FGameSystemManager* m_GameSystemMgr;

};
