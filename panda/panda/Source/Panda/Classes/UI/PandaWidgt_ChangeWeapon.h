// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidgt_ChangeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API UPandaWidgt_ChangeWeapon : public UPandaWidget
{
	GENERATED_BODY()
	UPandaWidgt_ChangeWeapon();
	~UPandaWidgt_ChangeWeapon();
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "bag")
	void playerEff(int old, int curr);
	void setItemIndex(int index);
	void changeWeapon(int id);
	UFUNCTION(BlueprintCallable, Category = "UPandaWidgt_ChangeWeapon")
	void createMath();

public:
	UFUNCTION()
		virtual void OnLeft()override;
	UFUNCTION()
		virtual void OnRight()override;
	UFUNCTION()
		virtual void OnUp()override;
	UFUNCTION()
		virtual void OnDown()override;
	UFUNCTION()
		virtual void OnCircle() override;
private:
	int m_itemIndex;
	TArray<int> weapons;
	FVector2D m_rollPos;//滚动的上下行位置
};
