

#include "EasyKit.h"
#include "EKWeapon_Instant.h"


AEKWeapon_Instant::AEKWeapon_Instant(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

//////////////////////////////////////////////////////////////////////////
// Weapon usage

void AEKWeapon_Instant::FireWeapon()
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float CurrentSpread = 1;
	const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

	//const FVector AimDir = GetAdjustedAim();
	//const FVector StartTrace = GetCameraDamageStartLocation(AimDir);
	//const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
	//const FVector EndTrace = StartTrace + ShootDir * InstantConfig.WeaponRange;

	//const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	//ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);

	//CurrentFiringSpread = FMath::Min(InstantConfig.FiringSpreadMax, CurrentFiringSpread + InstantConfig.FiringSpreadIncrement);
}

//void AEKWeapon_Instant::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(AEKWeapon_Instant, MyPawn);
//
//
//}