// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaUtils.h"
#include "Engine.h"
#include "BaseCharacter.h"
#include <Engine/GameEngine.h>
#include "Networking/NetworkingFwd.h"
#include "BaseAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

using namespace proto3;

APlayerController* UPandaUtils::GetLocalPlayerController(UObject* WorldContextObject){
	if(!GEngine)return nullptr;
	APlayerController* LocalPlayerController=nullptr;
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!World)
	{
		return nullptr;
	}
	for(FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = *Iterator;
		if(Cast<UNetConnection>(PlayerController->Player) != NULL)
		{
			// remote player
		}
		else
		{
			// local player
			LocalPlayerController=PlayerController;
		}
	}
	return LocalPlayerController;
}

TArray<ABaseCharacter*>	UPandaUtils::GetWorldCharacters(UObject* WorldContextObject){
	TArray<ABaseCharacter*> arr;
	if(WorldContextObject)for(auto it=WorldContextObject->GetWorld()->GetPawnIterator();it;++it){
		if(auto pawn=(*it)){
			if(auto p=Cast<ABaseCharacter>(pawn))
				arr.Add(p);
		}
	}
	return arr;
}


void UPandaUtils::SlowCamera(UObject* WorldContextObject, float TimeDilation)
{
	UGameplayStatics::SetGlobalTimeDilation(WorldContextObject, TimeDilation);
}

bool UPandaUtils::PauseGame(UObject* WorldContextObject, bool bPaused)
{
	return UGameplayStatics::SetGamePaused(WorldContextObject, bPaused);
}

void UPandaUtils::CameraShake(UObject* WorldContextObject, TSubclassOf<class UCameraShake> Shake, float Scale, 
	ECameraAnimPlaySpace::Type PlaySpace, FRotator UserPlaySpaceRot)
{
	
}

UBlueprintGeneratedClass* UPandaUtils::GetAssetFromPath(FString AssetPath)
{
	UBlueprintGeneratedClass* ParentClass = nullptr;
	FStringAssetReference ref = AssetPath;
	UObject* uoTmp = ref.ResolveObject();
	if (uoTmp == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("GetAssetFromPath path = %s"), *AssetPath);
		FStreamableManager EKAssetLoader;
		uoTmp = EKAssetLoader.SynchronousLoad(ref);
	}
	ParentClass = Cast<UBlueprintGeneratedClass>(uoTmp);

	return ParentClass;
}

UObject* UPandaUtils::CreateAsset(FString AssetPath)
{
	FStringAssetReference ref = AssetPath;
	UObject* uoTmp = ref.ResolveObject();
	if (uoTmp == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("CreateAsset path = %s"), *AssetPath);
		FStreamableManager EKAssetLoader;
		uoTmp = EKAssetLoader.SynchronousLoad(ref);
	}

	return uoTmp;
}

float UPandaUtils::VectorAngle(FVector direction, FVector distance)
{
	FVector tempDirection = FVector(direction.X, direction.Y, 0);
	tempDirection.Normalize();
	FVector tempDistance = FVector(distance.X, distance.Y, 0);
	tempDistance.Normalize();
	float angle = FMath::Acos(FVector::DotProduct(tempDirection, tempDistance))*180.0f/3.1415926f;
	if (FVector::CrossProduct(tempDirection, tempDistance).Z < 0)
	{
		return angle;
	}
	else
	{
		return -angle;
	}
}

void UPandaUtils::ChangeRoation(AActor *pTarget, AActor *pSelf)
{
	if (!pTarget || !pSelf)
		return;
	
	FVector outFirstPos;
	FRotator outRotator;

	outFirstPos = pTarget->GetActorLocation();
	//outRotator = pTarget->GetMesh()->GetComponentQuat().Rotator();
	outRotator = pTarget->GetActorQuat().Rotator();

	outFirstPos.Z = 0;

	FRotator Rotator1 = FRotationMatrix::MakeFromX(outFirstPos - pSelf->GetActorLocation()).Rotator();
	Rotator1.Roll = 0;
	Rotator1.Pitch = 0;

	float fInterpSpeed = 200.f;
	FRotator Rotator2 = FMath::RInterpTo(pSelf->GetActorRotation(), Rotator1, 0.01, fInterpSpeed);

	pSelf->SetActorRotation(Rotator2);
}

int32 UPandaUtils::TransformEnumToBit(int32 param)
{
	if (param > 2)
	{
		int32 result = pow(2, (param - 1));
		if (result < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("function TransformEnumToBit param is overflow"));
			return 0;
		}
		else
		{
			return result;
		}
	}

	return param;
}

//#define SKIP_ZONE

//login to Gateway
void UPandaUtils::Login() {
	if(GGameInstance&&GGameInstance->pandanet){
#ifdef SKIP_ZONE
		GGameInstance->pandanet->clientZConnection.handler.bLogin=true;
		UE_LOG(LogTemp,Warning,TEXT("--------entered Zone"));
#else
		auto& h=GGameInstance->pandanet->clientGConnection.handler;
		h.keepAlive=false;
		if(h.shClient){
			h.login();
		} else{
			h.connect();
		}
#endif // SKIP_ZONE
	}
}

bool UPandaUtils::EnteredZone(){
	return (GGameInstance&&GGameInstance->pandanet?
		GGameInstance->pandanet->clientZConnection.handler.bLogin:
		false);
}

void UPandaUtils::SetUserName(FString name){
	if(GGameInstance&&GGameInstance->pandanet){
		auto str=TCHAR_TO_ANSI(*name);
		GGameInstance->pandanet->clientZConnection.handler.testName=str;
		auto udid = TCHAR_TO_ANSI(*FPlatformMisc::GetUniqueDeviceId());

		MsgCZUpdateName msg;
		msg.set_mid(eMsg::MSG_CZ_UPDATE_NAME);
		msg.set_uid(udid);
		msg.set_name(str);
		PBHelper::Send(*GGameInstance->pandanet->clientZConnection.handler.shClient,msg);
	}
}

FString UPandaUtils::GetUserName(){
	if(GGameInstance&&GGameInstance->pandanet)
		return FString(ANSI_TO_TCHAR(GGameInstance->pandanet->clientZConnection.handler.testName.c_str()));
	return FString(TEXT("unknown"));
}

void UPandaUtils::EnterArena(int32 aid) {
	if(GGameInstance&&GGameInstance->pandanet){
#ifdef SKIP_ZONE
		//mockup for eMsg::MSG_AC_ENTER
		auto key="panda";//keye::MD5::HashAnsiString("panda");
		auto& h=GGameInstance->pandanet->clientAConnection.handler;
		auto& imsg=h.EnterArena;
		imsg.set_mid(eMsg::MSG_ZC_ENTER_ARENA);
		imsg.set_key(key);
		imsg.set_level("ArenaMap");
		imsg.set_host("192.168.0.107");
		imsg.set_port(7777);

		auto& czHandler=GGameInstance->pandanet->clientZConnection.handler;
		czHandler.preEnterArena(imsg);
#else
		auto& h=GGameInstance->pandanet->clientZConnection.handler;
		if(h.shClient){
			//request arena from Zone
			MsgCZEnterArena msg;
			msg.set_mid(eMsg::MSG_CZ_ENTER_ARENA);
			msg.set_aid(aid);
			PBHelper::Send(*h.shClient,msg);
		}
#endif // SKIP_ZONE
	}
}

void UPandaUtils::PauseAI(float fPauseTime, AActor* ControlledActor, UObject* WorldContextObject)
{
	if (ControlledActor)
	{
		auto obj = UAIBlueprintHelperLibrary::GetAIController(ControlledActor);
		if (obj)
		{
			auto selfController = Cast<ABaseAIController>(obj);
			if (selfController)
			{
				selfController->pause = fPauseTime;
			}
		}
	}
	else
	{
		/*TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors*/
		UE_LOG(LogTemp, Warning, TEXT("UPandaUtils::PauseAI() don't Imple Now."));
		// no deal
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AAIController::StaticClass(), OutActors);

		for (int i = 0; i < OutActors.Num(); i++)
		{
			if (!OutActors[i])
				continue;

			auto obj = UAIBlueprintHelperLibrary::GetAIController(OutActors[i]);
			if (obj)
			{
				auto selfController = Cast<ABaseAIController>(obj);
				if (selfController)
				{
					selfController->pause = fPauseTime;
				}
			}
		}
	}
}

template<typename CurrentClass>
CurrentClass* UPandaUtils::LoadResource(FString strPath)
{
	FStringAssetReference ref = strPath;
	UObject* uoTmp = ref.ResolveObject();
	if (uoTmp == nullptr)
	{
		FStreamableManager EKAssetLoader;
		uoTmp = EKAssetLoader.SynchronousLoad(ref);
	}

	return Cast<CurrentClass>(uoTmp);

}