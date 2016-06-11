//
// EKUesItem.h
//
// ���н�ɫ�����ƶ��Ļ�ɿ��ƵĽ�ɫ������
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

	/** ���Ŷ��� ���Բ��Ŷ���������̫�� */
	//virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;
	//virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, bool isLoop = false);
	//virtual float PlayAnimAsset(class UAnimationAsset* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);
	virtual void PlayAnimAsset(class UAnimationAsset* AnimMontage, bool isLoop = false);

	/** ֹͣ���Ŷ��� */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/** ֹͣ�������ж��� */
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

	/** ���Player�Ƿ񻹴�� */
	virtual bool IsAlive() const;

	/** get camera view type */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

	/* ֪ͨ��ͼ �Ѵ�����Ҵ��������� **/
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Panda Hit"))
	void EventPhysicsHit(FName inBoneName, FVector ImpactNormal, FVector inHitLoaction);
	

	/** Update the character. (Running, health etc). */
	virtual void Tick(float DeltaSeconds) override;

	void TestMoveSelf();

	virtual void ReceiveServerMove(const FVector &);

	virtual void ReceiveServerSync(const FVector &);

	//////////////////////////////////////////////////////////////////////////
	// Reading data
	/** ��� mesh component */
	USkeletalMeshComponent* GetPawnMesh() const;

	FEKPlayerState* mPlayerState;

	/* Tick֪ͨ�����ѿ�ʼ **/
	virtual void AttackNotify_Begin(){};
	/* Tick֪ͨ�����ѽ��� **/
	virtual void AttackNotify_End(){};
	/* Tick֪ͨ���������� **/
	virtual void AttackNotify_Tick(float DeltaTime){};
	/* ֪ͨ���������ѽ��� **/
	virtual void AttackAnimEnd(){};

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

