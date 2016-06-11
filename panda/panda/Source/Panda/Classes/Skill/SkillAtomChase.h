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

	//׷����Ŀ��
	ABaseCharacter* m_pTarget;

	//Ŀ�꽺�Ұ뾶
	int32 m_nRadius;
	
	//�Ƿ����׷��
	bool m_bFinish;
	
	//����timer���
	FTimerHandle m_FlyHandle;
	
};
