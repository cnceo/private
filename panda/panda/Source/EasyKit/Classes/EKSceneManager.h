//
// EKSceneManager.h
//
// 游戏场景管理器 用于加载场景管理地图 无缝加载等
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu, Shen Qian. All Rights Reserved. 
//

#pragma once


#include "Object.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <stack>
#include "Player/EKCharacter.h"
#include "Item/EKWeapon.h"
#define PANDA_MAP_PATH_NAME_PRE "/Game/Maps/1/"
#define PANDA_MAP_PATH_NAME_CAT "_"
#define PANDA_MAP_MIN 0
#define PANDA_MAP_MAX 9

namespace PackagePath
{
	const FString MapPath = "/Game/Maps/";
}

namespace EKSceneManagerStruct
{
	struct EnterViewSyncData
	{
		int64_t guid;      // 实体的唯一id
		int32 characterID;			// 角色id
		int         hp;             // 血量
		float dir;					// 方向
		FVector pos;                // 世界坐标
		FString name;               // 玩家名称（npc不需要同步这个）
	};

	struct LeaveViewSyncData
	{
		int64_t guid;               // 实体的唯一id
	};

	struct LocationSyncData
	{
		int64_t guid;               // 实体的唯一id
		FVector pos;
	};

	struct PlayerMoveData
	{
		char result;
		FVector pos;
	};

}


/**
* 场景管理器
*/
class EASYKIT_API FEKSceneManager
{

public:

	FEKSceneManager();

	// Init 
	void Init();

	// 加载地图
	bool LoadMap(FName inMapName);
	//void LoadMap(const FString inMapName);
	void LoadMap(const FString inMapName, FName inCallbackTarget);
	void LoadMap(const FString inMapName, FLatentActionInfo& inActionInfo);

	// 加载地图
	bool LoadMapToNetWorke(FName inMapName, FString& host, int32 port);

	// 设置World  很重要有很多 功能都需要得到world
	UWorld* GetWorld() const;
	void SetWorld(UWorld* inWorld);
	void LoadWorld(const FString& inMapName);

	// 设置Level 只有切换地图时才设置当前Level
	void SetCurrentLevel(class Ulevel* inLevel);

	void Tick(float DeltaSeconds);

	// 添加一个Actor到场景
	void AddActorToMap(class AActor* inActor);

	void SetCurActor(AActor * aActor);

	// Async load & unload map
	void AsyncLoadMap(const FString & inMapName);
	void AsyncLoadMap(const FString & inMapName, FName inCallbackTarget);
	void AsyncLoadMap(const FString & inMapName, FLatentActionInfo& inActionInfo);

	void AsyncUnLoadMap(const FString & inMapName);
	void AsyncUnLoadMap(const FString & inMapName, FLatentActionInfo& inActionInfo);

private:

	UWorld* m_World;
	class Ulevel* M_CurrentLevel;
	AActor* aCurActor;

	class AEKCharacter* m_pLocalPlayer;
	class APlayerController* m_Controller;

	std::string sInLevel;
	std::string sCurrentInMap;
	std::vector<std::string> vInMaps;
	bool bTimer;
	const float fChangeMapOffSetTime;
	bool bChangeMapInterval;
	std::string sChangingMapName;
	const float fChangeMapIntervalTime;
	std::string sRequiredUnloadMapName;
	bool bChangeMapInProcess;
	bool bChangeMapDuringChanging;

	// Check if need load maps in tick func
	void AsynLoadMapCheck();

	// Calculate which maps are close to the center map
	void CalculateAdjacentMaps(const std::string &, std::vector<std::string> &);

	void CalculateMapName(std::string &, const std::string &);

	void StoreMapFullName(int32, int32, std::vector<std::string> &);

	void UnloadNotRequiredMaps(std::vector<std::string> &, std::vector<std::string> &);

	void LoadRequiredMaps(std::vector<std::string> &, std::vector<std::string> &);

	void ChangeMapTimerReach();

	void ChangeMapIntervalTimerReach();

	bool CheckMapIsInMapContainers(const std::string &, const std::vector<std::string> &);

public:

	std::stack<AEKCharacter*> botPool;

	std::unordered_map<int64_t, AEKCharacter*> liveCharacterPool;

	void ServerExecEnterView(const std::vector<EKSceneManagerStruct::EnterViewSyncData> &);

	void ServerExecLeaveView(const std::vector<EKSceneManagerStruct::LeaveViewSyncData> &);

	void ServerExecLocationSync(const std::vector<EKSceneManagerStruct::LocationSyncData> &);

	void ServerExecPlayerMove(const EKSceneManagerStruct::PlayerMoveData &);

	AEKCharacter* ServerExecGetPawn(int64_t);

	void TestMovement();

	void SetLocalPlayer(class AEKCharacter* inPlayer);

	class AEKCharacter* GetLocalPlayer();

	void SetController(class APlayerController* inController);

	class APlayerController* GetController();

	// Set loading screen used for next loading.
	void CreateLoadingScreen();

public:

	/**
	 * 更换 当前第一控制器 所控制的Pawn
	 *
	 * @param	inPawn		新的Pawn的引用 
	 */
	bool ChangePossessedPawn(APawn *inPawn);

	/**
	 * 更换 当前第一控制器 至 新的控制器，保留原来的Pawn
	 * 不需要使用者spawn控制器
	 *
	 * @param	playerControllerClass		新的控制器的类的引用
	 * @return	返回新的控制器
	 */
	APlayerController* ChangeController(TSubclassOf<class APlayerController> playerControllerClass);

	/**
	 * 更换 当前第一控制器 至 新的控制器，保留原来的Pawn
	 * 需要使用者spawn控制器
	 *
	 * @param	newPC		新的控制器的引用
	 */
	void ChangeController(APlayerController *newPC);

	/**
	 * 更换 当前第一控制器 所包含的摄像机视角，
	 * 即，更换当前主视角
	 *
	 * @param	NewViewTarget		用来当成新视角的Actor，如果包含CameraComponent，那么就用CameraComponent为视角
	 * @param	BlendTime			视角切换所需要时间
	 * @param	BlendFunc			视角切换的方程，可以是线性，渐进等
	 * @param	BlendExp			视角切换的指数，用于某些切换方程
	 * @param	bLockOutgoing		如果是真？
	 */
	bool ChangeViewTarget(class AActor* NewViewTarget, float BlendTime = 0, enum EViewTargetBlendFunction BlendFunc = VTBlend_Linear, float BlendExp = 0, bool bLockOutgoing = false);

};
