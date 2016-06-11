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
		PT_Login,			// ��¼
		PT_CreaterChar,		// ����
		PT_SelectChar,		// ѡ��
		PT_Lobby,			// ����
		PT_Room,			// ����
		PT_Character,		// ѡ��ɫ
		PT_World,			// ����,����Ϊ�����ĸ���
		PT_Home,			// �ؼ�
		PT_Club,			// ���
		PT_MainCity,		// ����
		PT_CenterArea,		// �м�����
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
