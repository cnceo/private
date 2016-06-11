// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "BaseAIController.h"

ABaseAIController::ABaseAIController()
{
	Init();
	// ...
}

void ABaseAIController::StopMovement()
{
	AAIController::StopMovement();
}

/* Init data */
void ABaseAIController::Init()
{
	pause = 0.f;
}