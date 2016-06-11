

#pragma once

#include "EasyKit_ActorFactory.h"
#include "EasyKit_ActorFactoryStaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class UEasyKit_ActorFactoryStaticMesh : public UEasyKit_ActorFactory
{
	GENERATED_UCLASS_BODY()

	// Begin UActorFactory Interface
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;
	virtual void PostCreateBlueprint(UObject* Asset, AActor* CDO) override;
	virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;
	// End UActorFactory Interface
};
