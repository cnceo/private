// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKNetworkBaes.h"
#include "EKNetWorkManager.h"

//
//// ����
//FEKNetWorkManager::FEKNetWorkManager() 
//{
//	NetworkArray.Empty();
//}
//
//bool FEKNetWorkManager::Init()
//{
//	// ��ʼ�� �豸���� ��������
//	return true;
//}
//
//void FEKNetWorkManager::Tick(float DeltaSeconds)
//{
//	// ����ģ���߳�Tick
//	for (auto &network : NetworkArray)
//	{
//		network.Value->Tick(DeltaSeconds);
//	}
//}
//
//// ע���µ����絽���������
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
//	// ����ģ���߳�Tick
//	for (auto &network : NetworkArray)
//	{
//		network.Value->SetNetworkUseState(isUse);
//	}
//
//	return true;
//}
