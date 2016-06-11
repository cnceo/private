// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"

#include "SlateBasics.h"
#include "MoviePlayer.h"

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!


#include "EasyKit_ActorFactory.h"
#include "EasyKit_ActorFactoryStaticMesh.h"
#include "EasyKit_ActorFactorySkeletalMesh.h"
#include "EK_ActorFactoryAnimationAsset.h"
#include "EasyKit_ActorFactoryEmitter.h"

#include "AssetData.h"
#include "AssetRegistryModule.h"

#include "ParticleDefinitions.h"
#include "Particles/Emitter.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Animation/Skeleton.h"
#include "Animation/SkeletalMeshActor.h"
#include "Animation/VertexAnim/VertexAnimation.h"

#include "SoundDefinitions.h"
#include "BlueprintUtilities.h"



DEFINE_LOG_CATEGORY_STATIC(LogActorFactory, Log, All);

#define LOCTEXT_NAMESPACE "EKActorFactory"


/*-----------------------------------------------------------------------------
UEasyKit_ActorFactory
-----------------------------------------------------------------------------*/
UEasyKit_ActorFactory::UEasyKit_ActorFactory(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("DefaultName", "Actor");
	bShowInEditorQuickMenu = false;
}

bool UEasyKit_ActorFactory::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	// By Default we assume the factory can't work with existing asset data
	return !AssetData.IsValid() ||
		AssetData.ObjectPath == FName(*GetDefaultActor(AssetData)->GetPathName()) ||
		AssetData.ObjectPath == FName(*GetDefaultActor(AssetData)->GetClass()->GetPathName());
}

AActor* UEasyKit_ActorFactory::GetDefaultActor(const FAssetData& AssetData)
{
	if (NewActorClassName != TEXT(""))
	{
		UE_LOG(LogActorFactory, Log, TEXT("Loading ActorFactory Class %s"), *NewActorClassName);
		NewActorClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *NewActorClassName, NULL, LOAD_NoWarn, NULL));
		NewActorClassName = TEXT("");
		if (NewActorClass == NULL)
		{
			UE_LOG(LogActorFactory, Log, TEXT("ActorFactory Class LOAD FAILED"));
		}
	}
	return NewActorClass ? NewActorClass->GetDefaultObject<AActor>() : NULL;
}

UClass* UEasyKit_ActorFactory::GetDefaultActorClass(const FAssetData& AssetData)
{
	if (!NewActorClass)
	{
		GetDefaultActor(AssetData);
	}

	return NewActorClass;
}

UObject* UEasyKit_ActorFactory::GetAssetFromActorInstance(AActor* ActorInstance)
{
	return NULL;
}

AActor* UEasyKit_ActorFactory::CreateActor(UObject* Asset, ULevel* InLevel, const FVector& Location, const FRotator* const Rotation, EObjectFlags ObjectFlags, const FName Name)
{
	AActor* DefaultActor = GetDefaultActor(FAssetData(Asset));

	FVector SpawnLocation = Location + SpawnPositionOffset;
	FRotator SpawnRotation = Rotation ? *Rotation : DefaultActor ? DefaultActor->GetActorRotation() : FRotator::ZeroRotator;
	AActor* NewActor = NULL;
	if (PreSpawnActor(Asset, SpawnLocation, SpawnRotation, Rotation != NULL))
	{
		NewActor = SpawnActor(Asset, InLevel, SpawnLocation, SpawnRotation, ObjectFlags, Name);

		if (NewActor)
		{
			PostSpawnActor(Asset, NewActor);
		}
	}

	return NewActor;
}

bool UEasyKit_ActorFactory::PreSpawnActor(UObject* Asset, FVector& InOutLocation, FRotator& InOutRotation, bool bRotationWasSupplied)
{
	// Subclasses may implement this to set up a spawn or to adjust the spawn location or rotation.
	return true;
}

AActor* UEasyKit_ActorFactory::SpawnActor(UObject* Asset, ULevel* InLevel, const FVector& Location, const FRotator& Rotation, EObjectFlags ObjectFlags, const FName& Name)
{
	AActor* DefaultActor = GetDefaultActor(FAssetData(Asset));
	if (DefaultActor)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.OverrideLevel = InLevel;
		SpawnInfo.ObjectFlags = ObjectFlags;
		SpawnInfo.Name = Name;
		return InLevel->OwningWorld->SpawnActor(DefaultActor->GetClass(), &Location, &Rotation, SpawnInfo);
	}

	return NULL;
}

void UEasyKit_ActorFactory::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	// Subclasses may implement this to modify the actor after it has been spawned
}

void UEasyKit_ActorFactory::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	// Override this in derived actor factories to initialize the blueprint's CDO based on the asset assigned to the factory!
}

/*-----------------------------------------------------------------------------
UActorFactoryStaticMesh
-----------------------------------------------------------------------------*/
UEasyKit_ActorFactoryStaticMesh::UEasyKit_ActorFactoryStaticMesh(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("StaticMeshDisplayName", "Static Mesh");
	NewActorClass = AStaticMeshActor::StaticClass();
}

bool UEasyKit_ActorFactoryStaticMesh::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (!AssetData.IsValid() || !AssetData.GetClass()->IsChildOf(UStaticMesh::StaticClass()))
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoStaticMesh", "A valid static mesh must be specified.");
		return false;
	}

	return true;
}

void UEasyKit_ActorFactoryStaticMesh::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	UStaticMesh* StaticMesh = CastChecked<UStaticMesh>(Asset);

	UE_LOG(LogActorFactory, Log, TEXT("Actor Factory created %s"), *StaticMesh->GetName());

	// Change properties
	AStaticMeshActor* StaticMeshActor = CastChecked<AStaticMeshActor>(NewActor);
	UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
	check(StaticMeshComponent);

	StaticMeshComponent->UnregisterComponent();

	StaticMeshComponent->StaticMesh = StaticMesh;

	// Init Component
	StaticMeshComponent->RegisterComponent();
}

UObject* UEasyKit_ActorFactoryStaticMesh::GetAssetFromActorInstance(AActor* Instance)
{
	check(Instance->IsA(NewActorClass));
	AStaticMeshActor* SMA = CastChecked<AStaticMeshActor>(Instance);

	check(SMA->GetStaticMeshComponent());
	return SMA->GetStaticMeshComponent()->StaticMesh;
}

void UEasyKit_ActorFactoryStaticMesh::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	UStaticMesh* StaticMesh = CastChecked<UStaticMesh>(Asset);
	AStaticMeshActor* StaticMeshActor = CastChecked<AStaticMeshActor>(CDO);
	UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();

	StaticMeshComponent->StaticMesh = StaticMesh;
	//StaticMeshComponent->StaticMeshDerivedDataKey = StaticMesh->RenderData->DerivedDataKey;
}


/*-----------------------------------------------------------------------------
UActorFactorySkeletalMesh
-----------------------------------------------------------------------------*/
UEasyKit_ActorFactorySkeletalMesh::UEasyKit_ActorFactorySkeletalMesh(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("SkeletalMeshDisplayName", "Skeletal Mesh");
	NewActorClass = ASkeletalMeshActor::StaticClass();
}

bool UEasyKit_ActorFactorySkeletalMesh::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (!AssetData.IsValid() ||
		(!AssetData.GetClass()->IsChildOf(USkeletalMesh::StaticClass()) &&
		!AssetData.GetClass()->IsChildOf(UAnimBlueprint::StaticClass()) &&
		!AssetData.GetClass()->IsChildOf(USkeleton::StaticClass())))
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoAnimSeq", "A valid anim sequence must be specified.");
		return false;
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	FAssetData SkeletalMeshData;

	if (AssetData.GetClass()->IsChildOf(USkeletalMesh::StaticClass()))
	{
		SkeletalMeshData = AssetData;
	}

	if (!SkeletalMeshData.IsValid() && AssetData.GetClass()->IsChildOf(UAnimBlueprint::StaticClass()))
	{
		const FString* TargetSkeletonPath = AssetData.TagsAndValues.Find(TEXT("TargetSkeleton"));
		if (TargetSkeletonPath == NULL || TargetSkeletonPath->IsEmpty())
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoTargetSkeleton", "UAnimBlueprints must have a valid Target Skeleton.");
			return false;
		}

		FAssetData TargetSkeleton = AssetRegistry.GetAssetByObjectPath(**TargetSkeletonPath);
		if (!TargetSkeleton.IsValid())
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoTargetSkeleton", "UAnimBlueprints must have a valid Target Skeleton.");
			return false;
		}

		// skeleton should be loaded by this time. If not, we have problem
		// so I'm changing this to load directly not using tags and values
		USkeleton * Skeleton = Cast<USkeleton>(TargetSkeleton.GetAsset());
		if (Skeleton)
		{
			//USkeletalMesh * PreviewMesh = Skeleton->GetPreviewMesh(true);
			//if (PreviewMesh)
			//{
			//	return true;
			//}
			//else
			//{
			//	OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoPreviewSkeletalMesh", "The Target Skeleton of the UAnimBlueprint must have a valid Preview Skeletal Mesh.");
			//	return false;
			//}
		}
		else
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoTargetSkeleton", "UAnimBlueprints must have a valid Target Skeleton.");
		}
	}

	if (!SkeletalMeshData.IsValid() && AssetData.GetClass()->IsChildOf(USkeleton::StaticClass()))
	{
		// so I'm changing this to load directly not using tags and values
		USkeleton * Skeleton = Cast<USkeleton>(AssetData.GetAsset());
		if (Skeleton)
		{
			//USkeletalMesh * PreviewMesh = Skeleton->GetPreviewMesh(true);
			//if (PreviewMesh)
			//{
			//	return true;
			//}
			//else
			//{
			//	OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoPreviewSkeletalMesh", "The Target Skeleton of the UAnimBlueprint must have a valid Preview Skeletal Mesh.");
			//	return false;
			//}
		}
		else
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoTargetSkeleton", "SkeletalMesh must have a valid Target Skeleton.");
		}
	}

	if (!SkeletalMeshData.IsValid())
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoSkeletalMeshAss", "No valid skeletal mesh was found associated with the animation sequence.");
		return false;
	}

	//// Check to see if it's actually a DestructibleMesh, in which case we won't use this factory
	//if (SkeletalMeshData.GetClass()->IsChildOf(UDestructibleMesh::StaticClass()))
	//{
	//	OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoDestructibleMesh", "The animation sequence must not have a DestructibleMesh associated with it.");
	//	return false;
	//}

	return true;
}

USkeletalMesh* UEasyKit_ActorFactorySkeletalMesh::GetSkeletalMeshFromAsset(UObject* Asset) const
{
	USkeletalMesh*SkeletalMesh = Cast<USkeletalMesh>(Asset);

	check(SkeletalMesh != NULL);
	return SkeletalMesh;
}

void UEasyKit_ActorFactorySkeletalMesh::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	USkeletalMesh* SkeletalMesh = GetSkeletalMeshFromAsset(Asset);
	UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(Asset);
	ASkeletalMeshActor* NewSMActor = CastChecked<ASkeletalMeshActor>(NewActor);

	// Term Component
	NewSMActor->GetSkeletalMeshComponent()->UnregisterComponent();

	// Change properties
	NewSMActor->GetSkeletalMeshComponent()->SkeletalMesh = SkeletalMesh;
	if (NewSMActor->GetWorld()->IsGameWorld())
	{
		NewSMActor->ReplicatedMesh = SkeletalMesh;
	}

	// Init Component
	NewSMActor->GetSkeletalMeshComponent()->RegisterComponent();
	if (AnimBlueprint)
	{
		// 4.3.0 BY 
		//NewSMActor->SkeletalMeshComponent->SetAnimClass(AnimBlueprint->GeneratedClass);
	}
}

void UEasyKit_ActorFactorySkeletalMesh::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	USkeletalMesh* SkeletalMesh = GetSkeletalMeshFromAsset(Asset);
	UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(Asset);

	ASkeletalMeshActor* SkeletalMeshActor = CastChecked<ASkeletalMeshActor>(CDO);
	SkeletalMeshActor->GetSkeletalMeshComponent()->SkeletalMesh = SkeletalMesh;
	SkeletalMeshActor->GetSkeletalMeshComponent()->AnimClass = AnimBlueprint ? Cast<UAnimBlueprintGeneratedClass>(AnimBlueprint->GeneratedClass) : NULL;
}



/*-----------------------------------------------------------------------------
UActorFactoryEmitter
-----------------------------------------------------------------------------*/
UEasyKit_ActorFactoryEmitter::UEasyKit_ActorFactoryEmitter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("EmitterDisplayName", "Emitter");
	NewActorClass = AEmitter::StaticClass();
}

bool UEasyKit_ActorFactoryEmitter::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (!AssetData.IsValid() || !AssetData.GetClass()->IsChildOf(UParticleSystem::StaticClass()))
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoParticleSystem", "A valid particle system must be specified.");
		return false;
	}

	return true;
}

void UEasyKit_ActorFactoryEmitter::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	UParticleSystem* ParticleSystem = CastChecked<UParticleSystem>(Asset);
	AEmitter* NewEmitter = CastChecked<AEmitter>(NewActor);

	// Term Component
	NewEmitter->GetParticleSystemComponent()->UnregisterComponent();

	// Change properties
	NewEmitter->SetTemplate(ParticleSystem);

	// if we're created by Kismet on the server during gameplay, we need to replicate the emitter
	if (GWorld->HasBegunPlay() && GWorld->GetNetMode() != NM_Client)
	{
		NewEmitter->SetReplicates(true);
		NewEmitter->bAlwaysRelevant = true;
		NewEmitter->NetUpdateFrequency = 0.1f; // could also set bNetTemporary but LD might further trigger it or something
		// call into gameplay code with template so it can set up replication
		NewEmitter->SetTemplate(ParticleSystem);
	}

	// Init Component
	NewEmitter->GetParticleSystemComponent()->RegisterComponent();
}

UObject* UEasyKit_ActorFactoryEmitter::GetAssetFromActorInstance(AActor* Instance)
{
	check(Instance->IsA(NewActorClass));
	AEmitter* Emitter = CastChecked<AEmitter>(Instance);
	return Emitter->GetParticleSystemComponent();
}

void UEasyKit_ActorFactoryEmitter::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	UParticleSystem* ParticleSystem = CastChecked<UParticleSystem>(Asset);
	AEmitter* Emitter = CastChecked<AEmitter>(CDO);
	Emitter->SetTemplate(ParticleSystem);
}


/*-----------------------------------------------------------------------------
UActorFactoryAnimationAsset
-----------------------------------------------------------------------------*/
UEK_ActorFactoryAnimationAsset::UEK_ActorFactoryAnimationAsset(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("SingleAnimSkeletalDisplayName", "Single Animation Skeletal");
	NewActorClass = ASkeletalMeshActor::StaticClass();
}

bool UEK_ActorFactoryAnimationAsset::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (!AssetData.IsValid() ||
		(!AssetData.GetClass()->IsChildOf(UAnimSequence::StaticClass()) &&
		!AssetData.GetClass()->IsChildOf(UVertexAnimation::StaticClass())))
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoAnimData", "A valid anim data must be specified.");
		return false;
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	if (AssetData.GetClass()->IsChildOf(UAnimSequence::StaticClass()))
	{
		const FString* SkeletonPath = AssetData.TagsAndValues.Find("Skeleton");
		if (SkeletonPath == NULL || SkeletonPath->IsEmpty())
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoSkeleton", "UAnimationAssets must have a valid Skeleton.");
			return false;
		}

		FAssetData SkeletonData = AssetRegistry.GetAssetByObjectPath(**SkeletonPath);

		if (!SkeletonData.IsValid())
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoSkeleton", "UAnimationAssets must have a valid Skeleton.");
			return false;
		}

		// skeleton should be loaded by this time. If not, we have problem
		// so I'm changing this to load directly not using tags and values
		USkeleton * Skeleton = Cast<USkeleton>(SkeletonData.GetAsset());
	}

	FAssetData SkeletalMeshData;

	if (AssetData.GetClass()->IsChildOf(UVertexAnimation::StaticClass()))
	{
		const FString* BaseSkeletalMeshPath = AssetData.TagsAndValues.Find(TEXT("BaseSkelMesh"));
		if (BaseSkeletalMeshPath == NULL || BaseSkeletalMeshPath->IsEmpty())
		{
			OutErrorMsg = NSLOCTEXT("CanCreateActor", "UVertexAnimationNoSkeleton", "UVertexAnimations must have a valid base skeletal mesh.");
			return false;
		}

		SkeletalMeshData = AssetRegistry.GetAssetByObjectPath(**BaseSkeletalMeshPath);
	}

	if (!SkeletalMeshData.IsValid())
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoSkeletalMeshAss", "No valid skeletal mesh was found associated with the animation sequence.");
		return false;
	}

	//// Check to see if it's actually a DestructibleMesh, in which case we won't use this factory
	//if (SkeletalMeshData.GetClass()->IsChildOf(UDestructibleMesh::StaticClass()))
	//{
	//	OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoDestructibleMesh", "The animation sequence must not have a DestructibleMesh associated with it.");
	//	return false;
	//}

	return true;
}

USkeletalMesh* UEK_ActorFactoryAnimationAsset::GetSkeletalMeshFromAsset(UObject* Asset) const
{
	USkeletalMesh* SkeletalMesh = NULL;
	UAnimSequence* AnimationAsset = Cast<UAnimSequence>(Asset);
	UVertexAnimation* VertexAnimation = Cast<UVertexAnimation>(Asset);


	//// Check to see if it's actually a DestructibleMesh, in which case we won't use this factory
	//if (SkeletalMesh != NULL && SkeletalMesh->IsA(UDestructibleMesh::StaticClass()))
	//{
	//	SkeletalMesh = NULL;
	//}

	//check(SkeletalMesh != NULL);
	return SkeletalMesh;
}

void UEK_ActorFactoryAnimationAsset::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	Super::PostSpawnActor(Asset, NewActor);
	UAnimationAsset* AnimationAsset = Cast<UAnimationAsset>(Asset);
	UVertexAnimation* VertexAnimation = Cast<UVertexAnimation>(Asset);

	ASkeletalMeshActor* NewSMActor = CastChecked<ASkeletalMeshActor>(NewActor);
	USkeletalMeshComponent* NewSASComponent = (NewSMActor->GetSkeletalMeshComponent());

	if (NewSASComponent)
	{
		if (AnimationAsset)
		{
			NewSASComponent->SetAnimationMode(EAnimationMode::Type::AnimationSingleNode);
			NewSASComponent->AnimationData.AnimToPlay = AnimationAsset;
			// set runtime data
			NewSASComponent->SetAnimation(AnimationAsset);
		}
		else if (VertexAnimation)
		{
			NewSASComponent->SetAnimationMode(EAnimationMode::Type::AnimationSingleNode);
			NewSASComponent->AnimationData.VertexAnimToPlay = VertexAnimation;

			// set runtime data
			NewSASComponent->SetVertexAnimation(VertexAnimation);
		}
	}
}

void UEK_ActorFactoryAnimationAsset::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	Super::PostCreateBlueprint(Asset, CDO);
	UAnimationAsset* AnimationAsset = Cast<UAnimationAsset>(Asset);
	UVertexAnimation* VertexAnimation = Cast<UVertexAnimation>(Asset);

	ASkeletalMeshActor* SkeletalMeshActor = CastChecked<ASkeletalMeshActor>(CDO);
	USkeletalMeshComponent* SkeletalComponent = (SkeletalMeshActor->GetSkeletalMeshComponent());
	if (AnimationAsset)
	{
		SkeletalComponent->SetAnimationMode(EAnimationMode::Type::AnimationSingleNode);
		SkeletalComponent->SetAnimation(AnimationAsset);
	}
	else if (VertexAnimation)
	{
		SkeletalComponent->SetAnimationMode(EAnimationMode::Type::AnimationSingleNode);
		SkeletalComponent->SetVertexAnimation(VertexAnimation);
	}
}


#undef LOCTEXT_NAMESPACE
