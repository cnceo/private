/** 
 * ����������
 * �����л�˵����
 * 1. ����Ϸ�̳�EKGameInstance���������InitGameProcedure��������������볡���ĳ�ʼ��
 *    �Լ����õ�һ��Procedure��Scene.
 * 2. �л���ͼ������void ChangeMap(EKType::Scene inSceneType, bool isLoadMap);
 * 3. ��ͼ��ȡ��ɺ�̬������Դλ�ã�ÿ��SceneBase���е�PostLoadMap����.
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