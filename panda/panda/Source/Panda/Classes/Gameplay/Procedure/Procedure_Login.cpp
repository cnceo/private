// Copyright 1995-2016. All Rights Reserved.
// Created by ������ 


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
				//����loading���档
				//UGeometryGameInstance* tmpGI = Cast<UGeometryGameInstance>(UGameplayStatics::GetGameInstance(FEKGameFrame::Instance()->SceneManager()->GetWorld()));
				//tmpGI->CreateLoadingScreen();
				// ����ͼ����
				if (true)
				{
					FEKGameFrame::Instance()->SceneManager()->CreateLoadingScreen();
				}
			}
		}

		//ע��Pre Load Mapί�У��ڸ�ί�к����в���loading���档
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
	//	//����ɹ�����loading���棬ע��Post Load Mapί�У��ڸ�ί���н���loading����
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

	//���������������̬loading������ʽloading��
	FEKGameFrame::Instance()->HUDManager()->ShowWindow("Login");

	//while (!isAsyncLoadingFinish)
	//{
	//	//�������������ģ�����Ҫ�첽ִ�е�loading���ݣ����Ƽ�ʹ������ʽloading��
	//	UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
	//	//Sleep(1000);
	//}

	//����loading����
	//GetMoviePlayer()->WaitForMovieToFinish();
}

void FProcedure_Login::Leave()
{
	FEKProcedureBase::Leave();


	FEKGameFrame::Instance()->HUDManager()->HideWindow("Login", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure Login %d"), n_ID);
}
