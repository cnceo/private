#include "panda.h"
#include "PlayerDataManager.h"
#include <string>
#include <stdio.h>

static FPlayerDataManager *s_pSharedFPlayerDataManager = NULL;

FPlayerDataManager::FPlayerDataManager()
	: m_bLogPrint(true)
{

}

FPlayerDataManager::~FPlayerDataManager()
{

}

bool FPlayerDataManager::Init()
{
	setLogPrint(true);

	return true;
}

FPlayerDataManager * FPlayerDataManager::Instance()
{
	if (!s_pSharedFPlayerDataManager)
	{
		s_pSharedFPlayerDataManager = new FPlayerDataManager();
		s_pSharedFPlayerDataManager->Init();
	}

	return s_pSharedFPlayerDataManager;
}

void FPlayerDataManager::purgedFPlayerDataManager()
{
	//CC_SAFE_RELEASE_NULL(s_pSharedFPlayerDataManager);
}

int32 FPlayerDataManager::getPlayerLevel()
{
	return m_PlayerInfoData.level;
}

void FPlayerDataManager::setPlayerLevel(int32 nLevel)
{
	m_PlayerInfoData.level = nLevel;
}

/* get and set Martialclub ID */
int32 FPlayerDataManager::getMartialclubID()
{
	return m_PlayerInfoData.MartialclubID;
}

void FPlayerDataManager::setMartialclubID(int32 nID)
{
	m_PlayerInfoData.MartialclubID = nID;
}

int32 FPlayerDataManager::getPlayerExp()
{
	return m_PlayerInfoData.exp;
}

void FPlayerDataManager::setPlayerExp(int32 nExp)
{
	m_PlayerInfoData.exp = nExp;
}

int32 FPlayerDataManager::getPlayerEnergy()
{
	return m_PlayerInfoData.energy;
}

void FPlayerDataManager::setPlayerEnergy(int32 nEnergy)
{
	m_PlayerInfoData.energy = nEnergy;
}