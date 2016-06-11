// Copyright 1995-2016. All Rights Reserved.
// Created by ������ 


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
		//����loading���档
		if (GWorld == nullptr)
		{
			if (FEKGameFrame::Instance()->SceneManager()->GetWorld() != nullptr)
			{
				// ����ͼ����
				if (true)
				{
					FEKGameFrame::Instance()->SceneManager()->CreateLoadingScreen();
				}
			}
		}

		//ע��Pre Load Mapί�У��ڸ�ί�к����в���loading���档
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
	//	//����ɹ�����loading���棬ע��Post Load Mapί�У��ڸ�ί���н���loading����
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

	//���������������̬loading������ʽloading��
	//FEKGameFrame::Instance()->HUDManager()->ShowWindow("CreateChar");

	//while (!isAsyncLoadingFinish)
	//{
	//	//�������������ģ�����Ҫ�첽ִ�е�loading���ݣ����Ƽ�ʹ������ʽloading��
	//	UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
	//	//Sleep(1000);
	//}


	//����loading����
	GetMoviePlayer()->WaitForMovieToFinish();
}

void FProcedure_Club::Leave()
{
	FEKProcedureBase::Leave();

	//FEKGameFrame::Instance()->HUDManager()->HideWindow("Login");

	//FEKGameFrame::Instance()->HUDManager()->HideWindow("SelectChar", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure SelectChar %d"), n_ID);
}
