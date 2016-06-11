// Copyright 1995-2016. All Rights Reserved.
// Created by 尹俊旭 


#include "panda.h"
#include "MoviePlayer.h"
#include "EKGameFrame.h"
#include "EKHUDManager.h"
#include "EKProcedureManager.h"
#include "PandaGameInstance.h"
#include "Procedure_Club.h"



FProcedure_Club::FProcedure_Club(uint64 inID)
	:FEKProcedureBase(inID)
	,isSendLogin(false)
{

}

void FProcedure_Club::Init()
{
	return FEKProcedureBase::Init();
}

void FProcedure_Club::Tick(float inDeltaTime)
{
	FEKProcedureBase::Tick(inDeltaTime);
}

void FProcedure_Club::Enter()
{
	FEKProcedureBase::Enter();

	UE_LOG(LogScript, Warning, TEXT("Enter Procedure ClubMap %d"), n_ID);

	if (FEKGameFrame::Instance()->SceneManager()->LoadMap(TEXT("ClubMap")))
	{
		//设置loading界面。
		if (GWorld == nullptr)
		{
			if (FEKGameFrame::Instance()->SceneManager()->GetWorld() != nullptr)
			{
				// 检查地图数据
				if (true)
				{
					FEKGameFrame::Instance()->SceneManager()->CreateLoadingScreen();
				}
			}
		}

		//注册Pre Load Map委托，在该委托函数中播放loading画面。
		delegateHandle = FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FProcedure_Club::PreLoadMap);
	}
}

void FProcedure_Club::PreLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure SelectChar %d PreLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PreLoadMap.RemoveRaw(this, &FProcedure_Login::PreLoadMap);
	FCoreUObjectDelegates::PreLoadMap.Remove(delegateHandle);

	//isAsyncLoadingFinish.exchange(false);

	//if (GetMoviePlayer()->PlayMovie())
	//{
	//	//如果成功播放loading画面，注册Post Load Map委托，在该委托中结束loading画面
	//	FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_Login::PostLoadMap);
	//}

	GetMoviePlayer()->PlayMovie();
	delegateHandle = FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_Club::PostLoadMap);
}

void FProcedure_Club::PostLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure SelectChar %d PostLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PostLoadMap.RemoveRaw(this, &FProcedure_Login::PostLoadMap);
	FCoreUObjectDelegates::PostLoadMap.Remove(delegateHandle);

	//在这里进行其他动态loading等阻塞式loading。
	//FEKGameFrame::Instance()->HUDManager()->ShowWindow("CreateChar");

	//while (!isAsyncLoadingFinish)
	//{
	//	//在这里进行网络模块等需要异步执行的loading内容，但推荐使用阻塞式loading。
	//	UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
	//	//Sleep(1000);
	//}


	//结束loading画面
	GetMoviePlayer()->WaitForMovieToFinish();
}

void FProcedure_Club::Leave()
{
	FEKProcedureBase::Leave();

	//FEKGameFrame::Instance()->HUDManager()->HideWindow("Login");

	//FEKGameFrame::Instance()->HUDManager()->HideWindow("SelectChar", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure SelectChar %d"), n_ID);
}
