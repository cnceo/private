// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaGameInstance.h"
#include "Networking/NetworkingFwd.h"
#ifdef USE_SERVER_PERF_COUNTERS
#undef USE_SERVER_PERF_COUNTERS
#endif
#define USE_SERVER_PERF_COUNTERS 1
#include "PerfCountersHelpers.h"

// EasyKit
#include "EKGameFrame.h"
#include "EKLogManager.h"
#include "PandaDataPool.h"
#include "EKHUDManager.h"

// 系统
#include "System/Martialclub/MartialclubSystem.h"

// 流程
#include "Procedure_Login.h"
#include "Procedure_Scene.h"
#include "Procedure_SelectChar.h"
#include "Procedure_CreaterChar.h"
#include "Procedure_Club.h"
#include "Procedure_MainCity.h"
#include "Procedure_CenterArea.h"
#include "System/GameSystem.h"


//global accessor
UPandaGameInstance* GGameInstance = nullptr;

UPandaGameInstance::UPandaGameInstance()
{
	GGameInstance = this;
	m_itemManager = nullptr;
}

UPandaGameInstance::~UPandaGameInstance() 
{
	GGameInstance = nullptr;
	delete m_DataManager;
	
}

//initialize game here
void UPandaGameInstance::Init()
{
	Super::Init();

	InitNetwork();
	// 要在所有系统前初始化
	InitDataPool();

	//init QuestManager
	auto quest = NewObject<UQuestManager>(this, "UQuestManagerTargetName", RF_MarkAsRootSet);
	if (quest)
	{
		quest->Init();
		m_QuestManager = quest;

	}

	//SafeGetDataManager();
	//SafeGetUIManager();
	SafeGetItemManager();
	SafeGetCameraManager();
}

void UPandaGameInstance::InitDataPool()
{
	FPandaDataPool::Instance()->Init();
}

void UPandaGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
	
	if (GIsClient)
	{
		InitProcedure();
		InitHUD();
	}
}

DataManager* UPandaGameInstance::SafeGetDataManager()
{
	if (!m_DataManager)
	{
		//init Data Manager 
		DataManager* data = new DataManager();
		if (data)
		{
			data->Init();
			m_DataManager = data;
		}
	}

	return m_DataManager;
}

FGameSystemManager* UPandaGameInstance::SafeGetGameSyastemManager()
{
	if (!m_GameSystemMgr)
	{
		FGameSystemManager* GameSystemMgr = new FGameSystemManager();
		if (GameSystemMgr)
		{
			GameSystemMgr->InitSystem();
			m_GameSystemMgr = GameSystemMgr;
			return m_GameSystemMgr;
		}
	}

	return m_GameSystemMgr;
}

void UPandaGameInstance::InitNetwork()
{
	//patch for PIE
	if (GIsEditor&&WorldContext) 
	{
		GIsServer = UGameInstance::WorldContext->RunAsDedicated;
		GIsClient = !GIsServer;
	}

	auto path = FPaths::GameConfigDir() / TEXT("DefaultGame.ini");
	auto cfg = TCHAR_TO_ANSI(*path);
	PandaNet::instance().initialize(cfg);

	pandanet.reset(new PandaNetProxy);
	pandanet->start();
}

void UPandaGameInstance::InitProcedure()
{
	Super::InitGameProcedure();

	FEKGameFrame::Instance()->SceneManager()->SetWorld(GetWorldContext()->World());

	TSharedPtr<class FProcedure_Login> proc_Login(new FProcedure_Login(GeometrySpace::Procedure::PT_Login));
	TSharedPtr<class FProcedure_SelectChar> proc_SelectChar(new FProcedure_SelectChar(GeometrySpace::Procedure::PT_SelectChar));
	TSharedPtr<class FProcedure_CreaterChar> proc_CreaterChar(new FProcedure_CreaterChar(GeometrySpace::Procedure::PT_CreaterChar));
	TSharedPtr<class FProcedure_Scene> proc_Wrold(new FProcedure_Scene(GeometrySpace::Procedure::PT_World));
	TSharedPtr<class FProcedure_Club> proc_Clud(new FProcedure_Club(GeometrySpace::Procedure::PT_Club));
	TSharedPtr<class FProcedure_MainCity> proc_MainCity(new FProcedure_MainCity(GeometrySpace::Procedure::PT_MainCity));
	TSharedPtr<class FProcedure_PT_CenterArea> proc_CenterArea(new FProcedure_PT_CenterArea(GeometrySpace::Procedure::PT_CenterArea));
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_Login);
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_SelectChar);
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_CreaterChar);
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_Wrold);
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_Clud);
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_MainCity);
	FEKGameFrame::Instance()->ProcedureManager()->RegisterProcedure(proc_CenterArea);

	FEKGameFrame::Instance()->ProcedureManager()->SetCurrentProcedure(GeometrySpace::Procedure::PT_Login);

	FEKLogManager::Instance()->Log(EKLog::LogType::OutPut, "GameProcedure Init");
}

void UPandaGameInstance::InitHUD()
{
	// Comment temporary for testing by yinjunxu
	FHUDTableData* Table = (FHUDTableData*)(FPandaDataPool::Instance()->GetData(DataPool::DataType::DATA_HUDTable));
	FEKGameFrame::Instance()->HUDManager()->Init(Table->GetHUDTableData());
}

UIManager* UPandaGameInstance::SafeGetUIManager()
{
	if (!m_UIManager)
	{
		UIManager* UI = NewObject<UIManager>(this,"UImanager",EObjectFlags::RF_MarkAsRootSet);
		if (UI)
		{
			UI->Init();
			m_UIManager = UI;
		}
	}

	return m_UIManager;
}
UItemManager* UPandaGameInstance::SafeGetItemManager()
{
	if (!m_itemManager)
	{
		UItemManager* uitem = NewObject <UItemManager>(this, "UItemManager", EObjectFlags::RF_MarkAsRootSet);
		if (uitem)
		{
			uitem->init();
			m_itemManager = uitem;
			return m_itemManager;
		}
	}
	return m_itemManager;
}

UPandaGameInstance* UPandaGameInstance::Instance()
{
	return GGameInstance;
}
UPACameraManager* UPandaGameInstance::SafeGetCameraManager()
{
	if (!m_PACameraManager)
	{
		UPACameraManager* camera = NewObject <UPACameraManager>(this);
		if (camera)
		{
			m_PACameraManager = camera;
			return m_PACameraManager;
		}
	}
	return m_PACameraManager;
}


void UPandaGameInstance::SetupPerfCounter() {
	IPerfCountersModule::Get().CreatePerformanceCounters(TEXT("PandaPerf"));
	FTimerDelegate PerfCounterTD;
	PerfCounterTD.BindUObject(this, &UPandaGameInstance::PerfCounter);
	GetWorld()->GetTimerManager().SetTimer(PerfCounterHandler, PerfCounterTD, 3.f, true);
}

void UPandaGameInstance::PerfCounter() {
	IPerfCounters* PerfCounters = IPerfCountersModule::Get().GetPerformanceCounters();
	if (PerfCounters) {
		int32 NumClients = PerfCounters->Get(TEXT("NumClients"), 0);
		int32 ClientInBytesAvg = PerfCounters->Get(TEXT("InRateClientAvg"), 0);
		int32 ClientOutBytesAvg = PerfCounters->Get(TEXT("OutRateClientAvg"), 0);
		UE_LOG(LogTemp, Warning, TEXT("--------net stats(Conns=%d, InRate=%d, OutRate=%d)"), NumClients, ClientInBytesAvg, ClientOutBytesAvg);
	}
}