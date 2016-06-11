// Copyright 1998-2014 xishanju Games, Inc. All Rights Reserved.

#include "panda.h"
#include "GameData.h"
#include "EKHUDManager.h"
#include "SelectCharacterTableData.h"
#include "SelectCharacterBase.h"
#include "SelectCharPC.h"



FSelectCharacterTableData::FSelectCharacterTableData()
{

};

void FSelectCharacterTableData::Init()
{
	//////////////////////////////////////////////////////////////////////////
	// 种族数据 临时测试  请填充表数据
	class FRace* Race = new FRace();
	Race->RaceName = TEXT("阿宝");
	Race->RaceDescribe = TEXT("我是一只熊猫");

	class FRaceSkill* RaceSkill = new FRaceSkill();
	RaceSkill->SkillName = TEXT("熊猫拳");
	RaceSkill->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_001.Skill_Icon_001");
	Race->RaceSkillList.Add(RaceSkill);
	class FRaceSkill* RaceSkill1 = new FRaceSkill();
	RaceSkill1->SkillName = TEXT("熊猫拳1");
	RaceSkill1->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_002.Skill_Icon_002");
	Race->RaceSkillList.Add(RaceSkill1);
	class FRaceSkill* RaceSkill2 = new FRaceSkill();
	RaceSkill2->SkillName = TEXT("熊猫拳2");
	RaceSkill2->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_003.Skill_Icon_003");
	Race->RaceSkillList.Add(RaceSkill2);

	RaceDataList.Add(Race);

	class FRace* Race1 = new FRace();
	Race1->RaceName = TEXT("阿古达");
	Race1->RaceDescribe = TEXT("我是一阿古达");

	class FRaceSkill* nRaceSkill = new FRaceSkill();
	nRaceSkill->SkillName = TEXT("阿古达拳");
	nRaceSkill->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_001.Skill_Icon_001");
	Race1->RaceSkillList.Add(nRaceSkill);

	class FRaceSkill* nRaceSkill1 = new FRaceSkill();
	nRaceSkill1->SkillName = TEXT("阿古达拳1");
	nRaceSkill1->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_002.Skill_Icon_002");
	Race1->RaceSkillList.Add(nRaceSkill1);

	class FRaceSkill* nRaceSkill2 = new FRaceSkill();
	nRaceSkill2->SkillName = TEXT("阿古达拳2");
	nRaceSkill2->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_003.Skill_Icon_003");
	Race1->RaceSkillList.Add(nRaceSkill2);

	RaceDataList.Add(Race1);
	//////////////////////////////////////////////////////////////////////////
	// 职业数据 临时测试  请填充表数据
	class FProfession* Profession = new FProfession();
	Profession->ProfessionName = TEXT("喷火师");

	ProfessionDataList.Add(Profession);
}

void FSelectCharacterTableData::Serialize()
{

}

TArray<class FProfession*>& FSelectCharacterTableData::GetProfessionDataList()
{
	return ProfessionDataList;
}

TArray<class FRace*>& FSelectCharacterTableData::GetRaceDataList()
{
	return RaceDataList;
}
