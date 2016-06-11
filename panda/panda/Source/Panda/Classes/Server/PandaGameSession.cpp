// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaGameSession.h"
#include "Server/PandaSpawnHelper.h"
#include "Engine.h"

FString APandaGameSession::ApproveLogin(const FString& Options){
	AGameSession::ApproveLogin(Options);

	//add some verify here
	auto udid=UGameplayStatics::ParseOption(Options,"udid");
	auto name=UGameplayStatics::ParseOption(Options,"name");
//	auto gi=Cast<UGameEngine>(GEngine)->GameInstance;
//	UE_LOG(LogTemp,Warning,TEXT("--------localplayers=%d, name=%s, udid=%s"),gi->GetNumLocalPlayers(),*name,*udid);

	FString Result(TEXT("hello Kunfu Panda, you are cute!blablabla"));
	auto md5String=FMD5::HashAnsiString(*Result);

	return TEXT("");
}

void APandaGameSession::PostLogin(APlayerController* PC){
	if(PC&&PC->GetPawn()){
		auto pawn=PC->GetPawn();
		auto world=pawn->GetWorld();
		if(spawnHelper&&world){
			//reposition players
			FVector pos=pawn->GetActorLocation();
			UE_LOG(LogTemp,Warning,TEXT("--------client login at %s"),*pos.ToString());

			if(spawnHelper->spawnArray.Num()>0){
				//prefer array first
				pos=spawnHelper->spawnArray[0]->GetActorLocation();
				spawnHelper->spawnArray.RemoveAt(0);
			}else if(spawnHelper->spawnPoint){
				//then spawn point
				pos=spawnHelper->spawnPoint->GetActorLocation();
			}

			//check collission and resposition
			TArray<FHitResult> Hits;
			FCollisionQueryParams QueryParams(TEXT("SphereTraceMulti"),false);
			while(world->SweepMultiByObjectType(Hits,pos,pos+FVector(spawnHelper->spawnGap,0,0),FQuat::Identity,FCollisionObjectQueryParams(ECC_Pawn),
				FCollisionShape::MakeSphere(spawnHelper->spawnGap),QueryParams)){
				pos+=FVector(spawnHelper->spawnGap,0,0);
			}
			pawn->SetActorLocation(pos);

			pos=pawn->GetActorLocation();
			UE_LOG(LogTemp,Warning,TEXT("--------client relocate to %s"),*pos.ToString());
		}
	}
}

void APandaGameSession::NotifyLogout(const APlayerController* PC){
	UE_LOG(LogTemp,Warning,TEXT("--------client logout"));
}
