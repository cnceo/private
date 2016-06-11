// Copyright 1995-2016. All Rights Reserved.
// Created by 尹俊旭 


#include "panda.h"
#include "MoviePlayer.h"
#include "EKGameFrame.h"
#include "EKHUDManager.h"
#include "EKProcedureManager.h"
#include "PandaGameInstance.h"
#include "Procedure_Login.h"


std::atomic<bool> isAsyncLoadingFinish(false);

FProcedure_Login::FProcedure_Login(uint64 inID)
	:FEKProcedureBase(inID)
	,isSendLogin(false)
{

}

void FProcedure_Login::Init()
{
	return FEKProcedureBase::Init();
}

void FProcedure_Login::Tick(float inDeltaTime)
{
	FEKProcedureBase::Tick(inDeltaTime);
}

void FProcedure_Login::Enter()
{
	FEKProcedureBase::Enter();

	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Login %d"), n_ID);

	if (FEKGameFrame::Instance()->SceneManager()->LoadMap(TEXT("LoginMap")))
	{
		if (GWorld == nullptr)
		{
			if (FEKGameFrame::Instance()->SceneManager()->GetWorld() != nullptr)
			{
				//设置loading界面。
				//UGeometryGameInstance* tmpGI = Cast<UGeometryGameInstance>(UGameplayStatics::GetGameInstance(FEKGameFrame::Instance()->SceneManager()->GetWorld()));
				//tmpGI->CreateLoadingScreen();
				// 检查地图数据
				if (true)
				{
					FEKGameFrame::Instance()->SceneManager()->CreateLoadingScreen();
				}
			}
		}

		//注册Pre Load Map委托，在该委托函数中播放loading画面。
		delegateHandle = FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FProcedure_Login::PreLoadMap);
	}
}

void FProcedure_Login::PreLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Login %d PreLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PreLoadMap.RemoveRaw(this, &FProcedure_Login::PreLoadMap);
	FCoreUObjectDelegates::PreLoadMap.Remove(delegateHandle);

	//isAsyncLoadingFinish.exchange(false);

	//if (GetMoviePlayer()->PlayMovie())
	//{
	//	//如果成功播放loading画面，注册Post Load Map委托，在该委托中结束loading画面
	//	FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_Login::PostLoadMap);
	//}

	//GetMoviePlayer()->PlayMovie();
	delegateHandle = FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_Login::PostLoadMap);
}

void FProcedure_Login::PostLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Login %d PostLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PostLoadMap.RemoveRaw(this, &FProcedure_Login::PostLoadMap);
	FCoreUObjectDelegates::PostLoadMap.Remove(delegateHandle);

	//在这里进行其他动态loading等阻塞式loading。
	FEKGameFrame::Instance()->HUDManager()->ShowWindow("Login");

	//while (!isAsyncLoadingFinish)
	//{
	//	//在这里进行网络模块等需要异步执行的loading内容，但推荐使用阻塞式loading。
	//	UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
	//	//Sleep(1000);
	//}

	//结束loading画面
	//GetMoviePlayer()->WaitForMovieToFinish();
}

void FProcedure_Login::Leave()
{
	FEKProcedureBase::Leave();


	FEKGameFrame::Instance()->HUDManager()->HideWindow("Login", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure Login %d"), n_ID);
}
