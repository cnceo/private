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

	//延迟受力的Handle
	FTimerHandle m_DelayImpulseHandle;

	//延迟受力的角色
	ABaseCharacter* m_pCharacter;

	//力的方向
	FVector m_vDirection;

	//力的强度
	int32 m_nForce;

	//状态
	CHARACTER_SUB_STATE m_emSubState;

};
