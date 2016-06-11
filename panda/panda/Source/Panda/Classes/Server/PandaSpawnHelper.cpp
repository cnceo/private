// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaSpawnHelper.h"
#include "Server/PandaGameSession.h"

// Sets default values
APandaSpawnHelper::APandaSpawnHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APandaSpawnHelper::BeginPlay(){
	Super::BeginPlay();
	if(GetWorld()&&GetWorld()->GetAuthGameMode()&&GetWorld()->GetAuthGameMode()->GameSession){
		auto session=Cast<APandaGameSession>(GetWorld()->GetAuthGameMode()->GameSession);
		if(session)session->spawnHelper=this;
	}
}

// Called every frame
void APandaSpawnHelper::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

