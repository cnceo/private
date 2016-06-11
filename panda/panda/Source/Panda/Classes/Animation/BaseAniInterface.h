// add by yang 基础角色类接口定义
#pragma once
#include "CommonDefine.h"
#include "BaseAniInterface.generated.h"

UINTERFACE()
class PANDA_API UBaseAniInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PANDA_API IBaseAniInterface
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
};