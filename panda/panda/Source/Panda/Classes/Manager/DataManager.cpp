//
//  DataManager.h
//  demo003
//
//  Created by White.tian on 16-2-1.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#include "panda.h"
#include "DataManager.h"
#include "ResDefine.h"
#include "PandaUtils.h"

DataManager::DataManager()
{
	m_SampleStructLoadfromjsonfile.Reset();
	m_FsPAPlayerHeroBaseData.Reset();
	m_FsPAMonsterHeroBaseData.Reset();
	m_FsPAUserUpgradeBaseData.Reset();
	m_FsPANPCBaseData.Reset();

	m_FsPAChapterGroupData.Reset();
	m_FsPADungeonData.Reset();	m_StringTable.Reset();
	m_ResourcesTable.Reset();	m_AtomEffectTable.Reset();
	m_AtomHitTable.Reset();
	m_AtomChaseTable.Reset();
	m_AtomBulletTable.Reset();
	m_AtomBulletShapeTable.Reset();
	m_AtomExtendTable.Reset();
	m_SkillTable.Reset();

	// Task
	m_FsTaskInfo.Reset();
	m_FsMartialclubTable.Reset();
}

DataManager::~DataManager()
{

}

bool DataManager::Init()
{

	LoadAllData();
    return true;
}

void DataManager::LoadAllData()
{
	// sample
	ParseDatafromJson<FTestMyStruct>(MakeTablePath(FPaths::GameContentDir(), CONF_SampleTask), &m_SampleStructLoadfromjsonfile);
	// monster
	ParseDatafromJson<FsPAMonsterHeroBaseData>(MakeTablePath(FPaths::GameContentDir(), CONF_MONSTERHEROBASEDATA), &m_FsPAMonsterHeroBaseData);
	// player
	ParseDatafromJson<FsPAPlayerHeroBaseData>(MakeTablePath(FPaths::GameContentDir(), CONF_USERHEROBASEDATA), &m_FsPAPlayerHeroBaseData);
	// userUpgrade
	ParseDatafromJson<FsPAUserUpgradeBaseData>(MakeTablePath(FPaths::GameContentDir(), CONF_USERUPGRADEDATA), &m_FsPAUserUpgradeBaseData);
	// npcbase
	ParseDatafromJson<FsPANPCBaseData>(MakeTablePath(FPaths::GameContentDir(), CONF_NPCBASEDATA), &m_FsPANPCBaseData);
	// item
	ParseDatafromJson<FsPAItemData>(MakeTablePath(FPaths::GameContentDir(), CONF_ITEM), &m_fsPaItemData);
	// Task
	ParseDatafromJson<FsTaskInfo>(MakeTablePath(FPaths::GameContentDir(), CONF_TablePath_TaskInfo), &m_FsTaskInfo);
	// Martialclub
	ParseDatafromJson<FsMartialclubTable>(MakeTablePath(FPaths::GameContentDir(), CONF_MARTIALCLUB), &m_FsMartialclubTable);
	

	ParseDatafromJson<FsStringTable>(MakeTablePath(FPaths::GameContentDir(), CONF_STRINGTABLE), &m_StringTable);
	ParseDatafromJson<FsResourcesTable>(MakeTablePath(FPaths::GameContentDir(), CONF_RESOURCESTABLE), &m_ResourcesTable);

	ParseDatafromJson<FsAtomEffectTable>(MakeTablePath(FPaths::GameContentDir(), CONF_ATOMEFFECTTABLE), &m_AtomEffectTable);
	ParseDatafromJson<FsAtomExtendTable>(MakeTablePath(FPaths::GameContentDir(), CONF_ATOMEXTENDTABLE), &m_AtomExtendTable);
	ParseDatafromJson<FsAtomHitTable>(MakeTablePath(FPaths::GameContentDir(), CONF_ATOMHITTABLE), &m_AtomHitTable);
	ParseDatafromJson<FsAtomChaseTable>(MakeTablePath(FPaths::GameContentDir(), CONF_ATOMCHASETABLE), &m_AtomChaseTable);
	ParseDatafromJson<FsAtomBulletTable>(MakeTablePath(FPaths::GameContentDir(), CONF_ATOMBULLETTABLE), &m_AtomBulletTable);
	ParseDatafromJson<FsAtomBulletShapeTable>(MakeTablePath(FPaths::GameContentDir(), CONF_ATOMBULLETSHAPETABLE), &m_AtomBulletShapeTable);
	ParseDatafromJson<FsSkillTable>(MakeTablePath(FPaths::GameContentDir(), CONF_SKILLTTABLE), &m_SkillTable);

	// dungeon data etc at all...
	ParseDatafromJson<FsPADungeonCenterAreaData>(MakeTablePath(FPaths::GameContentDir(), CONF_CENTERAREADATA), &m_FsPADungeonCenterAreaData);
	ParseDatafromJson<FsPADungeonGroupData>(MakeTablePath(FPaths::GameContentDir(), CONF_CHAPTERDATA), &m_FsPAChapterGroupData);
	ParseDatafromJson<FsPADungeonData>(MakeTablePath(FPaths::GameContentDir(), CONF_STAGEDATA), &m_FsPADungeonData);
	ParseDatafromJson<FsPAStageLootRewardData>(MakeTablePath(FPaths::GameContentDir(), CONF_STAGELOOTREWARDDATA), &m_FsPAStageLootRewardData);
	ParseDatafromJson<FsPAStageMonsterPositionData>(MakeTablePath(FPaths::GameContentDir(), CONF_STAGEMONSTERPOSITIONDATA), &m_FsPAStageMonsterPositionData);
}

template<typename StructName>
void DataManager::ParseDatafromJson(FString filePath, TArray<StructName>* outArray)
{
	if (filePath.IsEmpty())
		return;

	FString FileContents;

	if (!FFileHelper::LoadFileToString(FileContents, *filePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to load OneSky credentials file %s."), *filePath);
		return;
	}

	//parse as JSON
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(FileContents);
	TSharedPtr<FJsonValue>  JsonValue;

	if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
	{
		
		StructName TempStruct;

		TArray<TSharedPtr<FJsonValue>> arr =  JsonValue->AsArray();
		
		for (TSharedPtr<FJsonValue> JsonValue : arr)
		{
			FJsonObjectConverter::JsonObjectToUStruct<StructName>(JsonValue->AsObject().ToSharedRef(), &TempStruct, 0, 0);
			outArray->Add(TempStruct);
		}

		//JSONObject->TryGetObjectField(TEXT("18"), obj);
		//FJsonObjectConverter::JsonObjectToUStruct<FTestMyStruct>(obj->ToSharedRef(), &testStruct, 0, 0);
		//bool b = FJsonObjectConverter::JsonObjectToUStruct<FTestMyStruct>(JSONObject, &testStruct, 0, 0);
		//bool b = FJsonObjectConverter::JsonArrayStringToUStruct(Reader->GetValueAsString(), &myStruct, 0, 0);


	//	return;
	}

}

template<typename TableStructName>
void DataManager::ParseDatafromJson(FString filePath, TMap<int32, TableStructName>* outMap)
{
	if (filePath.IsEmpty())
		return;

	FString FileContents;

	if (!FFileHelper::LoadFileToString(FileContents, *filePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to load OneSky credentials file %s."), *filePath);
		return;
	}

	//parse as JSON
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(FileContents);
	TSharedPtr<FJsonValue>  JsonValue;

	if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
	{

		TableStructName TempStruct;

		TArray<TSharedPtr<FJsonValue>> arr = JsonValue->AsArray();

		for (TSharedPtr<FJsonValue> JsonValue : arr)
		{
			FJsonObjectConverter::JsonObjectToUStruct<TableStructName>(JsonValue->AsObject().ToSharedRef(), &TempStruct, 0, 0);
			outMap->Add(TempStruct.nID, TempStruct);
		}
	}

}
const FsPAItemData* DataManager::getItemLocInfo(int id_)
{
	if (m_fsPaItemData.Find(id_))
	{
		return m_fsPaItemData.Find(id_);
	}

	return nullptr;
}

USkillFormula* DataManager::GetSkillFormula(FsResourcesTable sResources)
{
	auto FormulaBP = m_mapFormula.Find(sResources.strName);

	if (FormulaBP)
	{
		return *FormulaBP;
	}
	else
	{
		UBlueprintGeneratedClass* ParentClass = UPandaUtils::LoadResource<UBlueprintGeneratedClass>(sResources.strPath);
		if (ParentClass)
		{
			USkillFormula* pFormula = NewObject<USkillFormula>(ParentClass, ParentClass, FName(*sResources.strName), RF_MarkAsRootSet);
			m_mapFormula.Add(sResources.strName, pFormula);
			return pFormula;
		}
	}

	return nullptr;

}

USkillFormula* DataManager::GetSkillFormula(int32 nResourcesID)
{
	auto sResources = m_ResourcesTable.Find(nResourcesID);
	if (sResources)
	{
		return GetSkillFormula(*sResources);
	}
	return nullptr;
}
