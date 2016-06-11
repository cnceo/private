// Copyright 1995-2016. All Rights Reserved.
// Created by ������ 


#include "panda.h"
#include "MoviePlayer.h"
#include "EKGameFrame.h"
#include "EKHUDManager.h"
#include "EKProcedureManager.h"
#include "PandaGameInstance.h"
#include "Procedure_SelectChar.h"



FProcedure_SelectChar::FProcedure_SelectChar(uint64 inID)
	:FEKProcedureBase(inID)
	,isSendLogin(false)
{

}

void FProcedure_SelectChar::Init()
{
	return FEKProcedureBase::Init();
}

void FProcedure_SelectChar::Tick(float inDeltaTime)
{
	FEKProcedureBase::Tick(inDeltaTime);
}

void FProcedure_SelectChar::Enter()
{
	FEKProcedureBase::Enter();

	UE_LOG(LogScript, Warning, TEXT("Enter Procedure SelectChar %d"), n_ID);

	if (FEKGameFrame::Instance()->SceneManager()->LoadMap(TEXT("SelectCharMap")))
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
		delegateHandle = FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FProcedure_SelectChar::PreLoadMap);
	}
}

void FProcedure_SelectChar::PreLoadMap()
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
	delegateHandle = FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_SelectChar::PostLoadMap);
}

void FProcedure_SelectChar::PostLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure SelectChar %d PostLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PostLoadMap.RemoveRaw(this, &FProcedure_Login::PostLoadMap);
	FCoreUObjectDelegates::PostLoadMap.Remove(delegateHandle);

	//���������������̬loading������ʽloading��
	FEKGameFrame::Instance()->HUDManager()->ShowWindow("CreateChar");

	//while (!isAsyncLoadingFinish)
	//{
	//	//�������������ģ�����Ҫ�첽ִ�е�loading���ݣ����Ƽ�ʹ������ʽloading��
	//	UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
	//	//Sleep(1000);
	//}

	APlayerController* PC = GWorld->GetFirstLocalPlayerFromController()->GetPlayerController(GWorld);
	ASelectCharPC* SelectPC = Cast<ASelectCharPC>(PC);
	if (SelectPC)
	{
		SelectPC->InitSelectCharScene();
	}

	//����loading����
	GetMoviePlayer()->WaitForMovieToFinish();
}

void FProcedure_SelectChar::Leave()
{
	FEKProcedureBase::Leave();

	//FEKGameFrame::Instance()->HUDManager()->HideWindow("Login");

	FEKGameFrame::Instance()->HUDManager()->HideWindow("SelectChar", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure SelectChar %d"), n_ID);
}
