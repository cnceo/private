// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PACameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API UPACameraManager : public UObject
{
	GENERATED_BODY()
public:
	UPACameraManager();
		UFUNCTION(BlueprintCallable, Category = "CameraAnimNotifyState")
		static UPACameraManager* GetCameraManagerInstance();
	UFUNCTION(BlueprintCallable, Category = "CameraAnimNotifyState")
		void PlayTaskCameraAnim(USceneComponent* pCom);
	UFUNCTION(BlueprintCallable, Category = "CameraAnimNotifyState")
		void StopTaskCameraAnim(USceneComponent* pCom);
	UFUNCTION(BlueprintCallable, Category = "CameraAnimNotifyState")
		void PlayLocCameraAnim(int id);
	
};
