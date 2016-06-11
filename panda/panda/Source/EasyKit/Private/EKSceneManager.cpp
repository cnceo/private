//
// EKSceneManager.cpp
//
// 游戏场景管理器 用于加载场景管理地图 无缝加载等
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu, Shen Qian. All Rights Reserved. 
//

#include "EasyKit.h"
#include "AsyncLoading.h"
#include "SlateBasics.h"
#include "Engine/LevelStreaming.h"

#include "EKSceneManager.h"
#include "EKCharacter.h"
#include "EKGameFrame.h"

#include "PandaGameLoadingScreen.h"

#define  PLAYER_ID_CASE 1000

#define  CAY_START_MAX_Y 15000
#define  CAY_END_MIN_Y -10000

//#define EASYKIT_IOS

FEKSceneManager::FEKSceneManager()
: m_World(NULL)
, M_CurrentLevel(NULL)
, aCurActor(nullptr)
, bTimer(false)
, fChangeMapOffSetTime(0.05f)
, bChangeMapInterval(false)
, fChangeMapIntervalTime(0.05f)
, bChangeMapInProcess(false)
, bChangeMapDuringChanging(false)
{
	m_pLocalPlayer = NULL;
}


void FEKSceneManager::Init()
{

}

UWorld* FEKSceneManager::GetWorld() const
{
	check(m_World)

		return m_World;
}

void FEKSceneManager::SetWorld(UWorld* inWorld)
{
	check(inWorld)

	m_World = inWorld;
}

void FEKSceneManager::LoadWorld(const FString& inMapName)
{

}

void FEKSceneManager::CreateLoadingScreen()
{
	if (GIsServer)
		return;

	IPandaGameLoadingScreenModule* LoadingScreenModule = FModuleManager::LoadModulePtr<IPandaGameLoadingScreenModule>("PandaGameLoadingScreen");
	if (LoadingScreenModule != NULL)
	{
		LoadingScreenModule->StartInGameLoadingScreen();
	}
}

bool FEKSceneManager::LoadMap(FName inMapName)
{
	if (GWorld == nullptr)
	{
		if (m_World != nullptr)
		{
			UGameplayStatics::OpenLevel(m_World, inMapName);
		}
		else
			return false;
	}
	else
	{
		UGameplayStatics::OpenLevel(GWorld, inMapName);
	}
	
	return true;
}

void FEKSceneManager::LoadMap(const FString inMapName, FName inCallbackTarget)
{

	//////////////////////////////////////////////////////////////////////////
	check(m_World)

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = NULL;
	LatentInfo.UUID = 1025;
	LatentInfo.Linkage = 15;
	LatentInfo.ExecutionFunction = inCallbackTarget;

	LoadMap(inMapName, LatentInfo);
}

void FEKSceneManager::LoadMap(const FString inMapName, FLatentActionInfo& inActionInfo)
{

	//////////////////////////////////////////////////////////////////////////
	check(m_World)

	//if (m_World->GetMapName() == inMapName)
	//{
	//	FEKGameFrame::Instance()->ProcedureManager()->GetCurrentProcedure()->PostLoadMap();
	//	return;
	//}


	FString Cmd = PANDA_MAP_PATH_NAME_PRE + inMapName;
	//////////////////////////////////////////////////////////////////////////
	const ETravelType TravelType = TRAVEL_Absolute;
	FWorldContext &WorldContext = GEngine->GetWorldContextFromWorldChecked(m_World);

	FURL TestURL(&WorldContext.LastURL, *Cmd, TravelType);
	if (TestURL.IsLocalInternal())
	{
		// make sure the file exists if we are opening a local file
		if (!GEngine->MakeSureMapNameIsValid(TestURL.Map))
		{
			UE_LOG(LogLevel, Warning, TEXT("WARNING: The map '%s' does not exist."), *TestURL.Map);
		}
	}
	//FSlateApplication::Get().SetFocusToGameViewport();
    //FSlateApplication::Get().SetUserFocusToGameViewport(0);
    FSlateApplication::Get().SetAllUserFocusToGameViewport();
	GEngine->SetClientTravel(m_World, *Cmd, TravelType);
	
	CreateLoadingScreen();
	//////////////////////////////////////////////////////////////////////////
}

bool FEKSceneManager::LoadMapToNetWorke(FName inMapName, FString& host, int32 port)
{
	if (GWorld != nullptr)
	{
		m_World = GWorld;
	}
	if (GEngine)
	{
		if (m_World)
		{
			FString error;
			FURL url;
			url.Host = host;
			url.Port = port;
			url.Map = inMapName.ToString();
			auto UserId = FPlatformMisc::GetUniqueDeviceId();
			if (UserId.Len() > 0) {
				UserId = TEXT("udid=") + UserId;
				url.AddOption(*UserId);
			}
			auto idx = inMapName.ToString().Find(TEXT("?"));
			if (inMapName.ToString().IsValidIndex(idx)) 
			{
				url.Map = inMapName.ToString().Mid(0, idx);
				auto Options = inMapName.ToString().Mid(idx);
				FString Pair;

				while (UGameplayStatics::GrabOption(Options, Pair))
					url.AddOption(*Pair);
			}
			auto ctx = m_World->GetGameInstance()->GetWorldContext();

			return EBrowseReturnVal::Failure != GEngine->Browse(*ctx, url, error);
		}
	}

	return false;
}

void FEKSceneManager::AsyncLoadMap(const FString & inMapName)
{

	//////////////////////////////////////////////////////////////////////////
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = NULL;
	LatentInfo.UUID = 1025;
	LatentInfo.Linkage = 15;
	LatentInfo.ExecutionFunction = NAME_None;

	AsyncLoadMap(inMapName, LatentInfo);
}

void FEKSceneManager::AsyncLoadMap(const FString & inMapName, FName inCallbackTarget)
{

	//////////////////////////////////////////////////////////////////////////
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = NULL;
	LatentInfo.UUID = 0;
	LatentInfo.ExecutionFunction = inCallbackTarget;

	AsyncLoadMap(inMapName, LatentInfo);
}

void FEKSceneManager::AsyncLoadMap(const FString & inMapName, FLatentActionInfo& inActionInfo)
{

	//////////////////////////////////////////////////////////////////////////
#if WITH_EDITOR
#else
	check(m_World)

	FLatentActionManager& LatentManager = m_World->GetLatentActionManager();

	if (LatentManager.FindExistingAction<FStreamLevelAction>(NULL, inActionInfo.UUID) == NULL)
	{
		FStreamLevelAction* NewAction = new FStreamLevelAction(true, *inMapName, true, false, inActionInfo, m_World);
		LatentManager.AddNewAction(inActionInfo.CallbackTarget, inActionInfo.UUID, NewAction);

		//UE_LOG(LogScript, Warning, TEXT(" !!!! AEasyKit AsyncLoad Map !!!! %s "), *inMapName);
	}
#endif
}

void FEKSceneManager::AsyncUnLoadMap(const FString & inMapName)
{

	//////////////////////////////////////////////////////////////////////////
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = NULL;
	LatentInfo.UUID = 1025;
	LatentInfo.Linkage = 15;
	LatentInfo.ExecutionFunction = NAME_None;

	AsyncUnLoadMap(inMapName, LatentInfo);
}

void FEKSceneManager::AsyncUnLoadMap(const FString & inMapName, FLatentActionInfo& inActionInfo)
{
	if (inMapName == TEXT("/Game/Maps/1/Shared") || inMapName == TEXT("Shared") || FPackageName::GetShortName(inMapName) == TEXT("Shared") ) return;

	//////////////////////////////////////////////////////////////////////////
#if WITH_EDITOR
#else
	check(m_World)

		FLatentActionManager& LatentManager = m_World->GetLatentActionManager();

	if (LatentManager.FindExistingAction<FStreamLevelAction>(NULL, inActionInfo.UUID) == NULL)
	{
		FStreamLevelAction* NewAction = new FStreamLevelAction(false, *inMapName, false, false, inActionInfo, m_World);
		LatentManager.AddNewAction(inActionInfo.CallbackTarget, inActionInfo.UUID, NewAction);

		UE_LOG(LogScript, Warning, TEXT(" !!!! AEasyKit AsyncUnLoad Map !!!! %s "), *inMapName);
	}
#endif
}

void FEKSceneManager::Tick(float DeltaSeconds)
{
	AsynLoadMapCheck();
}

void FEKSceneManager::AsynLoadMapCheck()
{
//#ifdef EASYKIT_IOS
	if (aCurActor == nullptr) return;
	else
	{
		//std::vector<std::string> vRequiredMaps;
		std::vector<std::string> vCurrentMaps;
		sCurrentInMap.clear();

		TArray<class ULevelStreaming*>* StreamedLevels = &GetWorld()->StreamingLevels;

		ULevel* EachLevel = nullptr;
		for (int32 v = 0; v < StreamedLevels->Num(); v++)
		{
			if (!(*StreamedLevels)[v]) continue;
			//~~~~~~~~~~~~~~~~

			EachLevel = (*StreamedLevels)[v]->GetLoadedLevel();
			if (!EachLevel) continue;
			//~~~~~~~~~~~~

			//Is This Level Visible?
			if (!EachLevel->bIsVisible) continue;

			//if ((*StreamedLevels)[v]->PackageName.ToString() == TEXT("/Game/Maps/1/Shared")) return;
			//~~~~~~~~~~~~~~~~~~~

			std::string sMapTrueName;
			CalculateMapName(sMapTrueName, TCHAR_TO_ANSI(*(*StreamedLevels)[v]->PackageNameToLoad.ToString()));
			if (sMapTrueName == "Shared") continue;
			if (!sChangingMapName.empty() && sChangingMapName == sMapTrueName)
			{
				sChangingMapName.clear();
				bChangeMapInterval = true;

				FTimerHandle Chek;
				GetWorld()->GetTimerManager().SetTimer(Chek, FTimerDelegate::CreateRaw(this, &FEKSceneManager::ChangeMapIntervalTimerReach), fChangeMapIntervalTime, false);
			}
			vCurrentMaps.push_back(sMapTrueName);
		}

		
//#if WITH_EDITOR
//		for (TActorIterator<ATriggerVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
//#else
		for (TActorIterator<AVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
//#endif
		{
			if ((ActorItr->GetName())[0] == 'T' && ActorItr->GetComponentsBoundingBox().IsInside(aCurActor->GetActorLocation()))
			{
				//UE_LOG(LogScript, Warning, TEXT("Player Is Within %s Trigger Vol"), *ActorItr->GetName());

				if (sInLevel.empty())
				{
					CalculateMapName(sInLevel, TCHAR_TO_ANSI(*ActorItr->GetName()));
					CalculateAdjacentMaps(sInLevel, vInMaps);
				}

				if (sCurrentInMap.empty())
				{
					CalculateMapName(sCurrentInMap, TCHAR_TO_ANSI(*ActorItr->GetName()));
				}
			}
		}

		if (sCurrentInMap.empty() || sInLevel.empty()) return;

		// May change map, set timer to count down
		if (bTimer == false && sInLevel != sCurrentInMap && bChangeMapDuringChanging == false)
		{
			bTimer = true;
			FTimerHandle Change;
			GetWorld()->GetTimerManager().SetTimer(Change, FTimerDelegate::CreateRaw( this, &FEKSceneManager::ChangeMapTimerReach), fChangeMapOffSetTime, false);
		}

		/*if (bTimer == true && sInLevel == sCurrentInMap)
		{
		bTimer = false;
		GetWorld()->GetTimerManager().ClearTimer(FTimerDelegate::CreateRaw(this, &FEKSceneManager::ChangeMapTimerReach));
		}*/

		//CalculateAdjacentMaps(sInLevel, vRequiredMaps);

		if (!sRequiredUnloadMapName.empty() && std::find(vInMaps.begin(), vInMaps.end(), sRequiredUnloadMapName) == vInMaps.end())
		{
			// Unload sRequiredUnloadMap Finish, Rest interval time
			sRequiredUnloadMapName.clear();
			bChangeMapInterval = true;
			FTimerHandle Interval;
			GetWorld()->GetTimerManager().SetTimer(Interval, FTimerDelegate::CreateRaw( this, &FEKSceneManager::ChangeMapIntervalTimerReach), fChangeMapIntervalTime, false);
		}

		UnloadNotRequiredMaps(vCurrentMaps, vInMaps);

		LoadRequiredMaps(vCurrentMaps, vInMaps);

	}
//#endif
}

void FEKSceneManager::CalculateMapName(std::string & sOut, const std::string & sIn)
{
	if(!sIn.empty() && sIn[0] == 'T')
	{
		sOut = sIn.substr(14);
		return;
	}
	int32 nLastSlashIndex = sIn.find_last_of('/');
	sOut = sIn.substr(nLastSlashIndex + 1);
}

void FEKSceneManager::ChangeMapTimerReach()
{
	if (!CheckMapIsInMapContainers(sCurrentInMap, vInMaps))
	{
		UE_LOG(LogScript, Warning, TEXT("!!!!!!!!!!!!!!!!!!! FATAL WARNING, TELEPORT IN MAP, MAY CRASH !!!!!!!!!!!!!!!!!!!!"));
	}

	bTimer = false;

	if (sCurrentInMap.empty()) return;

	if (bChangeMapInProcess || bChangeMapInterval)
	{
		bChangeMapDuringChanging = true;
	}
	else
	{
		sInLevel = sCurrentInMap;
		CalculateAdjacentMaps(sInLevel, vInMaps);
	}
}

void FEKSceneManager::ChangeMapIntervalTimerReach()
{
	bChangeMapInterval = false;
	bChangeMapInProcess = false;
	if (bChangeMapDuringChanging == true)
	{
		bChangeMapDuringChanging = false;
		sInLevel = sCurrentInMap;
		CalculateAdjacentMaps(sInLevel, vInMaps);
	}
}

bool FEKSceneManager::CheckMapIsInMapContainers(const std::string & sMap, const std::vector<std::string> & vMaps)
{
	if (std::find(vMaps.begin(), vMaps.end(), sMap) == vMaps.end())
	{
		return false;
	}
	return true;
}

void FEKSceneManager::CalculateAdjacentMaps(const std::string & sCenterMap, std::vector<std::string> & vAdjacentMaps)
{
	// /Game/Maps/1/0_0
	vAdjacentMaps.clear();

	//int32 nLastSlashIndex = sCenterMap.find_last_of('/');
	int32 nUnderLineIndex = sCenterMap.find_last_of('_');
	int32 nMapIndexX = std::stoi(sCenterMap.substr(0, nUnderLineIndex));
	int32 nMapIndexY = std::stoi(sCenterMap.substr(nUnderLineIndex + 1));


	StoreMapFullName(nMapIndexX - 1, nMapIndexY - 1, vAdjacentMaps);
	StoreMapFullName(nMapIndexX - 1, nMapIndexY, vAdjacentMaps);
	StoreMapFullName(nMapIndexX - 1, nMapIndexY + 1, vAdjacentMaps);

	StoreMapFullName(nMapIndexX, nMapIndexY - 1, vAdjacentMaps);
	StoreMapFullName(nMapIndexX, nMapIndexY, vAdjacentMaps);
	StoreMapFullName(nMapIndexX, nMapIndexY + 1, vAdjacentMaps);

	StoreMapFullName(nMapIndexX + 1, nMapIndexY - 1, vAdjacentMaps);
	StoreMapFullName(nMapIndexX + 1, nMapIndexY, vAdjacentMaps);
	StoreMapFullName(nMapIndexX + 1, nMapIndexY + 1, vAdjacentMaps);
	 
}

void FEKSceneManager::StoreMapFullName(int32 x, int32 y, std::vector<std::string> & vMaps)
{
	if (x < PANDA_MAP_MIN || x > PANDA_MAP_MAX || y < PANDA_MAP_MIN || y > PANDA_MAP_MAX) return;
	//vMaps.push_back(PANDA_MAP_PATH_NAME_PRE + std::to_string(x) + PANDA_MAP_PATH_NAME_CAT + std::to_string(y));
	vMaps.push_back(std::to_string(x) + PANDA_MAP_PATH_NAME_CAT + std::to_string(y));
}

void FEKSceneManager::UnloadNotRequiredMaps(std::vector<std::string> & vCurrentMaps, std::vector<std::string> & vRequiredMaps)
{

	for (auto & sCurrentMap : vCurrentMaps)
	{
		if (std::find(vRequiredMaps.begin(), vRequiredMaps.end(), sCurrentMap) == vRequiredMaps.end())
		{

			if (bChangeMapInProcess == false && bChangeMapInterval == false)
			{
				// Unload sCurrentMap
				bChangeMapInProcess = true;
				sRequiredUnloadMapName = sCurrentMap;
				FString fs(sCurrentMap.c_str());
				fs = PANDA_MAP_PATH_NAME_PRE + fs;
				AsyncUnLoadMap(fs);
				return;
			}
			return;
		}
	}
}

void FEKSceneManager::LoadRequiredMaps(std::vector<std::string> & vCurrentMaps, std::vector<std::string> & vRequiredMaps)
{

	for (auto & sRequiredMap : vRequiredMaps)
	{
		if (std::find(vCurrentMaps.begin(), vCurrentMaps.end(), sRequiredMap) == vCurrentMaps.end())
		{

			// load sCurrentMap
			if (bChangeMapInProcess == false && bChangeMapInterval == false)
			{
				bChangeMapInProcess = true;
				sChangingMapName = sRequiredMap;
				FString fs(sRequiredMap.c_str());
				fs = PANDA_MAP_PATH_NAME_PRE + fs;
				AsyncLoadMap(fs);
				return;
			}
			return;
		}
	}
}

void FEKSceneManager::SetCurrentLevel(class Ulevel* inLevel)
{
	M_CurrentLevel = inLevel;
}

void FEKSceneManager::AddActorToMap(class AActor* inActor)
{
	
}

void FEKSceneManager::SetCurActor(AActor * aActor)
{
	aCurActor = aActor;
}

void FEKSceneManager::ServerExecEnterView(const std::vector<EKSceneManagerStruct::EnterViewSyncData> & birthData)
{
	for (auto & bd : birthData)
	{
		auto livePool_iter = liveCharacterPool.find(bd.guid);
		if (livePool_iter != liveCharacterPool.end())
		{
			continue;
		}

		if (botPool.empty())
		{
			UE_LOG(LogScript, Warning, TEXT("!!!!!!!!!!!!!!!!!!! FATAL WARNING, POOL STACK IS EMPTY !!!!!!!!!!!!!!!!!!!!"));
			return;
		}

		AEKCharacter* aekc = botPool.top();
		if (aekc == nullptr || !aekc->IsValidLowLevel())
		{
			UE_LOG(LogScript, Warning, TEXT("!!!!!!!!!!!!!!!!!!! FATAL WARNING, DEAD BOT IS NOT VALID IN POOL !!!!!!!!!!!!!!!!!!!!"));
			return;
		}

		aekc->nGUID = bd.guid;
		aekc->nCharacterID = bd.characterID;
		aekc->fsName = bd.name;
		aekc->Health = bd.hp;

		if (!aekc->RefreshAttrByID(bd.characterID))
		{
			UE_LOG(LogScript, Warning, TEXT("!!!!!!!!!!!!!!!!!!! FATAL WARNING, REFRESH ATTRI ERROR: %d !!!!!!!!!!!!!!!!!!!!"), bd.characterID);
			continue;
		}

		if (!aekc->ChangeMeshesByID(bd.characterID))
		{ 
			UE_LOG(LogScript, Warning, TEXT("!!!!!!!!!!!!!!!!!!! FATAL WARNING, CANNOT FOUND MESHES FOR CHAR: %d !!!!!!!!!!!!!!!!!!!!"), bd.characterID);
			continue;
		}

		aekc->SetActorTickEnabled(true);
		aekc->SetActorHiddenInGame(false);
		aekc->bIsUpdateTick = true;

		TArray<UActorComponent*> Components;
		aekc->GetComponents(Components);

		for (int32 j = 0; j < Components.Num(); ++j)
		{
			Components[j]->Activate();
		}

		FVector fvTmp = bd.pos;

		fvTmp.Z = CAY_START_MAX_Y;
		aekc->SetActorLocation(fvTmp);
		fvTmp.Z = CAY_END_MIN_Y;
		aekc->SetActorLocation(fvTmp, true);

		aekc->mPlayerState->SetDefaultState(Player_State::StateType::EKState_Idle, "PandaBotState");

		liveCharacterPool.insert({ bd.guid, aekc });
		botPool.pop();
	}

}

void FEKSceneManager::ServerExecLeaveView(const std::vector<EKSceneManagerStruct::LeaveViewSyncData> & dieData)
{
	for (auto & dd : dieData)
	{
		auto iter = liveCharacterPool.find(dd.guid);
		if (iter != liveCharacterPool.end())
		{
			AEKCharacter* aekc = iter->second;

			if (aekc == nullptr || !aekc->IsValidLowLevel())
			{
				UE_LOG(LogScript, Warning, TEXT("!!!!!!!!!!!!!!!!!!! FATAL WARNING, DEAD BOT IS NOT VALID IN LIVE POOL !!!!!!!!!!!!!!!!!!!!"));
				return;
			}

			aekc->SetActorLocation(FVector::ZeroVector);

			TArray<UActorComponent*> Components;
			aekc->GetComponents(Components);

			for (int32 j = 0; j < Components.Num(); ++j)
			{
				Components[j]->Deactivate();
			}

			////aPandaCharacter->TurnOff();
			aekc->bIsUpdateTick = false;
			aekc->SetActorHiddenInGame(true);
			aekc->SetActorTickEnabled(false);

			aekc->mPlayerState->GetFSMManager("PandaBotState")->ChangeState(Player_State::StateType::EKState_Idle);
			
			botPool.push(aekc);
			liveCharacterPool.erase(iter);
		}
	}
}

void FEKSceneManager::ServerExecLocationSync(const std::vector<EKSceneManagerStruct::LocationSyncData> & locSyncData)
{
	for (auto & lyData : locSyncData)
	{
		auto iter = liveCharacterPool.find(lyData.guid);
		if (iter != liveCharacterPool.end())
		{
			AEKCharacter* aekc = iter->second;
			aekc->ReceiveServerSync(lyData.pos);
		}
	}
}

void FEKSceneManager::ServerExecPlayerMove(const EKSceneManagerStruct::PlayerMoveData & playerMoveData)
{

	if (playerMoveData.result == 0)
		GetLocalPlayer()->ReceiveServerMove(playerMoveData.pos);
}


AEKCharacter* FEKSceneManager::ServerExecGetPawn(int64_t id)
{
	auto iter = liveCharacterPool.find(id);
	if (iter != liveCharacterPool.end())
	{
		return iter->second;
	}
	return nullptr;
}

void FEKSceneManager::TestMovement()
{
	auto iter = liveCharacterPool.find(1);
	if (iter != liveCharacterPool.end())
	{
		AEKCharacter* aekc = iter->second;

		AController* controller = aekc->GetController();
		AActor* aactor = aekc->GetOwner();


		aekc->TestMoveSelf();
		//aekc->CharacterMovement->MoveSmooth(v, 1000);
		//aekc->AddMovementInput(FVector(0.5f, 0.5f, 0));
		//aekc->SetActorRelativeLocation(FVector(-1500, 1500, 0));
	}

	auto iter1 = liveCharacterPool.find(2);
	if (iter1 != liveCharacterPool.end())
	{
		AEKCharacter* aekc = iter1->second;

		AController* controller = aekc->GetController();
		AActor* aactor = aekc->GetOwner();

		aekc->TestMoveSelf();
	}
}


void FEKSceneManager::SetLocalPlayer(class AEKCharacter* inPlayer)
{
	m_pLocalPlayer = inPlayer;

	if (m_pLocalPlayer != NULL)
		SetCurActor(m_pLocalPlayer);
	else
		UE_LOG(LogScript, Warning, TEXT("  No Have Player !   "));
}

AEKCharacter* FEKSceneManager::GetLocalPlayer()
{
	return m_pLocalPlayer;
}


void FEKSceneManager::SetController(class APlayerController* inController)
{
	m_Controller = inController;

	if (m_Controller == nullptr) UE_LOG(LogScript, Warning, TEXT("EK Scene Manager: Cannot set controller for this world."));
}

APlayerController* FEKSceneManager::GetController()
{
	return m_Controller;
}

bool FEKSceneManager::ChangePossessedPawn(APawn *inPawn)
{
	APlayerController *pc = UGameplayStatics::GetPlayerController(GWorld, 0);
	if (pc != NULL && !pc->IsPendingKill() && pc->IsValidLowLevel())
	{
		pc->Possess(inPawn);
		return true;
	}
	else
	{
		return false;
	}
}

APlayerController* FEKSceneManager::ChangeController(TSubclassOf<class APlayerController> playerControllerClass)
{
	AGameMode *gm = GWorld->GetAuthGameMode();
	APlayerController *pc = UGameplayStatics::GetPlayerController(GWorld, 0);
	if (playerControllerClass != NULL && gm != NULL && pc != NULL && !pc->IsPendingKill() && pc->IsValidLowLevel() && pc->GetClass() != playerControllerClass)
	{
		if (pc->Player != NULL)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Instigator = gm->Instigator;
			APlayerController* newPC = GWorld->SpawnActor<APlayerController>(playerControllerClass, pc->GetFocalLocation(), pc->GetControlRotation(), SpawnInfo);

			if (newPC == NULL)
			{
				UE_LOG(LogScript, Warning, TEXT("Failed to spawn new PlayerController for %s (old class %s)"), *pc->GetHumanReadableName(), *pc->GetClass()->GetName());
				pc->Destroy();
				return nullptr;
			}
			else
			{
				pc->CleanUpAudioComponents();
				newPC->Possess(pc->GetPawn());
				gm->SwapPlayerControllers(pc, newPC);
				newPC->AcknowledgedPawn = newPC->GetPawn();
				// Cannot transfer pawn from old one to the new one, because deleting old pc will delete pawn. If you transfer it before swap pc, the "AcknowledgedPawn" will not be assigned (It must has ULocalPlayer first), which will prevent controller rotation.
				return newPC;
			}
		}
		else
		{
			pc->Destroy();
			return nullptr;
		}
	}
	return nullptr;
}

void FEKSceneManager::ChangeController(APlayerController *newPC)
{
	if (newPC == nullptr || !newPC->IsValidLowLevel() || newPC->IsPendingKill()) return;
	
	AGameMode *gm = GWorld->GetAuthGameMode();
	APlayerController *pc = UGameplayStatics::GetPlayerController(GWorld, 0);

	if (gm != NULL && pc != NULL && !pc->IsPendingKill() && pc->IsValidLowLevel() && pc->GetClass() != newPC->GetClass())
	{
		if (pc->Player != NULL)
		{
			pc->CleanUpAudioComponents();
			newPC->Possess(pc->GetPawn());
			gm->SwapPlayerControllers(pc, newPC);
			newPC->AcknowledgedPawn = newPC->GetPawn();
			// Cannot transfer pawn from old one to the new one, because deleting old pc will delete pawn. If you transfer it before swap pc, the "AcknowledgedPawn" will not be assigned (It must has ULocalPlayer first), which will prevent controller rotation.
		}
		else
		{
			pc->Destroy();
		}
	}
}

bool FEKSceneManager::ChangeViewTarget(class AActor* NewViewTarget, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing)
{
	APlayerController *pc = UGameplayStatics::GetPlayerController(GWorld, 0);
	if (pc != NULL && !pc->IsPendingKill() && pc->IsValidLowLevel())
	{
		pc->SetViewTargetWithBlend(NewViewTarget, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
		return true;
	}
	else
	{
		return false;
	}
}
