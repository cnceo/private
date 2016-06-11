

#pragma once

#include "EasyKit_ActorFactory.h"
#include "EasyKit_ActorFactorySkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class UEasyKit_ActorFactorySkeletalMesh : public UEasyKit_ActorFactory
{
	GENERATED_UCLASS_BODY()

protected:
	// Begin UActorFactory Interface
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;
	virtual void PostCreateBlueprint(UObject* Asset, AActor* CDO) override;
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	// End UActorFactory Interface

	virtual USkeletalMesh* GetSkeletalMeshFromAsset(UObject* Asset) const;
};
