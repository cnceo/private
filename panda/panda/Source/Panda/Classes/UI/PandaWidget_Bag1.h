// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/PandaWidget.h"
#include "PandaWidget_Bag1.generated.h"
/**
 * 
 */
UCLASS()
class PANDA_API UPandaWidget_Bag1 : public UPandaWidget
{
	GENERATED_BODY()
	
public:
	UPandaWidget_Bag1();
	~UPandaWidget_Bag1();
	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	/** 创建背包 */
	UFUNCTION(BlueprintCallable, Category = "bag")
	void CreatePlayerBag(int itemType) ;
	/*更新背包*/
	UFUNCTION(BlueprintCallable, Category = "bag")
	void updateBag();
	/** 根据id移除物品 */
	UFUNCTION(BlueprintCallable, Category = "bag")
	bool RemoveItemById( int id_);
	UFUNCTION(BlueprintCallable, Category = "bag")
	void setSelBagType(int bagType);
	UFUNCTION(BlueprintCallable, Category = "bag")
	void setItemIndex(int index);
	UFUNCTION(BlueprintCallable, Category = "bag")
	int getSelItemId();
	UFUNCTION(BlueprintCallable, Category = "bag")
	int getItemIdx(int id);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "bag")
	void playerEff(int old , int curr);
	UFUNCTION(BlueprintCallable, Category = "bag")
	bool addItem();
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
	virtual void OnCircle()override;
	UFUNCTION()
	virtual void OnCross()override;
	UFUNCTION()
	virtual void OnSquare()override;
	UFUNCTION()
	virtual void OnTriangle()override;

	UFUNCTION()
	virtual void OnR1()override;
	UFUNCTION()
	virtual void OnR2()override;
	UFUNCTION()
	virtual void OnL1()override;
	UFUNCTION()
	virtual void OnL2()override;
	UFUNCTION()
	virtual void OnBag() override;
		
private:
	TArray<UItem*> m_uitems;
	int m_itemIndex;
	int m_selItemType;

	FVector2D m_rollPos;//背包滚动的上下行位置
};
