
#include "EasyKit.h"
#include "EKGameFrame.h"
#include "EKNetWorkManager.h"



//IMPLEMENT_CLASS(FEKGameFrame)

FEKGameFrame* FEKGameFrame::g_pEKGameFrame = nullptr;

FEKGameFrame::FEKGameFrame() :
m_pProceduerMgr(nullptr),
m_pSceneMgr(nullptr),
m_pResourMgr(nullptr),
m_pNetWorkMgr(nullptr),
m_pHUDMgr(nullptr)
{

}


FEKGameFrame::~FEKGameFrame()
{
	if (g_pEKGameFrame)
	{
		delete g_pEKGameFrame;
		g_pEKGameFrame = nullptr;
	}
}

FEKGameFrame* FEKGameFrame::Instance()
{
	if (g_pEKGameFrame == NULL)
	{

		g_pEKGameFrame = new FEKGameFrame();
		UE_LOG(LogScript, Warning, TEXT(" !!!! Welcome Come To AEasyKit GameFrame !!!!  [Start]  "));
	}

	return g_pEKGameFrame;
}

FEKProcedureManager* FEKGameFrame::ProcedureManager()
{
	if (m_pProceduerMgr == NULL)
	{
		m_pProceduerMgr = new FEKProcedureManager();
	}

	return m_pProceduerMgr;
}

FEKSceneManager* FEKGameFrame::SceneManager()
{
	if (m_pSceneMgr == NULL)
	{
		m_pSceneMgr = new FEKSceneManager();
	}

	return m_pSceneMgr;
}

UEKResourceManager* FEKGameFrame::ResourceManager()
{
	if (m_pResourMgr == nullptr)
	{
		m_pResourMgr = ConstructObject<UEKResourceManager>(UEKResourceManager::StaticClass());
	}

	return m_pResourMgr;
}

FEKNetWorkManager* FEKGameFrame::NetWorkManager()
{
	if (m_pNetWorkMgr == NULL)
	{
		m_pNetWorkMgr = new FEKNetWorkManager();
	}

	return m_pNetWorkMgr;
}

FEKHUDManager* FEKGameFrame::HUDManager()
{
	if (m_pHUDMgr == NULL)
	{
		m_pHUDMgr = new FEKHUDManager();
	}

	return m_pHUDMgr;
}

void FEKGameFrame::Tick(float DeltaSeconds, bool bIdleMode)
{
	if (m_pSceneMgr)
		m_pSceneMgr->Tick(DeltaSeconds);

	//if (m_pNetWorkMgr)
	//	m_pNetWorkMgr->Tick(DeltaSeconds);

	if (m_pProceduerMgr)
		m_pProceduerMgr->Tick(DeltaSeconds);
}

