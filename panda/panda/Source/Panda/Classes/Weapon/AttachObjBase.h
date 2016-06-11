// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CommonDefine.h"
#include "AttachObjBase.generated.h"




UCLASS(Blueprintable)
class PANDA_API AAttachObjBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UCapsuleComponent* m_CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class USkeletalMeshComponent* m_MeshComp;
	//
	UPROPERTY(Category = "AAttachObjBase", EditDefaultsOnly, BlueprintReadWrite)
	FName m_SocketName;

public:
	// Sets default values for this actor's properties
	AAttachObjBase();

	//If CapsuleComponent hit Actor 
	UFUNCTION()
	virtual void OnHit( AActor* OtherActor,  UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnBeginOverlap( AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION(BlueprintCallable, Category = "Sprite")
	virtual void Attach2Pawn(AActor* actor , USkeletalMeshComponent* mesh, FName SocketName = TEXT(""));

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;



};
