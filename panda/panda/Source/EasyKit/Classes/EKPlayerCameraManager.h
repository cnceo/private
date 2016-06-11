// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "EKPlayerCameraManager.generated.h"

UENUM()
enum  CAMERA_MODE
{
	CAMERA_NONE,
	CAMERA_FREE,
	CAMERA_SCENE,
	CAMERA_SKILL
};


UCLASS()
class EASYKIT_API AEKPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_UCLASS_BODY()

public:

	CAMERA_MODE CameraMode;

	/** normal FOV */
	float NormalFOV;

	/** targeting FOV */
	float TargetingFOV;

	/** After updating camera, inform pawn to update 1p mesh to match camera's location&rotation */
	virtual void UpdateCamera(float DeltaTime) override;

	virtual void SetCameraMode(CAMERA_MODE inType);

	void SetDevAngle(float inAngle);
	void SetMaxArmLength(float inLength);
	void SetMinArmLength(float inLength);
	void SetArmSpeed(float inSpeed);


	void AddSceneCamera(class ACameraActor* inCamera);
	void RemoveSceneCamera(class ACameraActor* inCamera);

protected:

	virtual void NoneMode(float DeltaTime);
	virtual void FreeMode(float DeltaTime);
	virtual void SceneMode(float DeltaTime);
	virtual void SkillMode(float DeltaTime);

private:

	float DevAngle;
	float MaxArmLength;
	float MinArmLength;
	float ArmSpeed;
	
	TArray<class ACameraActor*> SceneCameraList;
};
