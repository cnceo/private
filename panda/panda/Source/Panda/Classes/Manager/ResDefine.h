//
//  DataManager.h
//  demo003
//
//  Created by White.tian on 16-2-2.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#ifndef __APPRESDEFINE__
#define __APPRESDEFINE__

//#pragma mark - ===============================================================
//#pragma mark - ============================conf加载============================
//#pragma mark - ===============================================================

#define  MakeTablePath(ContentDir,TablePath)  FString((ContentDir) + (TablePath))

#define CONF_STRINGTABLE "Conf/StringTable.json"
#define CONF_RESOURCESTABLE "Conf/ResourcesTable.json"
#define CONF_SampleTask "Conf/task1.json"
#define CONF_MONSTERHEROBASEDATA "Conf/MonsterHeroBaseData.json"
#define CONF_USERHEROBASEDATA "Conf/UserHeroBaseData.json"
#define CONF_USERUPGRADEDATA "Conf/UserUpgrade.json"
#define CONF_NPCBASEDATA "Conf/NpcBaseData.json"
#define CONF_ATOMEFFECTTABLE "Conf/AtomEffectTable.json"
#define CONF_ATOMEXTENDTABLE "Conf/AtomExtendTable.json"
#define CONF_ATOMHITTABLE "Conf/AtomHitTable.json"
#define CONF_ATOMCHASETABLE "Conf/AtomChaseTable.json"
#define CONF_ATOMBULLETTABLE "Conf/AtomBulletTable.json"
#define CONF_ATOMBULLETSHAPETABLE "Conf/AtomBulletShapeTable.json"
#define CONF_SKILLTTABLE "Conf/SkillTable.json"
#define CONF_ITEM "Conf/item.json"
#define CONF_MARTIALCLUB "Conf/Martialclub.json"

#define CONF_CENTERAREADATA "Conf/centerArea.json"
#define CONF_CHAPTERDATA "Conf/dungeon_group.json"
#define CONF_STAGEDATA "Conf/dungeon.json"
#define CONF_STAGELOOTREWARDDATA "Conf/dungeon_collect.json"
#define CONF_STAGEMONSTERPOSITIONDATA "Conf/dungeon_monster.json"

#define CONF_TablePath_TaskInfo	"Conf/TaskData.json"


/* UI DEFINE */
#define UI_CREATE_TEAM TEXT("/Game/UI/UMG/Team/CreateTeam.CreateTeam_C")
#define UI_Dungeon_ACT TEXT("/Game/UI/UMG/Dungeon/ACT.ACT_C")
#define UI_Dungeon_SelectRegion TEXT("/Game/UI/UMG/Dungeon/SelectRegion.SelectRegion_C")

#endif /*__APPRESDEFINE__*/