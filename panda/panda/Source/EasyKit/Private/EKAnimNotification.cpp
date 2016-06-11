
#include "EasyKit.h"
#include "EKAnimNotification.h"



UEKAnimNotification::UEKAnimNotification(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UEKAnimNotification::FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AActor* & OutActor)
{
	OutActor = MeshComp->GetTypedOuter<AActor>();
}

void UEKAnimNotification::FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AEKCharacter* & OutPawn)
{
	OutPawn = MeshComp->GetTypedOuter<AEKCharacter>();
}
