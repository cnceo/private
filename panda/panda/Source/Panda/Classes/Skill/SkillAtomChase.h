// Fill out your copyright notice in the Description page of Project Settings.
//add by yang 20160503
#pragma once

#include "Skill/SkillAtomBase.h"
#include "SkillAtomChase.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API ASkillAtomChase : public ASkillAtomBase
{
	GENERATED_BODY()
public:
	ASkillAtomChase();

	void InitByData(FsAtomExtendTable TableData);

	bool PlaySkillAtom(ABaseCharacter* pReviseTarget = nullptr);

	void ResetAtom();

	bool OnAnimTick(float fTime, const FString& AnimName);

	void OnFlyCallBack();

public:
	FsAtomChaseTable m_TableData;

private:

	//追击的目标
	ABaseCharacter* m_pTarget;

	//目标胶囊半径
	int32 m_nRadius;
	
	//是否完成追击
	bool m_bFinish;
	
	//浮空timer句柄
	FTimerHandle m_FlyHandle;
	
};
