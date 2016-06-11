// Copyright 1995-2016. All Rights Reserved.
// Created by 尹俊旭 on 05,04,2016

#include "panda.h"
#include "MoviePlayer.h"
#include "EKGameFrame.h"
#include "EKHUDManager.h"
#include "EKProcedureManager.h"
#include "PandaGameInstance.h"
#include "Procedure_Scene.h"



FProcedure_Scene::FProcedure_Scene(uint64 inID)
	:FEKProcedureBase(inID)
	//, mLandscape(nullptr)
{

}

void FProcedure_Scene::Init()
{
	return FEKProcedureBase::Init();
}

void FProcedure_Scene::Tick(float inDeltaTime)
{
	FEKProcedureBase::Tick(inDeltaTime);

	//UPackage* LevelPackage = FindObjectFast<UPackage>(NULL, FName("/Game/Maps/DemoScene"));

	//if (LevelPackage && (LevelPackage->GetLoadTime() > 0))
	//{
	//	UE_LOG(LogScript, Warning, TEXT("LevelStreaming Progress is %d "), (int)LevelPackage->GetLoadTime());
	//}
	//else
	//{
	//	const float LevelLoadPercentage = GetAsyncLoadPercentage(FName("/Game/Maps/DemoScene"));
	//	if (LevelLoadPercentage >= 0.0f)
	//	{
	//		UE_LOG(LogScript, Warning, TEXT("LevelStreaming Progress is %d "), (int)LevelLoadPercentage);
	//	}
	//}

}

void FProcedure_Scene::Enter()
{
	FEKProcedureBase::Enter();

	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Login %d"), n_ID);

	FString IPstr = "127.0.0.1";
	bool isTrue = FEKGameFrame::Instance()->SceneManager()->LoadMap(TEXT("Scene_MainMap"));
	//if (FEKGameFrame::Instance()->SceneManager()->LoadMap(TEXT("BaseMap")))
	if(isTrue)
	{
		//SaintMoore_capitalgate
		//设置loading界面。
		if (GWorld == nullptr)
		{
			// 检查地图数据
			if (true)
			{
				FEKGameFrame::Instance()->SceneManager()->CreateLoadingScreen();
			}
		}

		//注册Pre Load Map委托，在该委托函数中播放loading画面。
		delegateHandle = FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FProcedure_Scene::PreLoadMap);
	}
}

void FProcedure_Scene::PreLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure BaseMap %d PreLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PreLoadMap.RemoveRaw(this, &FProcedure_Scene::PreLoadMap);
	FCoreUObjectDelegates::PreLoadMap.Remove(delegateHandle);

	//isAsyncLoadingFinish.exchange(false);

	//if (GetMoviePlayer()->PlayMovie())
	//{
	//	//如果成功播放loading画面，注册Post Load Map委托，在该委托中结束loading画面
	//	FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_Scene::PostLoadMap);
	//}
	// 检查地图数据

	GetMoviePlayer()->PlayMovie();
	delegateHandle = FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_Scene::PostLoadMap);
}

void FProcedure_Scene::PostLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure BaseMap %d PostLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PostLoadMap.RemoveRaw(this, &FProcedure_Scene::PostLoadMap);
	FCoreUObjectDelegates::PostLoadMap.Remove(delegateHandle);

	//在这里进行其他动态loading等阻塞式loading。
	//InitLandscape();

	//while (!isAsyncLoadingFinish)
	//{
	//	//在这里进行网络模块等需要异步执行的loading内容，但推荐使用阻塞式loading。
	//	UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
	//	//Sleep(1000);
	//}

	//结束loading画面
	GetMoviePlayer()->WaitForMovieToFinish();
}

//void FProcedure_Scene::InitLandscape()
//{
//	if (GWorld != nullptr)
//	{
//		mLandscape = GWorld->SpawnActor<AElementLandscape>();
//	}
//
//}
//
//AElementLandscape* FProcedure_Scene::GetLandscape()
//{
//	if (mLandscape == nullptr)
//	{
//		mLandscape = GWorld->SpawnActor<AElementLandscape>();
//	}
//	return mLandscape;
//}

void FProcedure_Scene::Leave()
{
	FEKProcedureBase::Leave();

	FEKGameFrame::Instance()->HUDManager()->HideWindow("Mian", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure BaseMap %d"), n_ID);
}
