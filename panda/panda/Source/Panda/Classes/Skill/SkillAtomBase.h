// Fill out your copyright notice in the Description page of Project Settings.
//add by yang 20160503
#pragma once

#include "GameFramework/Actor.h"
#include "SkillAtomBase.generated.h"

UCLASS()
class PANDA_API ASkillAtomBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillAtomBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:
	//根据原子扩展数据初始化原子
	virtual void InitByData(FsAtomExtendTable TableData);

	//重置原子播放数据
	virtual void ResetAtom();

	//播放一个原子
	virtual bool PlaySkillAtom(ABaseCharacter* pReviseTarget = nullptr);

	//检测原子播放条件
	virtual bool CheckPlaySkillAtom();

	//设置原子对应的角色动画
	virtual void SetAtomAnim();

	//获得拥有该技能原子的角色
	virtual ABaseCharacter* GetCharacter();

	//角色动画通知
	virtual void OnAnimBegin(float fTime, const FString& AnimName);

	//角色动画通知
	virtual bool OnAnimTick(float fTime, const FString& AnimName);

	//角色动画通知
	virtual void OnAnimEnd(const FString& AnimName);

	//设置原子基础数据
	void SetBaseTable(FsAtomBaseTable AtomData);

	ASkillIInstance* GetSkillIInstance();

public:
	//原子基础数据
	FsAtomBaseTable m_sBaseAtomData;

	//原子扩展数据
	FsAtomExtendTable m_sAtomExtendData;

	//原子角色动画资源
	FsResourcesTable m_sResources;

	//原子对应的蒙太奇动画(与动画序列互斥)
	UAnimMontage* m_pAnimMontage;

	//原子对应的动画序列(与蒙太奇互斥)
	UAnimSequence* m_pAnimSequence;

	//自动调整角度锁定的目标
	ABaseCharacter* m_pReviseTarget;

	//原子对自己的影响
	FsAtomEffectTable m_sSelfEffectTable;

	//原子对友方的影响
	FsAtomEffectTable m_sFriendEffectTable;

	//原子对敌人的影响
	FsAtomEffectTable m_sEnemyEffectTable;

	//当前原子动作的总时间
	float m_fMaxTime;

	//当前原子动作的Tick时间
	float m_fCurTime;

	//当前伤害判定计数
	int32 m_CurHitCount;

	//是否可进行其他动作的融合
	bool m_bNext;

	//可融合后经过的时间
	float m_fFuseTime;

	//是否检测过自动连接下一招
	bool m_bNextCheck;

};
