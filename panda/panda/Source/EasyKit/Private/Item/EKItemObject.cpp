

#include "EasyKit.h"
#include "EKItemObject.h"


AEKItemObject::AEKItemObject(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// ������ ����²������Tick�¼���
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

