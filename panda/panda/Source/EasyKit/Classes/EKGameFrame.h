//
// EGameFrame.h
//
// ��Ϸͨ�üܹ��� ��Ϸ�߼������
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "EKProcedureBase.h"
#include "EKSceneManager.h"
#include "EKResourceManager.h"
#include "EKProcedureManager.h"


/**
*  GameFrameΪEasyKit�ܹ������
*/
class EASYKIT_API FEKGameFrame 
{

	~FEKGameFrame();
	static FEKGameFrame* g_pEKGameFrame;

public:

	static FEKGameFrame* Instance();

	// ���̹�����
	
	class FEKProcedureManager* ProcedureManager();
	
	class FEKSceneManager* SceneManager();
	
	class UEKResourceManager* ResourceManager();
	
	class FEKNetWorkManager* NetWorkManager();
	
	class FEKHUDManager* HUDManager();

	void Tick(float DeltaSeconds, bool bIdleMode);

private:
	FEKGameFrame();

	class FEKProcedureManager* m_pProceduerMgr;
	class FEKSceneManager* m_pSceneMgr;
	class UEKResourceManager* m_pResourMgr;
	class FEKNetWorkManager* m_pNetWorkMgr;
	class FEKHUDManager* m_pHUDMgr;
};

