// Fill out your copyright notice in the Description page of Project Settings.
//add by yang 20160503
#pragma once

#include "Skill/SkillAtomBase.h"
#include "SkillAtomHit.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API ASkillAtomHit : public ASkillAtomBase
{
	GENERATED_BODY()
	
public:
	ASkillAtomHit();

	void InitByData(FsAtomExtendTable TableData);

	bool PlaySkillAtom(ABaseCharacter* pReviseTarget = nullptr);

	void ResetAtom();

	bool OnAnimTick(float fTime, const FString& AnimName);

public:

public:
	FsAtomHitTable m_TableData;
	
private:
	void CheckCollision(int32 nHitCount, TArray<FString> arrCollision);
	TMap<IActiveActorInterface*, FsSkillHitResult> m_mapTarget;
};
