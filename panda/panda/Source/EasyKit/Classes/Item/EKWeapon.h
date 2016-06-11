//
// EKWeapon.h
//
// 所有武器基类
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once


#include "EKWeapon.generated.h"

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

	/** animation played on pawn (1st person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* Pawn1P;

	/** animation played on pawn (3rd person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* Pawn3P;
};

/**
*
*/
UCLASS(Abstract, Blueprintable)
class EASYKIT_API AEKWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	//////////////////////////////////////////////////////////////////////////
	// Ammo

	enum class EWeaponType
	{
		EBullet,
		EMelee,
		EMax,
	};

	/** query Weapon type */
	virtual EWeaponType GetAmmoType() const
	{
		return EWeaponType::EMelee;
	}


	/** pawn owner */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_MyPawn)
	class AEKCharacter* MyPawn;

	//////////////////////////////////////////////////////////////////////////
	// Replication & effects

	UFUNCTION()
		void OnRep_MyPawn();

	UFUNCTION()
		void OnRep_BurstCounter();

	UFUNCTION()
		void OnRep_Reload();


	/** get weapon mesh (needs pawn owner to determine variant) */
	USkeletalMeshComponent* GetWeaponMesh() const;

	//////////////////////////////////////////////////////////////////////////
	// Input

	/** [local + server] start weapon fire */
	virtual void StartAttack();

	/** [local + server] stop weapon fire */
	virtual void StopAttack();

	//////////////////////////////////////////////////////////////////////////
	// Weapon usage

	/** [local] weapon specific fire implementation */
	virtual void FireWeapon() PURE_VIRTUAL(AEKWeapon::FireWeapon, );


	//////////////////////////////////////////////////////////////////////////
	// Weapon usage helpers

	/** play weapon sounds */
	UAudioComponent* PlayWeaponSound(class USoundCue* Sound);

	/** play weapon animations */
	float PlayWeaponAnimation(const FWeaponAnim& Animation);

	/** stop playing weapon animations */
	void StopWeaponAnimation(const FWeaponAnim& Animation);

	/** Get the aim of the weapon, allowing for adjustments to be made by the weapon */
	virtual FVector GetAdjustedAim() const;

	/** Get the aim of the camera */
	FVector GetCameraAim() const;

	/** get the originating location for camera damage */
	FVector GetCameraDamageStartLocation(const FVector& AimDir) const;

	void SetOwningPawn(AEKCharacter* NewOwner);

	FVector GetMuzzleLocation() const;
	FVector GetMuzzleDirection() const;

	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;
};

USTRUCT()
struct FEKItems
{
	GENERATED_USTRUCT_BODY()


};