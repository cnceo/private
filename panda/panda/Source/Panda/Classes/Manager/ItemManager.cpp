// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaGameInstance.h"
#include "ItemManager.h"
#include "EKGameFrame.h"
#include "PandaUtils.h"
TEnumAsByte<enum emItemType> UItem::getItemType()
{
	return m_LocResItem->itemType;
}
UImage* UItem::getItemIcon()
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		UItemManager* itemM = gameInstance->SafeGetItemManager();
		UImage* icon = nullptr;
		icon = NewObject<UImage>(this);

		UObject* test = UPandaUtils::CreateAsset(FString(TEXT("/Game/UITextures/itemIcon/")) + m_LocResItem->icon);
		icon->Brush.SetResourceObject(test);
		icon->Brush.ImageSize = FVector2D(120, 200);

		return icon;
	}
	return nullptr;
}
//================UitemManager=================
UItemManager::UItemManager()
{
	m_cretaeId = 100;
}
bool UItemManager::init()
{
	m_items.Empty();
	m_selWeapons.Empty();
	DataManager* itemM = UPandaGameInstance::Instance()->SafeGetDataManager();
	loadItems(itemM);

	m_useWeapon = 0;
	return true;
}

UItem* UItemManager::getItemById(int id)
{
// 	for (UItem& temItem : m_items)
// 	{
// 		if (temItem.getId() == id)
// 		{
// 			return &temItem;
// 		}
// 	}
	return nullptr;
}
void UItemManager::removeItemById(int id)
{
	for (UItem* temItem : m_items)
	{
		if (temItem->getItemId() == id)
		{
			m_items.Remove(temItem);
			return;
		}
	}
}

TArray<UItem*> UItemManager::getItemsByType(TArray<UItem*>& temArr,TEnumAsByte<enum emItemTypeDefine> itemTye)
{
	for (UItem* temItem : m_items)
	{
		if (temItem->getItemType() == itemTye)
		{
			temArr.Push(temItem);
		}
	}
	return temArr;
}

UObject * UItemManager::GetEKObject(const FString&  fsPath)
{
	FStringAssetReference ref = fsPath;
	UObject* uoTmp = ref.ResolveObject();
	if (uoTmp == nullptr)
	{
		FStreamableManager EKAssetLoader;

		uoTmp = EKAssetLoader.SynchronousLoad(ref);
	}
	return uoTmp;
}
void UItemManager::loadItems(DataManager* dataM)
{
	m_items.Empty();
	for (int i = 1; i < 20; i++)
	{
		UItem*  obj = NewObject<UItem>(this, *FString::Printf(TEXT("Item%d"),  i), RF_MarkAsRootSet);
		obj->m_LocResItem = dataM->getItemLocInfo(18);
		m_items.Add(obj);
		obj->m_id = i;
	}

	for (int i = 20; i < 35; i++)
	{
		UItem*  obj = NewObject<UItem>(this, *FString::Printf(TEXT("Item%d"), i), RF_MarkAsRootSet);
		obj->m_LocResItem = dataM->getItemLocInfo(19);
		m_items.Add(obj);
		obj->m_id = i;
		
	}

	for (int i = 35; i < 40; i++)
	{
		UItem*  obj = NewObject<UItem>(this, *FString::Printf(TEXT("Item%d"), i), RF_MarkAsRootSet);
		obj->m_LocResItem = dataM->getItemLocInfo(20);
		m_items.Add(obj);
		obj->m_id = i;

	}
	m_selWeapons.Add(1);
	m_selWeapons.Add(5);
}
UItem* UItemManager::addItem()
{
	DataManager* dataM = UPandaGameInstance::Instance()->SafeGetDataManager();
	int createId = createItemId();
	UItem*  obj = NewObject<UItem>(this, *FString::Printf(TEXT("Item%d"), createId), RF_MarkAsRootSet);
	obj->m_LocResItem = dataM->getItemLocInfo(20);
	m_items.Add(obj);
	obj->m_id = createId;

	return obj;
}
int UItemManager::createItemId()
{
	return m_cretaeId += 1;

}

int UItemManager::getUseWeapon()
{
	return m_useWeapon;
}
void UItemManager::setUseWeapon(int id)
{
	m_useWeapon = id;
}

UItem* UItemManager::getWeaponByIdx(int idx)
{
	if (m_selWeapons.Num() > idx)
	{
		int itemId = m_selWeapons[idx];
		return getItemById(itemId);
	}
	return nullptr;
}