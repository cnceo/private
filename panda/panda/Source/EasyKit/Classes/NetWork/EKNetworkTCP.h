//
// FEKNetworkTCP.h
//
// 网络连接 用于客户端的通信相关业务
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

//// 必须先包含这个头文件不然会重定义 WIN基本数据类型
//// 

#include "EKNetworkBaes.h"
#include <string>


/**
* 网络连接类
*/

DECLARE_DELEGATE(FConnectSucceedDelegate);

class EASYKIT_API FEKNetworkTCP : public FEKNetworkBaes
{
//
//public:
//
//	FEKNetworkTCP();
//
//	bool Init();
//
//	FConnectSucceedDelegate ConnectSucceedDelegate;
//
//	bool Connect();
//	bool IsConnect();
//	//bool Disconnect();
//	//bool ReInit();
//	void SetIPPort(const char *, uint16);
//
//	void Tick(float DeltaSeconds);
//
//	bool SendToSever(xsjme::ProtocolPacketBase& protocolSerializer, int64_t sessionId = 0);
//
//	void RegisterProtocol(ushort protocolId, xsjme::ProtocolProcessor func);
//
//	xsjme::ClientSocket* m_iSocket;
};

