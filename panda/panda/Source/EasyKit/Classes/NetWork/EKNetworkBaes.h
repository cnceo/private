//
// FEKNetWorkManager.h
//
// �������ӹ����� ���ڿͻ��˵�ͨ�����ҵ��
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

// �����Ȱ������ͷ�ļ���Ȼ���ض��� WIN������������
#include "EKAllowWindowsPlatformType.h"

//#include "Net/Socket.h"
//#include "Net/ClientSocket.h"

#include <string>



namespace xsjme
{
	class ClientSocket;
	class ProtocolSerializer;
	class Session;
	struct Protocol;
}


/**
* ����������
*/
class EASYKIT_API FEKNetworkBaes
{
//
//public:
//
//	FEKNetworkBaes();
//
//	virtual bool Init() = 0;
//
//	virtual bool IsConnect(){ return true; };
//
//	virtual bool Connect() = 0;
//
//	virtual void Tick(float DeltaSeconds);
//	
//	virtual void AddProtocol(class FProcessor* inProcessor);
//
//	virtual void RegisterProtocol(ushort protocolId, xsjme::ProtocolProcessor func) = 0;
//
//	virtual bool SendToSever(xsjme::ProtocolPacketBase& protocolSerializer, int64_t sessionId = 0) = 0;
//
//	void SetNetworkUseState(bool inUse){ bUseNetwork = inUse; }
//
//	void SetIP();
//
//	void SetPort();
//
//	virtual void SetIPPort(const char *, uint16){}
//
//	static volatile bool bIsConnect;
//
//protected:
//
//	TArray<class FProcessor*> ProcessorArray;
//
//	static volatile bool bUseNetwork;
};

