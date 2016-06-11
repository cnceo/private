// Copyright 1995-2016. All Rights Reserved.
// Created by ������ 


#include "panda.h"
#include "MoviePlayer.h"
#include "EKGameFrame.h"
#include "EKHUDManager.h"
#include "EKProcedureManager.h"
#include "PandaGameInstance.h"
#include "Procedure_CreaterChar.h"
#include "SelectCharPC.h"



FProcedure_CreaterChar::FProcedure_CreaterChar(uint64 inID)
	:FEKProcedureBase(inID)
	,isSendLogin(false)
{

}

void FProcedure_CreaterChar::Init()
{
	return FEKProcedureBase::Init();
}

void FProcedure_CreaterChar::Tick(float inDeltaTime)
{
	FEKProcedureBase::Tick(inDeltaTime);
}

void FProcedure_CreaterChar::Enter()
{
	FEKProcedureBase::Enter();

	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Creater %d"), n_ID);

	if (FEKGameFrame::Instance()->SceneManager()->LoadMap(TEXT("SelectRoleMap")))
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
		delegateHandle = FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FProcedure_CreaterChar::PreLoadMap);
	}
}

void FProcedure_CreaterChar::PreLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Login %d PreLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PreLoadMap.RemoveRaw(this, &FProcedure_CreaterChar::PreLoadMap);
	FCoreUObjectDelegates::PreLoadMap.Remove(delegateHandle);

	isAsyncLoadingFinish.exchange(false);

	//if (GetMoviePlayer()->PlayMovie())
	//{
	//	//����ɹ�����loading���棬ע��Post Load Mapί�У��ڸ�ί���н���loading����
	//	FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_CreaterChar::PostLoadMap);
	//}

	GetMoviePlayer()->PlayMovie();
	delegateHandle = FCoreUObjectDelegates::PostLoadMap.AddRaw(this, &FProcedure_CreaterChar::PostLoadMap);
}

void FProcedure_CreaterChar::PostLoadMap()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Login %d PostLoadMap()"), n_ID);

	//FCoreUObjectDelegates::PostLoadMap.RemoveRaw(this, &FProcedure_CreaterChar::PostLoadMap);
	FCoreUObjectDelegates::PostLoadMap.Remove(delegateHandle);

	//���������������̬loading������ʽloading��
	FEKGameFrame::Instance()->HUDManager()->ShowWindow("CreateChar");

	while (!isAsyncLoadingFinish)
	{
		//�������������ģ�����Ҫ�첽ִ�е�loading���ݣ����Ƽ�ʹ������ʽloading��
		UE_LOG(LogScript, Warning, TEXT(" !!!! Waiting Loading !!!! "));
		Sleep(500);
	}

	//����loading����
	GetMoviePlayer()->WaitForMovieToFinish();
}

void FProcedure_CreaterChar::Leave()
{
	FEKProcedureBase::Leave();


	FEKGameFrame::Instance()->HUDManager()->HideWindow("CreateChar", true);

	UE_LOG(LogScript, Warning, TEXT("Leave Procedure Creater %d"), n_ID);
}
