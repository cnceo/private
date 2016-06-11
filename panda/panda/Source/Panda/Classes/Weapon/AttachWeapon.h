// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttachObjBase.h"
#include "CommonDefine.h"
#include "AttachWeapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PANDA_API AAttachWeapon : public AAttachObjBase
{
	GENERATED_BODY()

	AAttachWeapon();
	
public:

	//Weapon data
	UPROPERTY(Category = "Weapon", EditDefaultsOnly, BlueprintReadWrite)
	FsWeaponBaseData m_WeapData;


	
};
