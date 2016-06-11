//
//  DataManager.h
//  demo003
//
//  Created by White.tian on 16-2-1.
//  Copyright (c) 2016年 White.tian All rights reserved.
//
//  Modify by ZP
//  Do not new this class Anywhere  find it in GameInstance
#ifndef __DATAMANAGER__
#define __DATAMANAGER__


#include "Json.h"
#include "PASkillData.h"
#include "PANPCBaseData.h"
#include "PAUserUpgradeBaseData.h"
#include "PAMonsterHeroBaseData.h"
#include "PAUserHeroBaseData.h"
#include "PADungeonData.h"
#include "pAItemData.h"
#include "SkillFormula.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

struct FTestMyStruct;
struct FLocResItem;

class DataManager/* : public FPlatformFileManager*/
{    
public:   
    DataManager();
    ~DataManager();
	// Init Data
    bool Init();
	// Load Data
	void LoadAllData();

public:
	const FsPAItemData* getItemLocInfo(int id);
public:
	/*
	*
	*/
	TArray<FTestMyStruct>						m_SampleStructLoadfromjsonfile;
	TMap<int32, FsPAPlayerHeroBaseData>			m_FsPAPlayerHeroBaseData;			// player hero
	TMap<int32, FsPAMonsterHeroBaseData>		m_FsPAMonsterHeroBaseData;			// monster hero
	TMap<int32, FsPAUserUpgradeBaseData>		m_FsPAUserUpgradeBaseData;			// user upgrade
	TMap<int32, FsPANPCBaseData>				m_FsPANPCBaseData;					// npc base

	TMap<int32, FsPADungeonCenterAreaData>		m_FsPADungeonCenterAreaData;		// dungeon_center_area
	TMap<int32, FsPADungeonGroupData>			m_FsPAChapterGroupData;				// dungeon_chapter
	TMap<int32, FsPADungeonData>				m_FsPADungeonData;					// dungeon_stage
	TMap<int32, FsPAStageLootRewardData>		m_FsPAStageLootRewardData;			// dungeon_loot reward
	TMap<int32, FsPAStageMonsterPositionData>	m_FsPAStageMonsterPositionData;		// dungeon_monster postion

	TMap<int32, FsPAItemData>					m_fsPaItemData;						// item data
	TMap<int32, FsTaskInfo>						m_FsTaskInfo;						// Task data
	TMap<int32, FsMartialclubTable>				m_FsMartialclubTable;				// Martialclub data

	TMap<int32, FsStringTable>					m_StringTable; 
	TMap<int32, FsResourcesTable>				m_ResourcesTable;
	TMap<int32, FsAtomEffectTable>				m_AtomEffectTable;
	TMap<int32, FsAtomHitTable>				m_AtomHitTable;
	TMap<int32, FsAtomChaseTable>				m_AtomChaseTable;
	TMap<int32, FsAtomBulletTable>				m_AtomBulletTable;
	TMap<int32, FsAtomBulletShapeTable>			m_AtomBulletShapeTable;
	TMap<int32, FsAtomExtendTable>				m_AtomExtendTable;
	TMap<int32, FsSkillTable>					m_SkillTable;

public:
	template<typename StructName>
	static void ParseDatafromJson(FString filePath, TArray<StructName>* outArray);
	template<typename TableStructName>
	static void ParseDatafromJson(FString filePath, TMap<int32, TableStructName>* outMap);

	USkillFormula* GetSkillFormula(FsResourcesTable sResources);
	USkillFormula* GetSkillFormula(int32 nResourcesID);
private:
	TMap<FString, USkillFormula*>				m_mapFormula;

};


#endif /* defined(__DATAMANAGER__) */
