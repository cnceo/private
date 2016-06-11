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
	//����ԭ����չ���ݳ�ʼ��ԭ��
	virtual void InitByData(FsAtomExtendTable TableData);

	//����ԭ�Ӳ�������
	virtual void ResetAtom();

	//����һ��ԭ��
	virtual bool PlaySkillAtom(ABaseCharacter* pReviseTarget = nullptr);

	//���ԭ�Ӳ�������
	virtual bool CheckPlaySkillAtom();

	//����ԭ�Ӷ�Ӧ�Ľ�ɫ����
	virtual void SetAtomAnim();

	//���ӵ�иü���ԭ�ӵĽ�ɫ
	virtual ABaseCharacter* GetCharacter();

	//��ɫ����֪ͨ
	virtual void OnAnimBegin(float fTime, const FString& AnimName);

	//��ɫ����֪ͨ
	virtual bool OnAnimTick(float fTime, const FString& AnimName);

	//��ɫ����֪ͨ
	virtual void OnAnimEnd(const FString& AnimName);

	//����ԭ�ӻ�������
	void SetBaseTable(FsAtomBaseTable AtomData);

	ASkillIInstance* GetSkillIInstance();

public:
	//ԭ�ӻ�������
	FsAtomBaseTable m_sBaseAtomData;

	//ԭ����չ����
	FsAtomExtendTable m_sAtomExtendData;

	//ԭ�ӽ�ɫ������Դ
	FsResourcesTable m_sResources;

	//ԭ�Ӷ�Ӧ����̫�涯��(�붯�����л���)
	UAnimMontage* m_pAnimMontage;

	//ԭ�Ӷ�Ӧ�Ķ�������(����̫�滥��)
	UAnimSequence* m_pAnimSequence;

	//�Զ������Ƕ�������Ŀ��
	ABaseCharacter* m_pReviseTarget;

	//ԭ�Ӷ��Լ���Ӱ��
	FsAtomEffectTable m_sSelfEffectTable;

	//ԭ�Ӷ��ѷ���Ӱ��
	FsAtomEffectTable m_sFriendEffectTable;

	//ԭ�ӶԵ��˵�Ӱ��
	FsAtomEffectTable m_sEnemyEffectTable;

	//��ǰԭ�Ӷ�������ʱ��
	float m_fMaxTime;

	//��ǰԭ�Ӷ�����Tickʱ��
	float m_fCurTime;

	//��ǰ�˺��ж�����
	int32 m_CurHitCount;

	//�Ƿ�ɽ��������������ں�
	bool m_bNext;

	//���ںϺ󾭹���ʱ��
	float m_fFuseTime;

	//�Ƿ�����Զ�������һ��
	bool m_bNextCheck;

};
