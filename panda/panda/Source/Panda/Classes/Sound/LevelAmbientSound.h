// Fill out your copyright notice in the Description page of Project Settings.
// add by yang. πÿø®±≥æ∞“Ù¿÷
#pragma once

#include "Sound/AmbientSound.h"
#include "LevelAmbientSound.generated.h"
/**
 * 
 */
UCLASS()
class PANDA_API ALevelAmbientSound : public AAmbientSound
{
	GENERATED_BODY()

public:
	ALevelAmbientSound();
	~ALevelAmbientSound();
	virtual void BeginPlay() override;
private:
	USoundBase* m_pSound;
};