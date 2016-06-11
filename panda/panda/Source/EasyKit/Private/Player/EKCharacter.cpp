// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AEKCharacter

//FName AEKCharacter::fnRWeapon(TEXT("RightWeaponComponent"));
//FName AEKCharacter::fnLWeapon(TEXT("LeftWeaponComponent"));

AEKCharacter::AEKCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, fsName("EKPlayer")
	, mPlayerState(NULL)
{
	bIsUpdateTick = true;
	//bIsTestMove = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Note: The skeletal mesh and anim blueprint references on the GetMesh() component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//usmRWeaponComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, AEKCharacter::fnRWeapon);
	//if (usmRWeaponComponent)
	//{
	//	usmRWeaponComponent->AttachTo(GetMesh());
	//}

	//usmLWeaponComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, AEKCharacter::fnLWeapon);
	//if (usmLWeaponComponent)
	//{
	//	usmLWeaponComponent->AttachTo(GetMesh());
	//}

	Health = 1000;
	MaxHealth = 1000;

	bOpenMap = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEKCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{

}

/************************************************************************/
/* Change Meshes                                                        */
/************************************************************************/
bool AEKCharacter::ChangeMeshesByID(int nID)
{
	if (ChangeBodyMeshByID(nID) && 
		ChangeAnimBPByID(nID) &&
		ChangeRWeaponMeshByID(nID) &&
		ChangeLWeaponMeshByID(nID))
	{
		return true;
	}
	return false;
}

/************************************************************************/
/* Change Body Skeleton GetMesh()                                            */
/************************************************************************/
bool AEKCharacter::ChangeBodyMeshByID(int InID)
{
	return true;
}

/************************************************************************/
/* Change Body AnimBP                                          */
/************************************************************************/
bool AEKCharacter::ChangeAnimBPByID(int InID)
{
	return true;
}

/************************************************************************/
/* Change Right Weapon Static GetMesh()                                      */
/************************************************************************/
bool AEKCharacter::ChangeRWeaponMeshByID(int nRWID)
{
	return true;
}

/************************************************************************/
/* Change Left Weapon Static GetMesh()                                      */
/************************************************************************/
bool AEKCharacter::ChangeLWeaponMeshByID(int nLWID)
{
	return true;
}

bool AEKCharacter::IsFirstPerson() const
{
	return true;
}

bool AEKCharacter::IsAlive() const
{
	return true;
}

void AEKCharacter::EventPhysicsHit_Implementation(FName inBoneName, FVector ImpactNormal, FVector inHitLoaction) 
{

};

void AEKCharacter::PlayAnimAsset(class UAnimationAsset* AnimMontage, bool isLoop /*= false*/)
{
	if (AnimMontage && GetMesh())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		UAnimSingleNodeInstance* SingleNodeInstance = GetMesh()->GetSingleNodeInstance();
		if (SingleNodeInstance)
		{
			SingleNodeInstance->SetPosition(0.f);
		}
		GetMesh()->SetAnimation(AnimMontage);
		GetMesh()->Play(isLoop);
	}
}

void AEKCharacter::StopAnimMontage(class UAnimMontage* AnimMontage)
{
	USkeletalMeshComponent* UseMesh = GetPawnMesh();

	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0);
	}
}

void AEKCharacter::StopAllAnimMontages()
{
	USkeletalMeshComponent* UseMesh = GetPawnMesh();
	if (UseMesh && UseMesh->AnimScriptInstance)
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
	}
}

void AEKCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

int32 AEKCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AEKCharacter>()->MaxHealth;
}

void AEKCharacter::Tick(float DeltaSeconds)
{
	if (bIsUpdateTick) 
		Super::Tick(DeltaSeconds);
}

USkeletalMeshComponent* AEKCharacter::GetPawnMesh() const
{
	return GetMesh();
}

void AEKCharacter::TestMoveSelf()
{
	//bIsTestMove = true;
}

void AEKCharacter::ReceiveServerMove(const FVector & fvPos)
{

}

void AEKCharacter::ReceiveServerSync(const FVector & fvPos)
{

}

