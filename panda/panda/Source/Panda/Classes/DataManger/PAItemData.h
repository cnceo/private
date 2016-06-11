#pragma once
#include "CommonDefine.h"
#include "pAItemData.generated.h"

UENUM()
enum emItemType
{
	em_ItemType_None ,//�e�`�ĵ���
	em_ItemType_Item , //��ͨ����
	em_ItemType_equip//װ��
	
};
UENUM()
enum emEquipType
{
	em_EquipType_None,//����
	em_EquipType_weapon, //����
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
