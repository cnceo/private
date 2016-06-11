#pragma once
#include "CommonDefine.h"
#include "pAItemData.generated.h"

UENUM()
enum emItemType
{
	em_ItemType_None ,//錯誤的道具
	em_ItemType_Item , //普通道具
	em_ItemType_equip//装备
	
};
UENUM()
enum emEquipType
{
	em_EquipType_None,//错误
	em_EquipType_weapon, //武器
};
USTRUCT(BlueprintType)
struct PANDA_API FsPAItemData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAItemData")
	FString name;		// 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAItemData")
	TEnumAsByte<enum emItemType>  itemType;		// 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAItemData")
	FString icon;				// 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAItemData")
	FString describe;			//

	FsPAItemData()
	{
		itemType = emItemType::em_ItemType_None;
	}
};
