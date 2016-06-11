// Copyright 1995-2016. All Rights Reserved.
// Created by Òü¿¡Ðñ on 05,04,2016

/*=============================================================================
The game scene procedure
=============================================================================*/

#pragma once

#include <atomic> 
#include "EKProcedureBase.h"

class PANDA_API FProcedure_Scene : public FEKProcedureBase
{
public:

	FProcedure_Scene(uint64 inID);
	virtual ~FProcedure_Scene(){};

	virtual void Init();

	virtual void Tick(float inDeltaTime);

	virtual void Enter();

	// Call this to do pre-load func before map change.
	void PreLoadMap();

	// Call this to do post-load after UE4 map and GWorld has been loaded.
	void PostLoadMap();

	virtual void Leave();

	//class AElementLandscape* GetLandscape();

private:

	//class AElementLandscape* mLandscape;

	//void InitLandscape();

};


