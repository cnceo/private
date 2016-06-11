// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget_Bag1.h"
#include "PandaGameInstance.h"
#include "ItemManager.h"
#include "PandaUtils.h"
#include "DataManager.h"
#include "WidgetLayoutLibrary.h"
UPandaWidget_Bag1::UPandaWidget_Bag1()
{
	m_selItemType = 101;
	m_itemIndex = 0;
	m_rollPos = FVector2D(1, 3);
}
UPandaWidget_Bag1::~UPandaWidget_Bag1()
{

}
void UPandaWidget_Bag1::NativeConstruct()
{
	UPandaWidget::NativeConstruct();
	setSelBagType(101);
	setItemIndex(0);
}
void UPandaWidget_Bag1::CreatePlayerBag(int itemType)
{
	UWrapBox* box_ = Cast<UWrapBox>(getChildByName(this,"WrapBox_71"));

	UItemManager* uitemMan = nullptr;
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		uitemMan = gameInstance->SafeGetItemManager();
	}
	box_->ClearChildren();

	//根据道具类型，获取所有道具
	m_uitems.Empty();
	uitemMan->getItemsByType(m_uitems,(emItemTypeDefine)itemType);
	for (UItem* ite : m_uitems)
	{
		//FString AssetPath = "/Game/BPInstance/UI/bag/Unit1.Unit1_C";
		//UBlueprintGeneratedClass* ParentClass6 = UPandaUtils::GetAssetFromPath(AssetPath);
		//UClass* GCClass = FindObject<UClass>(nullptr, TEXT("/Game/BPInstance/UI/bag/Unit1.Unit1_C"));
		UObject *inObject = uitemMan->GetEKObject(TEXT("/Game/BPInstance/UI/bag/Unit1.Unit1_C"));
		if (ensure(inObject))
		{
			UUserWidget* obj = CreateWidget<UUserWidget>(GWorld, Cast<UClass>(inObject));
			//auto  obj = NewObject<UPandaWidget>(this, GCClass);
			box_->AddChild(obj);
			//UKismetStringLibrary::Conv_IntToString(ite->getId());

 			auto CanvasPanel_itemBox = Cast<UCanvasPanel>(getChildByName(obj, TEXT("CanvasPanel_itemBox")));
			auto TextBlock_173 = Cast<UTextBlock>(getChildByName(obj, TEXT("TextBlock_173")));
			auto TextBlock_174 = Cast<UTextBlock>(getChildByName(obj, TEXT("TextBlock_174")));
			TextBlock_173->SetText(FText::FromString(ite->m_LocResItem->name));
			TextBlock_174->SetText(FText::FromString(ite->m_LocResItem->describe));
 			CanvasPanel_itemBox->AddChild(ite->getItemIcon());
		}
	}
}
void UPandaWidget_Bag1::updateBag()
{
	if (m_selItemType)
	{
		CreatePlayerBag((emItemTypeDefine)m_selItemType);
	}
}

bool UPandaWidget_Bag1::addItem()
{
	UWrapBox* box_ = Cast<UWrapBox>(getChildByName(this, "WrapBox_71"));

	UItemManager* uitemMan = nullptr;
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		uitemMan = gameInstance->SafeGetItemManager();
	}
	uitemMan->addItem();
	if (m_selItemType)
	{
		switch (m_selItemType)
		{
		case 101:
			CreatePlayerBag(1);
			break;
		case 102:
			CreatePlayerBag(2);
			break;
		case 103:
			CreatePlayerBag(3);
			break;
		default:
			break;
		}
	}
	setItemIndex(0);
	m_rollPos = FVector2D(1, 3);
	UScrollBox* ScrollBox_213 = Cast<UScrollBox>(getChildByName(this, "ScrollBox_213"));
	ScrollBox_213->SetScrollOffset(0);
	return true;
}
bool UPandaWidget_Bag1::RemoveItemById(int id_)
{
	UWrapBox* box_ = Cast<UWrapBox>(getChildByName(this, "WrapBox_71"));
// 
// 	int childCunt = box_->GetChildrenCount();
// 	box_->RemoveChildAt(childCunt - 1);

	UItemManager* uitemMan = nullptr;
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		uitemMan = gameInstance->SafeGetItemManager();
	}
	uitemMan->removeItemById(id_);
	if (m_selItemType)
	{
		switch (m_selItemType)
		{
		case 101:
			CreatePlayerBag(1);
			break;
		case 102:
			CreatePlayerBag(2);
			break;
		case 103:
			CreatePlayerBag(3);
			break;
		default:
			break;
		}
	}
	int idx = getItemIdx(id_);
	setItemIndex(0);
	m_rollPos = FVector2D(1, 3);
	UScrollBox* ScrollBox_213 = Cast<UScrollBox>(getChildByName(this, "ScrollBox_213"));
	ScrollBox_213->SetScrollOffset(0);
	return true;
}

void UPandaWidget_Bag1::OnLeft()
{
	setItemIndex(m_itemIndex-1);
}

void UPandaWidget_Bag1::OnRight()
{
	setItemIndex(m_itemIndex + 1);
}

void UPandaWidget_Bag1::OnUp()
{
	setItemIndex(m_itemIndex - 3);
}

void UPandaWidget_Bag1::OnDown()
{
	setItemIndex(m_itemIndex + 3);
}

void UPandaWidget_Bag1::OnCircle()
{

}

void UPandaWidget_Bag1::OnCross()
{

}

void UPandaWidget_Bag1::OnSquare()
{

}

void UPandaWidget_Bag1::OnTriangle()
{

}

void UPandaWidget_Bag1::OnR1()
{
	setSelBagType(m_selItemType + 1);
}
void UPandaWidget_Bag1::OnR2()
{

}

void UPandaWidget_Bag1::OnL1()
{
	setSelBagType(m_selItemType - 1);
}

void UPandaWidget_Bag1::OnL2()
{

}
void UPandaWidget_Bag1::OnBag()
{
	RemoveFromParent();
}
void UPandaWidget_Bag1::setSelBagType(int bagType)
{
	UImage* Image_101 = Cast<UImage>(getChildByName(this, "Image_101"));
	UImage* Image_102 = Cast<UImage>(getChildByName(this, "Image_102"));
	UImage* Image_103 = Cast<UImage>(getChildByName(this, "Image_103"));
	Image_101->SetVisibility(ESlateVisibility::Hidden);
	Image_102->SetVisibility(ESlateVisibility::Hidden);
	Image_103->SetVisibility(ESlateVisibility::Hidden);
	m_rollPos = FVector2D(1, 3);
	UScrollBox* ScrollBox_213 = Cast<UScrollBox>(getChildByName(this, "ScrollBox_213"));
	ScrollBox_213->SetScrollOffset(0);
	if (bagType > 103)
	{
		m_selItemType = 101;
	}
	else if (bagType < 101)
	{
		m_selItemType = 103;
	}
	else
	{
		m_selItemType = bagType;
	}
	switch (m_selItemType)
	{
	case 101:
		CreatePlayerBag(1);
		Image_101->SetVisibility(ESlateVisibility::Visible);
		setItemIndex(0);
		break;
	case 102:
		CreatePlayerBag(2);
		Image_102->SetVisibility(ESlateVisibility::Visible);
		setItemIndex(0);
		break;
	case 103:
		CreatePlayerBag(3);
		Image_103->SetVisibility(ESlateVisibility::Visible);
		setItemIndex(0);
		break;
	default:
		break;
	}
}
void UPandaWidget_Bag1::setItemIndex(int index)
{
	int oldInded = m_itemIndex;
	int itemSize = m_uitems.Num();
	if (itemSize <= 0)
	{
		return;
	}
	if (index >= itemSize || index<0)
	{
		return;
	}
	//设置选中效果
	int myIndex = index;
	UWrapBox* box_ = Cast<UWrapBox>(getChildByName(this, "WrapBox_71"));
	UUserWidget* slot = Cast<UUserWidget>(box_->GetChildAt(myIndex));
	UUserWidget* currSlot = Cast<UUserWidget>(box_->GetChildAt(m_itemIndex));
	if (currSlot)
	{
		UImage* currSelImage = Cast<UImage>(getChildByName(currSlot, "Image_sel"));
		currSelImage->SetVisibility(ESlateVisibility::Hidden);

		UImage* currdImage = Cast<UImage>(getChildByName(currSlot, "Image_48"));
		currdImage->SetVisibility(ESlateVisibility::Visible);
	}
	if (slot)
	{
		UImage* SelImage = Cast<UImage>(getChildByName(slot, "Image_sel"));
		SelImage->SetVisibility(ESlateVisibility::Visible);

		UImage* oldImage = Cast<UImage>(getChildByName(slot, "Image_48"));
		oldImage->SetVisibility(ESlateVisibility::Hidden);
		m_itemIndex = myIndex;
	}
	
	//设置自动滚动
	UScrollBox* ScrollBox_213 = Cast<UScrollBox>(getChildByName(this, "ScrollBox_213"));

	int row = (m_uitems.Num()) / 3;
	int rem = (m_uitems.Num()) % 3;

	rem = ((m_itemIndex+1) % 3);
	row = (m_itemIndex+1) / 3;
	if (rem > 0 )
	{
		row += 1;
	}
	if (row > m_rollPos.Y)
	{
		ScrollBox_213->SetScrollOffset(ScrollBox_213->GetScrollOffset()+153);
		m_rollPos.X += 1;
		m_rollPos.Y += 1;
	}else if (row < m_rollPos.X )
	{
		ScrollBox_213->SetScrollOffset(ScrollBox_213->GetScrollOffset() - 153);
		m_rollPos.X -= 1;
		m_rollPos.Y -= 1;
	}

	//播放选中效果
	playerEff(oldInded,m_itemIndex);

	UCanvasPanelSlot* myslot = Cast<UCanvasPanelSlot>(ScrollBox_213->Slot);
}
int UPandaWidget_Bag1::getSelItemId()
{
	if (m_uitems.Num()==0)
	{
		return -1;
	}
	UItem* myItem = m_uitems[m_itemIndex];
	return myItem->getItemId();
}
int UPandaWidget_Bag1::getItemIdx(int id)
{
	int idx = 0;
	for (UItem*  ite : m_uitems)
	{
		if (ite->getItemId() == id)
		{
			return idx;
		}
		idx += 1;
	}
	return -1;
}