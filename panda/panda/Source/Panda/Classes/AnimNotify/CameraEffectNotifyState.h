// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CameraEffectNotifyState.generated.h"


UENUM(BlueprintType)
enum class emCameraType : uint8
{
	ManJingTou,//��ͷ����
	DouDong, //��ͷ����
	MoHu,//��ͷģ��
	BianSe//��ͷ��ɫ
};
/**
 * 
 */
UCLASS()
class PANDA_API UCameraEffectNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UCameraEffectNotifyState();
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraEffect")
	emCameraType CameraType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraEffect")
	float  speed;

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraEffect")
// 	float  ShakeTime;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraEffect")
// 	float  ShakeScope;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraEffect")
	TSubclassOf<class UCameraShake> myCameraShake;
};
