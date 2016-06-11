// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Object.h"
#include "DataManager.h"
#include "PAItemData.h"
#include "ItemManager.generated.h"

class UItemManager;
//道具类
UCLASS()
class UItem : public UObject
{
	GENERATED_BODY()
	
public:
	
	int getItemId() { return m_id; }
	TEnumAsByte<enum emItemType> getItemType();
	UImage* getItemIcon();
	const FsPAItemData* m_LocResItem;
	int m_id;
};

UCLASS()
class PANDA_API UItemManager : public UObject
{
	GENERATED_BODY()
public:
	UItemManager();
	bool init();
	void loadItems(DataManager* dataM);
	UObject * GetEKObject(const FString&  fsPath);
	int createItemId();
	// 道具相关
	UItem* getItemById(int id);
	UItem* addItem();
	void removeItemById(int id);
	TArray<UItem*>getItemsByType(TArray<UItem*>& temArr, TEnumAsByte<enum emItemTypeDefine> itemTye);

	//武器相关
	int getUseWeapon();
	void setUseWeapon(int id);
	UItem* getWeaponByIdx(int idx);
	TArray<int> getWeapons() { return m_selWeapons; }
private:
	TArray<UItem*> m_items;//所有道具
	TArray<int> m_selWeapons;//携带的全部武器
	int m_useWeapon;//当前使用的武器
	int m_cretaeId;
};
