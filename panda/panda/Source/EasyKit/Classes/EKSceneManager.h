//
// EKSceneManager.h
//
// ��Ϸ���������� ���ڼ��س��������ͼ �޷���ص�
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
		int64_t guid;      // ʵ���Ψһid
		int32 characterID;			// ��ɫid
		int         hp;             // Ѫ��
		float dir;					// ����
		FVector pos;                // ��������
		FString name;               // ������ƣ�npc����Ҫͬ�������
	};

	struct LeaveViewSyncData
	{
		int64_t guid;               // ʵ���Ψһid
	};

	struct LocationSyncData
	{
		int64_t guid;               // ʵ���Ψһid
		FVector pos;
	};

	struct PlayerMoveData
	{
		char result;
		FVector pos;
	};

}


/**
* ����������
*/
class EASYKIT_API FEKSceneManager
{

public:

	FEKSceneManager();

	// Init 
	void Init();

	// ���ص�ͼ
	bool LoadMap(FName inMapName);
	//void LoadMap(const FString inMapName);
	void LoadMap(const FString inMapName, FName inCallbackTarget);
	void LoadMap(const FString inMapName, FLatentActionInfo& inActionInfo);

	// ���ص�ͼ
	bool LoadMapToNetWorke(FName inMapName, FString& host, int32 port);

	// ����World  ����Ҫ�кܶ� ���ܶ���Ҫ�õ�world
	UWorld* GetWorld() const;
	void SetWorld(UWorld* inWorld);
	void LoadWorld(const FString& inMapName);

	// ����Level ֻ���л���ͼʱ�����õ�ǰLevel
	void SetCurrentLevel(class Ulevel* inLevel);

	void Tick(float DeltaSeconds);

	// ���һ��Actor������
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
	 * ���� ��ǰ��һ������ �����Ƶ�Pawn
	 *
	 * @param	inPawn		�µ�Pawn������ 
	 */
	bool ChangePossessedPawn(APawn *inPawn);

	/**
	 * ���� ��ǰ��һ������ �� �µĿ�����������ԭ����Pawn
	 * ����Ҫʹ����spawn������
	 *
	 * @param	playerControllerClass		�µĿ��������������
	 * @return	�����µĿ�����
	 */
	APlayerController* ChangeController(TSubclassOf<class APlayerController> playerControllerClass);

	/**
	 * ���� ��ǰ��һ������ �� �µĿ�����������ԭ����Pawn
	 * ��Ҫʹ����spawn������
	 *
	 * @param	newPC		�µĿ�����������
	 */
	void ChangeController(APlayerController *newPC);

	/**
	 * ���� ��ǰ��һ������ ��������������ӽǣ�
	 * ����������ǰ���ӽ�
	 *
	 * @param	NewViewTarget		�����������ӽǵ�Actor���������CameraComponent����ô����CameraComponentΪ�ӽ�
	 * @param	BlendTime			�ӽ��л�����Ҫʱ��
	 * @param	BlendFunc			�ӽ��л��ķ��̣����������ԣ�������
	 * @param	BlendExp			�ӽ��л���ָ��������ĳЩ�л�����
	 * @param	bLockOutgoing		������棿
	 */
	bool ChangeViewTarget(class AActor* NewViewTarget, float BlendTime = 0, enum EViewTargetBlendFunction BlendFunc = VTBlend_Linear, float BlendExp = 0, bool bLockOutgoing = false);

};
