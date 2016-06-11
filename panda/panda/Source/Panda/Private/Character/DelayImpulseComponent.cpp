// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "DelayImpulseComponent.h"


// Sets default values for this component's properties
UDelayImpulseComponent::UDelayImpulseComponent()
	: m_pCharacter(nullptr)
	, m_vDirection(FVector::ZeroVector)
	, m_nForce(0)
	, m_emSubState(CHARACTER_SUB_STATE::SUB_STATE_NONE)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDelayImpulseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDelayImpulseComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UDelayImpulseComponent::CelarDelayData()
{
	m_pCharacter = nullptr;
	m_vDirection = FVector::ZeroVector;
	m_nForce = 0;
	m_emSubState = CHARACTER_SUB_STATE::SUB_STATE_NONE;
}

void UDelayImpulseComponent::DelayImpulse(ABaseCharacter* pCharacter, float fDelayTime, FVector vDirection, int32 nForce, CHARACTER_SUB_STATE emSubState)
{
	m_pCharacter = pCharacter;
	m_vDirection = vDirection;
	m_nForce = nForce;
	m_emSubState = emSubState;
	if (m_pCharacter)
	{
		FTimerDelegate ImpulseDelegate;
		ImpulseDelegate.BindUObject(this, &UDelayImpulseComponent::DelayImpulseCallback);
		GetWorld()->GetTimerManager().SetTimer(m_DelayImpulseHandle, ImpulseDelegate, fDelayTime, false);
	}
}

void UDelayImpulseComponent::DelayImpulseCallback()
{
	if (!m_pCharacter || m_pCharacter->GetSubState() != m_emSubState) 
		return;
	
	FRotationMatrix CauserMatrix(m_pCharacter->GetActorRotation());
	FVector Impulse = FVector(CauserMatrix.TransformVector(m_vDirection)).GetSafeNormal() * m_nForce;
	m_pCharacter->GetCharacterMovement()->AddImpulse(Impulse, true);

	CelarDelayData();
}