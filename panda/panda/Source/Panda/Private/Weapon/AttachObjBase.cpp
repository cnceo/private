// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "AttachObjBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine.h"
//class UWorld;


// Sets default values
AAttachObjBase::AAttachObjBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//GWorld()->SpawnActor()
	
	m_MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	if (m_MeshComp)
	{
		//m_MeshComp->AttachParent = m_CapsuleComponent;
		m_MeshComp->AlwaysLoadOnClient = true;
		m_MeshComp->AlwaysLoadOnServer = true;
		m_MeshComp->bOwnerNoSee = false;
		m_MeshComp->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		m_MeshComp->bCastDynamicShadow = true;
		m_MeshComp->bAffectDynamicIndirectLighting = true;
		m_MeshComp->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		m_MeshComp->bGenerateOverlapEvents = false;
//		m_MeshComp->bCanEverAffectNavigation = false;
	}

//	m_StaticMeshComp = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
//	if (m_MeshComp && m_StaticMeshComp)
//	{
//		m_StaticMeshComp->AttachParent = m_MeshComp;
//		m_StaticMeshComp->AlwaysLoadOnClient = true;
//		m_StaticMeshComp->AlwaysLoadOnServer = true;
//		m_StaticMeshComp->bOwnerNoSee = false;
//		m_StaticMeshComp->bCastDynamicShadow = true;
//		m_StaticMeshComp->bAffectDynamicIndirectLighting = true;
//		m_StaticMeshComp->PrimaryComponentTick.TickGroup = TG_PrePhysics;
//		m_MeshComp->bGenerateOverlapEvents = false;
////		m_MeshComp->bCanEverAffectNavigation = false;
//	}

	m_CapsuleComponent = CreateOptionalDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	if (m_CapsuleComponent)
	{
		m_CapsuleComponent->bGenerateOverlapEvents = true;
		m_CapsuleComponent->AttachParent = m_MeshComp;
		m_CapsuleComponent->OnComponentHit.AddDynamic(this,&AAttachObjBase::OnHit);
		m_CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AAttachObjBase::OnBeginOverlap);
	}

}

void AAttachObjBase::OnHit( AActor* OtherActor,  UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GetWorld()->GetGameInstance()->GetEngine()->AddOnScreenDebugMessage(-1,2.f,FColor::Red,OtherActor->GetName());

}

void AAttachObjBase::OnBeginOverlap( AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GetWorld()->GetGameInstance()->GetEngine()->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, OtherActor->GetName());
}

void AAttachObjBase::Attach2Pawn(AActor* actor, USkeletalMeshComponent * mesh,FName SocketName)
{
	check(mesh);

	if (SocketName == TEXT(""))
	{
		SocketName = m_SocketName;
	}
	
	USkeletalMeshSocket const* Socket = mesh->GetSocketByName(m_SocketName);
	
	//FTransform SocketLocalTransform = Socket->GetSocketLocalTransform();
	if(Socket)
	{
		GetRootComponent()->AttachTo(mesh, Socket->SocketName, EAttachLocation::SnapToTarget);
		this->SetOwner(actor);
	}
	
}

// Called when the game starts or when spawned
void AAttachObjBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAttachObjBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

