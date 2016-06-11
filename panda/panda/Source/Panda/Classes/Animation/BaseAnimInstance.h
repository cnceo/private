// Fill out your copyright notice in the Description page of Project Settings.
//add by yang
#pragma once

#include "Animation/AnimInstance.h"
#include "BaseAniInterface.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta = (ShortTooltip = "Base AnimInstance"))
class PANDA_API UBaseAnimInstance : public UAnimInstance, public IBaseAniInterface
{
	GENERATED_BODY()
	
public:
	UBaseAnimInstance();
	~UBaseAnimInstance();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlaySkill();

	void OnAnimTick_Implementation(float fTime, const FString& AnimName);
	void OnAnimBegin_Implementation(float fTime, const FString& AnimName);
	void OnAnimEnd_Implementation(const FString& AnimName);

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	void OnAnimTickBP(float fTime, const FString& AnimName);

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	void OnAnimBeginBP(float fTime, const FString& AnimName);

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	void OnAnimEndBP(const FString& AnimName);

public:
	UPROPERTY(BlueprintReadWrite, Category = "AnimInstance")
	float m_fMaxAnimTime;

	UPROPERTY(BlueprintReadWrite, Category = "AnimInstance")
	float m_fFlowAnimTime;
};
