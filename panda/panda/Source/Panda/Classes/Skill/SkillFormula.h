// Fill out your copyright notice in the Description page of Project Settings.
//att by yang 技能数值公式
#pragma once
#include "SkillFormula.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (ShortTooltip = "SkillFormula"))
class PANDA_API USkillFormula :public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	float GetResult(AActor* pCauser, AActor* pTarget, float fParam);

};
