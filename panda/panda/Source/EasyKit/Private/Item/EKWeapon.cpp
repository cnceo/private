

#include "EasyKit.h"
#include "EKCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EKWeapon.h"


AEKWeapon::AEKWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

//////////////////////////////////////////////////////////////////////////
// Input

void AEKWeapon::StartAttack()
{

}

void AEKWeapon::StopAttack()
{

}

//////////////////////////////////////////////////////////////////////////
// Replication & effects

void AEKWeapon::OnRep_MyPawn()
{

}

void AEKWeapon::OnRep_BurstCounter()
{

}

void AEKWeapon::OnRep_Reload()
{

}


USkeletalMeshComponent* AEKWeapon::GetWeaponMesh() const
{
	return NULL;//(MyPawn != NULL && MyPawn->IsFirstPerson()) ? Mesh1P : Mesh3P;
}

//////////////////////////////////////////////////////////////////////////
// Weapon usage helpers

UAudioComponent* AEKWeapon::PlayWeaponSound(USoundCue* Sound)
{
	UAudioComponent* AC = NULL;
	if (Sound && MyPawn)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, MyPawn->GetRootComponent());
	}

	return AC;
}

float AEKWeapon::PlayWeaponAnimation(const FWeaponAnim& Animation)
{
	float Duration = 0.0f;
	if (MyPawn)
	{
		UAnimMontage* UseAnim = MyPawn->IsFirstPerson() ? Animation.Pawn1P : Animation.Pawn3P;
		if (UseAnim)
		{
			Duration = MyPawn->PlayAnimMontage(UseAnim, false);
		}
	}

	return Duration;
}

void AEKWeapon::StopWeaponAnimation(const FWeaponAnim& Animation)
{
	if (MyPawn)
	{
		UAnimMontage* UseAnim = MyPawn->IsFirstPerson() ? Animation.Pawn1P : Animation.Pawn3P;
		if (UseAnim)
		{
			MyPawn->StopAnimMontage(UseAnim);
		}
	}
}

FVector AEKWeapon::GetCameraAim() const
{
	APlayerController* const PlayerController = Instigator ? Cast<APlayerController>(Instigator->Controller) : NULL;
	FVector FinalAim = FVector::ZeroVector;

	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
		FinalAim = CamRot.Vector();
	}
	else if (Instigator)
	{
		FinalAim = Instigator->GetBaseAimRotation().Vector();
	}

	return FinalAim;
}

FVector AEKWeapon::GetAdjustedAim() const
{
	APlayerController* const PlayerController = Instigator ? Cast<APlayerController>(Instigator->Controller) : NULL;
	FVector FinalAim = FVector::ZeroVector;
	// If we have a player controller use it for the aim
	if (PlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
		FinalAim = CamRot.Vector();
	}
	else if (Instigator)
	{
		//// Now see if we have an AI controller - we will want to get the aim from there if we do
		//AShooterAIController* AIController = MyPawn ? Cast<AShooterAIController>(MyPawn->Controller) : NULL;
		//if (AIController != NULL)
		//{
		//	FinalAim = AIController->GetControlRotation().Vector();
		//}
		//else
		//{
		//	FinalAim = Instigator->GetBaseAimRotation().Vector();
		//}
	}

	return FinalAim;
}

FVector AEKWeapon::GetCameraDamageStartLocation(const FVector& AimDir) const
{
	//AShooterPlayerController* PC = MyPawn ? Cast<AShooterPlayerController>(MyPawn->Controller) : NULL;
	//AShooterAIController* AIPC = MyPawn ? Cast<AShooterAIController>(MyPawn->Controller) : NULL;
	FVector OutStartTrace = FVector::ZeroVector;

	//if (PC)
	//{
	//	// use player's camera
	//	FRotator UnusedRot;
	//	PC->GetPlayerViewPoint(OutStartTrace, UnusedRot);

	//	// Adjust trace so there is nothing blocking the ray between the camera and the pawn, and calculate distance from adjusted start
	//	OutStartTrace = OutStartTrace + AimDir * ((Instigator->GetActorLocation() - OutStartTrace) | AimDir);
	//}
	//else if (AIPC)
	//{
	//	OutStartTrace = GetMuzzleLocation();
	//}

	return OutStartTrace;
}

FVector AEKWeapon::GetMuzzleLocation() const
{
	return FVector::ZeroVector;
}

FVector AEKWeapon::GetMuzzleDirection() const
{
	return FVector::ZeroVector;
}

FHitResult AEKWeapon::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_WEAPON, TraceParams);

	return Hit;
}

void AEKWeapon::SetOwningPawn(AEKCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		Instigator = NewOwner;
		MyPawn = NewOwner;
		// net owner for RPC calls
		SetOwner(NewOwner);
	}
}

void AEKWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}