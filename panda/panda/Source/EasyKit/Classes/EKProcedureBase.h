// Copyright 1995-2014 ��ɽ��. All Rights Reserved.
// Created by ������
// Edited by ��ǫ on Oct 22, 2014

/*=============================================================================
The game logic procedure.
It has multiple different scenes which belong to same procedure.
It may be login, select character, main game world, and so on.
=============================================================================*/


#pragma once

namespace EKType
{
	enum Procedure
	{
		PT_None,
		PT_Login,		// ��¼
		PT_Character,	// ѡ��ɫ
		PT_World,		// ����
		PT_Home		// �ؼ�
	};
}

class EASYKIT_API FEKProcedureBase : public TSharedFromThis<FEKProcedureBase>
{
private:

	// The Finite State Machine of Scenes belong to this procedure.
	//TSharedPtr<class FEKSceneFSM> sp_SceneFSM;

public:

	FEKProcedureBase(uint64 inID);
	virtual ~FEKProcedureBase();

	// The manager that manage this procedure.
	class FEKProcedureManager * m_EKProcedureMgr;

	// The unique ID for this procedure
	uint64 n_ID;

	float f_ElapsedTime;

	FDelegateHandle delegateHandle;

	// Call Init after construct
	virtual void Init();

	virtual void Tick(float inDeltaTime);

	// Call this when just change to this procedure
	virtual void Enter();

	virtual void Leave();

	// Call this to do post-load after UE4 map and GWorld has been loaded.
	//virtual void PostLoadMap(){};

	bool Register();

	// Get Finite State Machine of Scenes belong to this procedure.
	//TSharedPtr<class FEKSceneFSM> GetSceneFSM();
};


