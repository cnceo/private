

#pragma once

#include "EasyKit_ActorFactory.h"
#include "EasyKit_ActorFactoryEmitter.generated.h"

/**
 * 
 */
UCLASS()
class UEasyKit_ActorFactoryEmitter : public UEasyKit_ActorFactory
{
	GENERATED_UCLASS_BODY()

	// Begin UActorFactory Interface
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;
	virtual void PostCreateBlueprint(UObject* Asset, AActor* CDO) override;
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;
	// End UActorFactory Interface
};
