//
// EKUesItem.h
//
// 所有角色（可移动的或可控制的角色）基类
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

//#include "Foundation/Platform.h"
#include "EKPlayerState.h"
#include "EKPlayerCameraManager.h"
#include "EKCharacter.generated.h"



UCLASS(Abstract, Blueprintable)
class EASYKIT_API AEKCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	//class UStaticMeshComponent* usmRWeaponComponent;
	//static FName fnRWeapon;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	//class UStaticMeshComponent* usmLWeaponComponent;
	//static FName fnLWeapon;

public:

	//////////////////////////////////////////////////////////////////////////
	// Camera 
	// 
	//////////////////////////////////////////////////////////////////////////
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Camera Auto Rotation Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DevAngle;
	/** Camera Auto Arm Max Length */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxArmLength;
	/** Camera Auto Arm Min Length */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinArmLength;
	/** Camera Auto Arm Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ArmSpeed;
	/** Set Camera Mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TEnumAsByte<CAMERA_MODE> CameraMode;

	//////////////////////////////////////////////////////////////////////////
	/* Player current HP */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Health")
	int32 TeamColorID;


	int64_t nGUID;
	int32 nCharacterID;
	FString fsName;


	bool bIsUpdateTick;
	bool bOpenMap;

	class USkeletalMeshComponent* GetMeshComponent()
	{
		return GetMesh();
	}

	/** get max health */
	int32 GetMaxHealth() const;
	virtual void OpenMap(){};
	//////////////////////////////////////////////////////////////////////////
	// Animations

	/** 播放动画 可以播放动画集和蒙太奇 */
	//virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;
	//virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, bool isLoop = false);
	//virtual float PlayAnimAsset(class UAnimationAsset* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);
	virtual void PlayAnimAsset(class UAnimationAsset* AnimMontage, bool isLoop = false);

	/** 停止播放动画 */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/** 停止播放所有动画 */
	void StopAllAnimMontages();

	/* Refresh Character Attributes */
	virtual bool RefreshAttrByID(int InID) { return true; }

	/************************************************************************/
	/* Change Meshes                                                        */
	/************************************************************************/
	virtual bool ChangeMeshesByID(int InID);

	/************************************************************************/
	/* Change Body Skeleton Mesh                                            */
	/************************************************************************/
	virtual bool ChangeBodyMeshByID(int InID);

	/************************************************************************/
	/* Change Body AnimBP                                          */
	/************************************************************************/
	virtual bool ChangeAnimBPByID(int InID);

	/************************************************************************/
	/* Change Right Weapon Mesh By ID                                       */
	/************************************************************************/
	virtual bool ChangeRWeaponMeshByID(int nRWID);

	/************************************************************************/
	/* Change Left Weapon Mesh By ID                                       */
	/************************************************************************/
	virtual bool ChangeLWeaponMeshByID(int nLWID);

	/** 检测Player是否还存活 */
	virtual bool IsAlive() const;

	/** get camera view type */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

	/* 通知蓝图 已打击并且传骨骼名称 **/
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Panda Hit"))
	void EventPhysicsHit(FName inBoneName, FVector ImpactNormal, FVector inHitLoaction);
	

	/** Update the character. (Running, health etc). */
	virtual void Tick(float DeltaSeconds) override;

	void TestMoveSelf();

	virtual void ReceiveServerMove(const FVector &);

	virtual void ReceiveServerSync(const FVector &);

	//////////////////////////////////////////////////////////////////////////
	// Reading data
	/** 获得 mesh component */
	USkeletalMeshComponent* GetPawnMesh() const;

	FEKPlayerState* mPlayerState;

	/* Tick通知攻击已开始 **/
	virtual void AttackNotify_Begin(){};
	/* Tick通知攻击已结束 **/
	virtual void AttackNotify_End(){};
	/* Tick通知攻击持续中 **/
	virtual void AttackNotify_Tick(float DeltaTime){};
	/* 通知攻击动画已结束 **/
	virtual void AttackAnimEnd(){};

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

