

#pragma once

#include "EasyKit_ActorFactorySkeletalMesh.h"
#include "EK_ActorFactoryAnimationAsset.generated.h"

/**
 * 
 */
UCLASS()
class UEK_ActorFactoryAnimationAsset : public UEasyKit_ActorFactorySkeletalMesh
{
	GENERATED_UCLASS_BODY()

protected:
	// Begin UActorFactory Interface
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;
	virtual void PostCreateBlueprint(UObject* Asset, AActor* CDO) override;
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	// End UActorFactory Interface

	virtual USkeletalMesh* GetSkeletalMeshFromAsset(UObject* Asset) const override;
};
