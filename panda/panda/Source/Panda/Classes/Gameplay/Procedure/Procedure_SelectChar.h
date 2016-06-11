// Copyright 1995-2016. All Rights Reserved.
// Created by Òü¿¡Ðñ 

/*=============================================================================
The game login procedure
=============================================================================*/

#pragma once

#include <atomic> 
#include "EKProcedureBase.h"

extern std::atomic<bool> isAsyncLoadingFinish;

class PANDA_API FProcedure_SelectChar : public FEKProcedureBase
{
public:

	FProcedure_SelectChar(uint64 inID);
	virtual ~FProcedure_SelectChar(){};

	virtual void Init();

	virtual void Tick(float inDeltaTime);

	virtual void Enter();

	// Call this to do pre-load func before map change.
	void PreLoadMap();

	// Call this to do post-load after UE4 map and GWorld has been loaded.
	void PostLoadMap();

	virtual void Leave();

private:
	bool isSendLogin;

};


