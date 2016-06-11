// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************
//* Desc.  
//*
//* Created by ZP
//************************************************************************

#pragma once

#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "PandaWidget.generated.h"


/**
 *
 */
UCLASS()
class PANDA_API UPandaWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString m_AssetPath;

public:

	virtual void NativeConstruct()override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void UpdateSelf(float deltaTime);
	UFUNCTION(BlueprintCallable, Category = "PandaWidget")
		void  CloseSelf(bool bDestory = false);

public:
	UFUNCTION()
		virtual void OnLeft() {}
	UFUNCTION()
		virtual void OnRight() {}
	UFUNCTION()
		virtual void OnUp() {}
	UFUNCTION()
		virtual void OnDown();

	/** 圈*/
	UFUNCTION()
		virtual void OnCircle() {}
	/** 叉*/
	UFUNCTION()
		virtual void OnCross();
	UFUNCTION()
		virtual void OnSquare() {}
	UFUNCTION()
		virtual void OnTriangle() {}

	UFUNCTION()
		virtual void OnR1() {}
	UFUNCTION()
		virtual void OnR2() {}
	UFUNCTION()
		virtual void OnL1() {}
	UFUNCTION()
		virtual void OnL2() {}
	UFUNCTION()
		virtual void OnBag() {}


	FOnInputAction OnInputleft;
	FOnInputAction OnInputRight;
	FOnInputAction OnInputUp;
	FOnInputAction OnInputDown;

	FOnInputAction OnInput_Circle;
	FOnInputAction OnInput_Cross;
	FOnInputAction OnInput_Square;
	FOnInputAction OnInput_Triangle;

	FOnInputAction OnInput_R1;
	FOnInputAction OnInput_R2;
	FOnInputAction OnInput_L1;
	FOnInputAction OnInput_L2;

	FOnInputAction OnInput_closeBag;
//modify by anyin
public:
	//打开ui设置背景模糊
	void setSettingDim();
	UWidget* getChildByName(UUserWidget* widget, FString fname);
	int getTag() { return m_tag;}
	void setTag(int tag) { m_tag = tag; };
	int m_tag;

//modify by anyin

protected:
	class APlayerCharacter* m_Player;
};

