

#include "EasyKit.h"
#include "EKItemObject.h"


AEKItemObject::AEKItemObject(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// 不增加 这个事不会接收Tick事件的
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

