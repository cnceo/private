// Fill out your copyright notice in the Description page of Project Settings.
//add by yang 20160503
#pragma once

#include "SkillAtomBase.h"
#include "GameFramework/Actor.h"
#include "SkillIInstance.generated.h"

UCLASS()
class PANDA_API ASkillIInstance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillIInstance();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:

	//根据ID初始化技能实例
	void InitByID(int32 nID);

	//获得拥有该技能的角色
	ABaseCharacter* GetCharacter();

	//重置技能数据.(在技能使用完毕时调用.)
	void ResetInstance();

	//释放技能
	bool PlaySkill();

	//获得角度修正后的原子下标索引及目标
	int32 GetAngleReviseIndex(int32 arrIndex, AActor*& pOutTarget);

	//中断技能
	void BreakSkill(bool bChangeState = true);

	//通知动画蓝图释放技能
	void OnAnimInstanceEvent();

	//获得当前原子的蒙太奇
	UAnimMontage* GetCurAtomMontage();

	//获得当前原子的动画序列
	UAnimSequence* GetCurAtomSequence();

	//重置角色相关状态数据
	void ResetCharacterData(bool bChangeState = true);

	//角色动画通知
	void OnAnimBegin(float fTime, const FString& AnimName);

	//角色动画通知
	void OnAnimTick(float fTime, const FString& AnimName);

	//角色动画通知
	void OnAnimEnd(const FString& AnimName);

	//当前播放的原子可进行其他动作融合事件
	void OnBeFuseEvent();

	//检测输入按键是否触发技能连招.返回连招下标
	int32 CheckPlayNextByInputKey(bool arrbPressedKey[PLAYER_KEY::PLAYER_KEY_MAX], PLAYER_KEY emCurKey);

	//播放技能连招
	bool PlayNextSkill(int32 nNextIndex = 0);

	//能否触发架招反击
	bool IsBeCounterattack();

	//是否可以进行其他动作融合
	bool IsBeFuse();

	//技能原子播放结束接口
	void PlayAtomEnd();

public:
	//表数据
	FsSkillTable m_sTableData;


	//当前播放中的原子数组下标
	int32 m_nCurArrIndex;

	//当前播放中的原子下标
	int32 m_nCurAtomIndex;

private:
	TArray< TArray<ASkillAtomBase*> > m_arrAtomInstance;
	
};

//角色MODE.配表参照用
//enum EMovementMode
//{
//	MOVE_None = 0	,
//	MOVE_Walking = 1,
//	MOVE_NavWalking = 2,
//	MOVE_Falling = 3,
//	MOVE_Swimming = 4,
//	MOVE_Flying = 5,
//	MOVE_Custom = 6,
//	MOVE_MAX,
//};