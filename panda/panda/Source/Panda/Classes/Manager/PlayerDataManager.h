//
//  PlayerDataManager.h
//  Panda
//
//  Created by White.tian on 2016-05-23 10:08:44.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#ifndef __FPLAYERDATAMANAGER__
#define __FPLAYERDATAMANAGER__

#include "CCPlatformMacros.h"
#include "PAUserData.h"

#define PANDA_PlayerManager (FPlayerDataManager::Instance())


class FPlayerDataManager
{

	FPlayerDataManager();
	~FPlayerDataManager();
public:

	static FPlayerDataManager * Instance();
	static void purgedFPlayerDataManager();
private:

	bool Init();
	// Print Log?
	CC_SYNTHESIZE(bool, m_bLogPrint, LogPrint);
public:
	/*
	*	Player Data
	*	
	*	member: PlayerInfoData, like playerLevel, playerExp...
	*	member: PlaceInfoData,	like last_place_x_y_z
	*	member: PlayerExtraInfoData, like...
	*/

	///* Player Information, player base data, server data */
	//UPROPERTY(EditAnywhere, replicated)
	//FsPAPlayerInfo PlayerInfoData;
	//UPROPERTY(EditAnywhere, replicated)
	//FsPAPlaceInfo PlaceInfoData; 
	//UPROPERTY(EditAnywhere, replicated)
	//FsPAPlayerExtraInfo PlayerExtraInfoData;
	//
	//// PlayerData,  Get player Base Information
	//FsPAPlayerInfo GetPlayerInfo() { return PlayerInfoData; }
	//// SynchronyPlayerInfo. Set and Synchrony player information
	//void SetPlayerInfo(FsPAPlayerInfo PlayerInfo);

	CC_SYNTHESIZE(FsPAPlayerInfo, m_PlayerInfoData, PlayerInfo);

	//// PlayerPlaceData,  Get player Place Information
	//FsPAPlaceInfo GetPlaceInfo() { return PlaceInfoData; }
	//// SynchronyPlaceInfo. Set and Synchrony player placeInfo information
	//void SetPlaceInfo(FsPAPlaceInfo PlaceInfo);

	CC_SYNTHESIZE(FsPAPlaceInfo, m_PlaceInfoData, PlaceInfo);

	//// PlayerExtraData,  Get player Extra Information
	//FsPAPlayerExtraInfo GetPlayerExtraInfo() { return PlayerExtraInfoData; }
	//// SynchronyPlayerExtraInfo. Set and Synchrony player playerExtraInfo information
	//void SetPlayerExtraInfo(FsPAPlayerExtraInfo PlayerExtraInfo);

	CC_SYNTHESIZE(FsPAPlayerExtraInfo, m_PlayerExtraInfoData, PlayerExtraInfo);

	/* get and set player level */
	int32 getPlayerLevel();
	void setPlayerLevel(int32 nLevel);

	/* get and set Martialclub ID */
	int32 getMartialclubID();
	void setMartialclubID(int32 nID);

	/* get and set player exp */
	int32 getPlayerExp();
	void setPlayerExp(int32 nExp);

	/* get and set player energy */
	int32 getPlayerEnergy();
	void setPlayerEnergy(int32 nEnergy);
};

#endif /* defined(__FPlayerDataManager__) */