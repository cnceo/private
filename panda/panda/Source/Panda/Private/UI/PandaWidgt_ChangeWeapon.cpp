// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidgt_ChangeWeapon.h"
#include "PandaUtils.h"
#include "ItemManager.h"
#include "PandaGameInstance.h"
#include "MainPlayerController.h"

UPandaWidgt_ChangeWeapon::UPandaWidgt_ChangeWeapon()
{
	weapons.Empty();
	m_rollPos = FVector2D(1, 3);
}
UPandaWidgt_ChangeWeapon::~UPandaWidgt_ChangeWeapon()
{

}
void UPandaWidgt_ChangeWeapon::NativeConstruct()
{
	UPandaWidget::NativeConstruct();

	UItemManager* itemM = nullptr;
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		itemM = gameInstance->SafeGetItemManager();
	}

	UHorizontalBox* HorizontalBox_30 = Cast<UHorizontalBox>(getChildByName(this, "HorizontalBox_30"));
	HorizontalBox_30->ClearChildren();
	weapons = itemM->getWeapons();
	for (int i = 0; i < weapons.Num();i++)
	{
		UObject *inObject = UPandaUtils::CreateAsset(TEXT("/Game/BPInstance/UI/Weapon/weapon_unit.weapon_unit_C"));
		if (inObject && ensure(inObject))
		{
			UUserWidget* obj = CreateWidget<UUserWidget>(GWorld, Cast<UClass>(inObject));
			HorizontalBox_30->AddChild(obj);

			auto CanvasPanel_83 = Cast<UHorizontalBox>(getChildByName(obj, "HorizontalBox_30"));
		}
	}
	setItemIndex(0);
}

void UPandaWidgt_ChangeWeapon::setItemIndex(int index)
{
	int oldInded = m_itemIndex;
	int itemSize = weapons.Num();
	if (itemSize <= 0)
	{
		return;
	}
	if (index >= itemSize || index < 0)
	{
		return;
	}
	//设置选中效果
	int myIndex = index;
	UHorizontalBox* box_ = Cast<UHorizontalBox>(getChildByName(this, "HorizontalBox_30"));
	UUserWidget* slot = Cast<UUserWidget>(box_->GetChildAt(myIndex));
	UUserWidget* currSlot = Cast<UUserWidget>(box_->GetChildAt(m_itemIndex));
	if (currSlot)
	{
		//UImage* currSelImage = Cast<UImage>(getChildByName(currSlot, "Image_66"));
		//currSelImage->SetVisibility(ESlateVisibility::Hidden);

		UImage* currdImage = Cast<UImage>(getChildByName(currSlot, "Image_66"));
		currdImage->SetVisibility(ESlateVisibility::Hidden);
	}
	if (slot)
	{
		//UImage* SelImage = Cast<UImage>(getChildByName(slot, "Image_66"));
		//SelImage->SetVisibility(ESlateVisibility::Visible);

		UImage* oldImage = Cast<UImage>(getChildByName(slot, "Image_66"));
		oldImage->SetVisibility(ESlateVisibility::Visible);
	}
	m_itemIndex = myIndex;

	//设置自动滚动
	UScrollBox* ScrollBox_213 = Cast<UScrollBox>(getChildByName(this, "ScrollBox_57"));

	int youbiao = m_itemIndex + 1;
	if (youbiao > m_rollPos.Y)
	{
		ScrollBox_213->SetScrollOffset(ScrollBox_213->GetScrollOffset() + 390);
		m_rollPos.X += 1;
		m_rollPos.Y += 1;
	}
	else if (youbiao < m_rollPos.X)
	{
		ScrollBox_213->SetScrollOffset(ScrollBox_213->GetScrollOffset() - 390);
		m_rollPos.X -= 1;
		m_rollPos.Y -= 1;
	}

	//播放选中效果
	playerEff(oldInded, m_itemIndex);

}
void UPandaWidgt_ChangeWeapon::changeWeapon(int id)
{
	AMainPlayerController* contro = Cast<AMainPlayerController>(UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance())) ;
	APlayerCharacter* character = contro->GetMainPlayer();
	switch (id)
	{
	case 1:
		character->EquipWeapon("");
		RemoveFromParent();
		break;
	case 5:
		character->UnequipWeapon();
		RemoveFromParent();
		break;
	default:
		break;
	}

}
void UPandaWidgt_ChangeWeapon::OnLeft()
{
	setItemIndex(m_itemIndex - 1);
}

void UPandaWidgt_ChangeWeapon::OnRight()
{
	setItemIndex(m_itemIndex + 1);
}

void UPandaWidgt_ChangeWeapon::OnUp()
{
	setItemIndex(m_itemIndex - 3);
}

void UPandaWidgt_ChangeWeapon::OnDown()
{
	setItemIndex(m_itemIndex + 3);
}
void UPandaWidgt_ChangeWeapon::OnCircle()
{
	int id = weapons[m_itemIndex];

	UItemManager* itemM = nullptr;
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		itemM = gameInstance->SafeGetItemManager();
	}
	changeWeapon(id);
}
void UPandaWidgt_ChangeWeapon::createMath()
{
	FActorSpawnParameters fasp;
	fasp.Name = TEXT("ac");
	FVector Location;
	FRotator  Rotation;
	Location.X = -9060;
	Location.Y = 10690;
	Location.Z = 640;

	AStaticMeshActor* ac = GWorld->SpawnActor<AStaticMeshActor>(Location,Rotation,fasp);

	APlayerCharacter* wanjia = Cast<AMainPlayerController>(UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance()))->GetMainPlayer();
	//ac->GetRootComponent()->AttachTo(wanjia->GetRootComponent());
	ac->K2_AttachRootComponentTo(wanjia->GetRootComponent(),TEXT("aaaaaa"), EAttachLocation::SnapToTarget);

	UObject* asset =  UPandaUtils::CreateAsset(FString("/Game/Environment/Meshes/Bricks/SM_Cave_Brick_01a.SM_Cave_Brick_01a"));
	UStaticMesh* StaticMesh = CastChecked<UStaticMesh>(asset);

	UStaticMeshComponent* StaticMeshComponent = ac->GetStaticMeshComponent();
	check(StaticMeshComponent);
	StaticMeshComponent->UnregisterComponent();
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	// Init Component
	StaticMeshComponent->RegisterComponent();



	//ac->SetOwner(UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance()));
}