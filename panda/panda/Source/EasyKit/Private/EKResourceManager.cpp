

#include "EasyKit.h"
#include "AssetData.h"
#include "GameFramework/Actor.h"
#include "EKGameFrame.h"
#include "EKSceneManager.h"
#include "Factory/EasyKit_ActorFactory.h"
#include "EKResourceManager.h"

//IMPLEMENT_CLASS(UEKResourceManager)


UEKResourceManager::UEKResourceManager(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// ��ʼ��
	init();
}

UPackage* UEKResourceManager::LoadResource(FString inPath)
{
	UPackage* Package = LoadPackage(NULL, *inPath, LOAD_None);

	return Package;
}

void UEKResourceManager::init()
{
	// ����һ��Acotr����ʵ��������
	for (TObjectIterator<UClass> ObjectIt; ObjectIt; ++ObjectIt)
	{
		UClass* TestClass = *ObjectIt;
		if (TestClass->IsChildOf(UEasyKit_ActorFactory::StaticClass()))
		{
			if (!TestClass->HasAnyClassFlags(CLASS_Abstract))
			{
				UEasyKit_ActorFactory* NewFactory = ConstructObject<UEasyKit_ActorFactory>(TestClass);
				check(NewFactory);
				m_ActorFactories.Add(NewFactory);
			}
		}
	}
}

AActor* UEKResourceManager::Instance(UObject* inAsset)
{
	FVector vect = FVector(0, 0, 0);
	FRotator rortoat = FRotator(0, 0, 0);
	return Instance(inAsset, vect, rortoat);
}

AActor* UEKResourceManager::Instance(UObject* inAsset, FVector& inVect, FRotator& inRotat)
{
	const FAssetData AssetData(inAsset);
	FText UnusedErrorMessage;
	AActor* Actor = NULL;

	// �������й������Դ���Actor
	for (int32 FactoryIdx = 0; FactoryIdx < m_ActorFactories.Num(); FactoryIdx++)
	{
		UEasyKit_ActorFactory* ActorFactory = m_ActorFactories[FactoryIdx];

		//������Actor���Դ���ʹ���������
		if (ActorFactory->CanCreateActorFrom(AssetData, UnusedErrorMessage))
		{
			AActor* NewActorTemplate = ActorFactory->GetDefaultActor(inAsset);
			if (!NewActorTemplate)
			{
				return NULL;
			}

			const FRotator SurfaceOrientation(inRotat);
			const FRotator* const Rotation = &SurfaceOrientation;
			// ����
			Actor = ActorFactory->CreateActor(inAsset, GWorld->GetCurrentLevel(), inVect, Rotation, RF_Transient, "");
		}
	}

	return Actor;
}


void UEKResourceManager::InstancePackag(UPackage* inPackag, FVector& inVect, FRotator& inRotat)
{
	// �õ�ȫ������
	TArray<UObject*> Objects;
	GetObjectsWithOuter(inPackag, Objects);

	if (Objects.Num() > 0)
	{
		// ����ȫ������
		for (UObject* Child : Objects)
		{
			Instance(Child, inVect, inRotat);
		}
	}
}

void UEKResourceManager::InstanceAllObjcet(TArray<UObject*> inObjects, FVector& inVect, FRotator& inRotat)
{
	if (inObjects.Num() > 0)
	{
		for (UObject* Child : inObjects)
		{
			Instance(Child, inVect, inRotat);
		}
	}
}

UObject * UEKResourceManager::GetEKObject(const FString & fsPath)
{
	FStringAssetReference ref = fsPath;
	UObject* uoTmp = ref.ResolveObject();
	if (uoTmp == nullptr)
	{
		UE_LOG(LogScript, Warning, TEXT("EK Resource Manager: SynchronousLoad %s"), *fsPath);
		FStreamableManager EKAssetLoader;

		uoTmp = EKAssetLoader.SynchronousLoad(ref);
	}
	return uoTmp;
}

UBlueprintGeneratedClass * UEKResourceManager::GetEKBlueprintClass(const FString & fsPath)
{
	FStringAssetReference ref = fsPath;
	UObject* uoTmp = ref.ResolveObject();
	if (uoTmp == nullptr)
	{
		UE_LOG(LogScript, Warning, TEXT("EK Resource Manager: SynchronousLoad %s"), *fsPath);
		FStreamableManager EKAssetLoader;

		uoTmp = EKAssetLoader.SynchronousLoad(ref);
	}
	return Cast<UBlueprintGeneratedClass>(uoTmp);
}



