
#include "EasyKit.h"
#include "EKAnimNotifyState.h"



UEKAnimNotifyState::UEKAnimNotifyState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UEKAnimNotifyState::FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AActor* & OutActor)
{
	OutActor = MeshComp->GetTypedOuter<AActor>();
}

void UEKAnimNotifyState::FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AEKCharacter* & OutPawn)
{
	OutPawn = MeshComp->GetTypedOuter<AEKCharacter>();
}
