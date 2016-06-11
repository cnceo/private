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
	// �������� ��ʱ����  ����������
	class FRace* Race = new FRace();
	Race->RaceName = TEXT("����");
	Race->RaceDescribe = TEXT("����һֻ��è");

	class FRaceSkill* RaceSkill = new FRaceSkill();
	RaceSkill->SkillName = TEXT("��èȭ");
	RaceSkill->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_001.Skill_Icon_001");
	Race->RaceSkillList.Add(RaceSkill);
	class FRaceSkill* RaceSkill1 = new FRaceSkill();
	RaceSkill1->SkillName = TEXT("��èȭ1");
	RaceSkill1->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_002.Skill_Icon_002");
	Race->RaceSkillList.Add(RaceSkill1);
	class FRaceSkill* RaceSkill2 = new FRaceSkill();
	RaceSkill2->SkillName = TEXT("��èȭ2");
	RaceSkill2->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_003.Skill_Icon_003");
	Race->RaceSkillList.Add(RaceSkill2);

	RaceDataList.Add(Race);

	class FRace* Race1 = new FRace();
	Race1->RaceName = TEXT("���Ŵ�");
	Race1->RaceDescribe = TEXT("����һ���Ŵ�");

	class FRaceSkill* nRaceSkill = new FRaceSkill();
	nRaceSkill->SkillName = TEXT("���Ŵ�ȭ");
	nRaceSkill->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_001.Skill_Icon_001");
	Race1->RaceSkillList.Add(nRaceSkill);

	class FRaceSkill* nRaceSkill1 = new FRaceSkill();
	nRaceSkill1->SkillName = TEXT("���Ŵ�ȭ1");
	nRaceSkill1->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_002.Skill_Icon_002");
	Race1->RaceSkillList.Add(nRaceSkill1);

	class FRaceSkill* nRaceSkill2 = new FRaceSkill();
	nRaceSkill2->SkillName = TEXT("���Ŵ�ȭ2");
	nRaceSkill2->SkillIocnPaht = TEXT("/Game/UI/Icon/Skill/Skill_Icon_003.Skill_Icon_003");
	Race1->RaceSkillList.Add(nRaceSkill2);

	RaceDataList.Add(Race1);
	//////////////////////////////////////////////////////////////////////////
	// ְҵ���� ��ʱ����  ����������
	class FProfession* Profession = new FProfession();
	Profession->ProfessionName = TEXT("���ʦ");

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
