// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKNetworkBaes.h"
#include "EKNetWorkManager.h"

//
//// 构造
//FEKNetWorkManager::FEKNetWorkManager() 
//{
//	NetworkArray.Empty();
//}
//
//bool FEKNetWorkManager::Init()
//{
//	// 初始化 设备本身 网络问题
//	return true;
//}
//
//void FEKNetWorkManager::Tick(float DeltaSeconds)
//{
//	// 网络模块线程Tick
//	for (auto &network : NetworkArray)
//	{
//		network.Value->Tick(DeltaSeconds);
//	}
//}
//
//// 注册新的网络到网络管理器
//void FEKNetWorkManager::AddNetwork(class FEKNetworkBaes* inNetwork, FString inKey)
//{
//	NetworkArray.Add(inKey, inNetwork);
//}
//
//FEKNetworkBaes* FEKNetWorkManager::GetNetwork(FString inKey)
//{
//	if (!NetworkArray.Contains(inKey)) return nullptr;
//
//	return NetworkArray[inKey];
//}
//
//bool FEKNetWorkManager::SetNetworkUseState(bool isUse)
//{
//	// 网络模块线程Tick
//	for (auto &network : NetworkArray)
//	{
//		network.Value->SetNetworkUseState(isUse);
//	}
//
//	return true;
//}
