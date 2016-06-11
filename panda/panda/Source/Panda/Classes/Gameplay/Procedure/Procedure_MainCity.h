// Copyright 1995-2016. All Rights Reserved.
// 
//  Copy From Òü¿¡Ðñ's same code.
//  Procedure_CenterArea.h
//  Panda
//  The Game MainCity Procedure.
//  Created by White.tian on 2016-05-21 10:46:05
//  Copyright (c) 2016Äê White.tian All rights reserved.
//

#pragma once

#include <atomic> 
#include "EKProcedureBase.h"

extern std::atomic<bool> isAsyncLoadingFinish;

class PANDA_API FProcedure_MainCity : public FEKProcedureBase
{
public:

	FProcedure_MainCity(uint64 inID);
	virtual ~FProcedure_MainCity(){};

	virtual void Init();

	virtual void Tick(float inDeltaTime);

	virtual void Enter();

	// Call this to do pre-load func before map change.
	void PreLoadMap();

	// Call this to do post-load after UE4 map and GWorld has been loaded.
	void PostLoadMap();

	virtual void Leave();

//private:
//	bool isSendLogin;

};