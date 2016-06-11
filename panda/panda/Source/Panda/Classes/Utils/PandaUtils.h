// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "PandaUtils.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API UPandaUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category = "Networking")
		static void SetUserName(FString name);	//test
	UFUNCTION(BlueprintCallable,Category = "Networking")
	static FString GetUserName();	//test

	UFUNCTION(BlueprintCallable,Category = "Networking")
	static bool EnteredZone();

	UFUNCTION(BlueprintCallable,Category = "Networking")
	static void Login();

	UFUNCTION(BlueprintCallable,Category = "Networking")
	static void EnterArena(int32 aid);
	
	//get all characters include Monsters, Boss and Players, please Cast your self
	UFUNCTION(BlueprintCallable,Category = "Utils")
	static TArray<ABaseCharacter*>GetWorldCharacters(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable,Category = "Utils")
	static APlayerController* GetLocalPlayerController(UObject* WorldContextObject);

	/**
	* Sets the global time dilation.
	* @param	TimeDilation	value to set the global time dilation to
	*/
	UFUNCTION(BlueprintCallable,Category = "Utils")
	static void	SlowCamera(UObject* WorldContextObject, float TimeDilation = 0.2);

	/**
	* Sets the game's paused state
	* @param	bPaused		Whether the game should be paused or not
	* @return	Whether the game was successfully paused/unpaused
	*/
	UFUNCTION(BlueprintCallable,Category = "Utils")
	static bool	PauseGame(UObject* WorldContextObject, bool bPaused = true);

	UFUNCTION(BlueprintCallable,Category = "Utils")
	static void	CameraShake(UObject* WorldContextObject, TSubclassOf<class UCameraShake> Shake, float Scale = 1.f, ECameraAnimPlaySpace::Type PlaySpace = ECameraAnimPlaySpace::CameraLocal, FRotator UserPlaySpaceRot = FRotator::ZeroRotator);
	
	/**
	* Dynamic_create BP
	* Created by zhangpeng
	* Modify by white.tian 2016/4/20
	*/
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static UBlueprintGeneratedClass* GetAssetFromPath(FString AssetPath);

	/*template<typename ClassName>
	static ClassName* CreateAsset(FString AssetPath);*/
	/* Create Asset*/
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static UObject* CreateAsset(FString AssetPath);

	/**
	* get relatively angle.
	* @param	direction
	* @param	distance
	*/
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static float VectorAngle(FVector direction, FVector distance);
	
	// adjust roation
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static void ChangeRoation(AActor *pTarget, AActor *pSelf);

	/*
	*	Puase AI
	*   fPauseTime: pause time
	*	ControlledActor: Get Your Pawn Controller
	*/
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static void PauseAI(float fPauseTime, AActor* ControlledActor, UObject* WorldContextObject);

	//加载本地资源
	template<typename CurrentClass>
	static CurrentClass* LoadResource(FString strPath);

	//把一个枚举定义转换成2进制位表示的10进制数
	static int32 TransformEnumToBit(int32 param);
};
