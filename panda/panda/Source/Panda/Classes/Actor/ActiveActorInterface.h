//add by yang
#pragma once
#include "CommonDefine.h"
#include "PASkillData.h"
#include "ActiveActorInterface.generated.h"

UINTERFACE()
class PANDA_API UActiveActorInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PANDA_API IActiveActorInterface
{
	GENERATED_IINTERFACE_BODY()
public:

	// Anim every frame tick and record the notify single time
	UFUNCTION(BlueprintNativeEvent)
	void OnAnimTick(float fTime, const FString& AnimName);

	// Anim begin and record the notify total time, only used to record notify total time 
	// fTime = fTotalTime
	UFUNCTION(BlueprintNativeEvent)
	void OnAnimBegin(float fTime, const FString& AnimName);

	// Anim end
	UFUNCTION(BlueprintNativeEvent)
	void OnAnimEnd(const FString& AnimName);

	// be skill hit 
	UFUNCTION(BlueprintNativeEvent)
	void OnHit(AActor* HitCauser, FsSkillHitResult sHitResult);

	//UFUNCTION(BlueprintNativeEvent)
	//void ShowCollision(CHARACTER_COLLISION_TYPE emCollType);

	//UFUNCTION(BlueprintNativeEvent)
	//void HideCollision(CHARACTER_COLLISION_TYPE emCollType);

};