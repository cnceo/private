
#include "EasyKit.h"
#include "EKProcedureBase.h"
#include "EKProcedureManager.h"


FEKProcedureManager::FEKProcedureManager() :
sp_CurrentProcedure(nullptr)
{

}

FEKProcedureManager::~FEKProcedureManager()
{
}

bool FEKProcedureManager::Init()
{
	UE_LOG(LogScript, Warning, TEXT(" !!!! UEasyKit FEKProcedureManager Init Finish !!!!  "));

	return true;
}

void FEKProcedureManager::Tick(float inDeltaTime)
{
	if (sp_CurrentProcedure.IsValid())
		sp_CurrentProcedure->Tick(inDeltaTime);
}

void FEKProcedureManager::RegisterProcedure(TSharedPtr<class FEKProcedureBase> InProcedure)
{
	if (InProcedure.IsValid())
		c_ProcedureMap.Add(InProcedure->n_ID, InProcedure);
}

bool FEKProcedureManager::SetCurrentProcedure(uint64 inProcID)
{
	if (!c_ProcedureMap.Contains(inProcID)) return false;
	TSharedPtr<class FEKProcedureBase> newProcedure = c_ProcedureMap[inProcID];
	if (!newProcedure.IsValid()) return false;

	sp_CurrentProcedure = newProcedure;
	sp_CurrentProcedure->Enter();

	return true;
}

bool FEKProcedureManager::ChangeCurrentProcedure(uint64 inProcID)
{
	if (!sp_CurrentProcedure.IsValid()) return false;

	if (inProcID == sp_CurrentProcedure->n_ID) return false;

	if (!c_ProcedureMap.Contains(inProcID)) return false;
	TSharedPtr<class FEKProcedureBase> newProcedure = c_ProcedureMap[inProcID];
	if (!newProcedure.IsValid()) return false;

	sp_CurrentProcedure->Leave();
	sp_CurrentProcedure = newProcedure;
	sp_CurrentProcedure->Enter();
	
	return true;
}