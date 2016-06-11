// Fill out your copyright notice in the Description page of Project Settings.

// @ header MainAIController.h
// @ author white.tian
// @ createtime 2016Äê4ÔÂ27ÈÕ 13:44:30
// @ discussion The MainAIController class is used for AIController Base Class
// @ copyright Copyright(c) 2016 Beijing Lianyouyidian Science and Technology Ltd. All rights reserved.

#pragma once

#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAIController();

	/** Aborts the move the controller is currently performing */
	virtual void StopMovement() override;	


public:
	/* AI pause Time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAIParam)
	float pause;

	/* Init data */
	void Init();
};