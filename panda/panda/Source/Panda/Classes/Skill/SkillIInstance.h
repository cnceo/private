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

	//����ID��ʼ������ʵ��
	void InitByID(int32 nID);

	//���ӵ�иü��ܵĽ�ɫ
	ABaseCharacter* GetCharacter();

	//���ü�������.(�ڼ���ʹ�����ʱ����.)
	void ResetInstance();

	//�ͷż���
	bool PlaySkill();

	//��ýǶ��������ԭ���±�������Ŀ��
	int32 GetAngleReviseIndex(int32 arrIndex, AActor*& pOutTarget);

	//�жϼ���
	void BreakSkill(bool bChangeState = true);

	//֪ͨ������ͼ�ͷż���
	void OnAnimInstanceEvent();

	//��õ�ǰԭ�ӵ���̫��
	UAnimMontage* GetCurAtomMontage();

	//��õ�ǰԭ�ӵĶ�������
	UAnimSequence* GetCurAtomSequence();

	//���ý�ɫ���״̬����
	void ResetCharacterData(bool bChangeState = true);

	//��ɫ����֪ͨ
	void OnAnimBegin(float fTime, const FString& AnimName);

	//��ɫ����֪ͨ
	void OnAnimTick(float fTime, const FString& AnimName);

	//��ɫ����֪ͨ
	void OnAnimEnd(const FString& AnimName);

	//��ǰ���ŵ�ԭ�ӿɽ������������ں��¼�
	void OnBeFuseEvent();

	//������밴���Ƿ񴥷���������.���������±�
	int32 CheckPlayNextByInputKey(bool arrbPressedKey[PLAYER_KEY::PLAYER_KEY_MAX], PLAYER_KEY emCurKey);

	//���ż�������
	bool PlayNextSkill(int32 nNextIndex = 0);

	//�ܷ񴥷����з���
	bool IsBeCounterattack();

	//�Ƿ���Խ������������ں�
	bool IsBeFuse();

	//����ԭ�Ӳ��Ž����ӿ�
	void PlayAtomEnd();

public:
	//������
	FsSkillTable m_sTableData;


	//��ǰ�����е�ԭ�������±�
	int32 m_nCurArrIndex;

	//��ǰ�����е�ԭ���±�
	int32 m_nCurAtomIndex;

private:
	TArray< TArray<ASkillAtomBase*> > m_arrAtomInstance;
	
};

//��ɫMODE.��������
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