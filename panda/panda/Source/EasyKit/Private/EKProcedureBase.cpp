// Copyright 1995-2014 Î÷É½¾Ó. All Rights Reserved.
// Created by Òü¿¡Ðñ 
// Edited by ÉòÇ« on Oct 22, 2014

#include "EasyKit.h"
#include "EKGameFrame.h"
#include "EKProcedureManager.h"
#include "EKProcedureBase.h"

FEKProcedureBase::FEKProcedureBase(uint64 inID)
:n_ID(inID)
,f_ElapsedTime(0.f)
{
	m_EKProcedureMgr = FEKGameFrame::Instance()->ProcedureManager();
}

FEKProcedureBase::~FEKProcedureBase()
{
}

void FEKProcedureBase::Init()
{
	Register();
}

void FEKProcedureBase::Tick(float inDeltaTime)
{
	f_ElapsedTime += inDeltaTime;

	//GetSceneFSM()->Tick(inDeltaTime);
}

void FEKProcedureBase::Enter()
{
	UE_LOG(LogScript, Warning, TEXT("Enter Procedure Base %d"), n_ID);

	f_ElapsedTime = 0;
}

void FEKProcedureBase::Leave()
{
	UE_LOG(LogScript, Warning, TEXT("Leave Procedure Base %d"), n_ID);

	//GetSceneFSM()->ResetCurrentScene();

	f_ElapsedTime = 0; 
}

//TSharedPtr<class FEKSceneFSM> FEKProcedureBase::GetSceneFSM()
//{
//	if (!sp_SceneFSM.IsValid())
//	{
//		sp_SceneFSM = MakeShareable(new FEKSceneFSM(AsShared()));
//	}
//	return sp_SceneFSM;
//}

bool FEKProcedureBase::Register()
{
	if (m_EKProcedureMgr == nullptr) return false;

	m_EKProcedureMgr->RegisterProcedure(AsShared());
	return true;
}
