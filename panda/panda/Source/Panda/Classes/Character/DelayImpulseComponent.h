// Fill out your copyright notice in the Description page of Project Settings.
//add by yang
#pragma once
#include "CommonDefine.h"
#include "Components/ActorComponent.h"
#include "DelayImpulseComponent.generated.h"

class ABaseCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PANDA_API UDelayImpulseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDelayImpulseComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void DelayImpulse(ABaseCharacter* pCharacter, float fDelayTime, FVector vDirection, int32 nForce, CHARACTER_SUB_STATE emSubState = CHARACTER_SUB_STATE::SUB_STATE_NONE);

	virtual void CelarDelayData();

protected:

	void DelayImpulseCallback();

	//�ӳ�������Handle
	FTimerHandle m_DelayImpulseHandle;

	//�ӳ������Ľ�ɫ
	ABaseCharacter* m_pCharacter;

	//���ķ���
	FVector m_vDirection;

	//����ǿ��
	int32 m_nForce;

	//״̬
	CHARACTER_SUB_STATE m_emSubState;

};
