//
// FEKNetworkTCP.h
//
// �������� ���ڿͻ��˵�ͨ�����ҵ��
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

//// �����Ȱ������ͷ�ļ���Ȼ���ض��� WIN������������
//// 

#include "EKNetworkBaes.h"
#include <string>


/**
* ����������
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

