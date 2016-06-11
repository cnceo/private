/** 
 * 场景管理器
 * 场景切换说明：
 * 1. 在游戏继承EKGameInstance的类里面的InitGameProcedure里进行所有流程与场景的初始化
 *    以及设置第一个Procedure和Scene.
 * 2. 切换地图函数：void ChangeMap(EKType::Scene inSceneType, bool isLoadMap);
 * 3. 地图读取完成后动态加载资源位置：每个SceneBase类中的PostLoadMap方法.
 */    

#pragma once

#include "Object.h"
#include "EKProcedureBase.h"

class EASYKIT_API FEKProcedureManager 
{
public:

	FEKProcedureManager();
	~FEKProcedureManager();

	// The hashtable that reference all procedures.
	TMap<uint64, TSharedPtr<class FEKProcedureBase>> c_ProcedureMap;

	bool Init();

	void Tick(float inDeltaTime);

	void SetWorld(UWorld* inWorld){ world = inWorld; };
	UWorld* GetWorld(){ return world; };

	TSharedPtr<class FEKProcedureBase> GetCurrentProcedure() { return sp_CurrentProcedure; }

	void RegisterProcedure(TSharedPtr<class FEKProcedureBase> InProcedure);

	/**
	* Set current Procedure to the Procedure Manager.
	*
	* @param	inProcID		The unique ID of the procedure.
	*/
	bool SetCurrentProcedure(uint64 inProcID);

	/**
	* Change current Procedure to the Procedure Manager.
	*
	* @param	inProcID		The unique ID of the procedure.
	*/
	bool ChangeCurrentProcedure(uint64 inProcID);

private:

	// Current working Procedure. 
	TSharedPtr<class FEKProcedureBase> sp_CurrentProcedure;

	UWorld* world;
};