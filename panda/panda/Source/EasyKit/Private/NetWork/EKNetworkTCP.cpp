// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"

#include "EKNetworkTCP.h"
#include "EKNetworkBaes.h"
//#include "Net/ClientSocket.h"
//#include "Net/SocketContext.h"
//#include "Foundation/Others.h"
//#include "CommonProcessor.h"



#define IP "10.235.2.211" 
#define PORT 9002

#define ZHUREN_IP "10.235.2.35"
#define ZHUREN_PORT 5002

#define YANMENG_IP "10.235.6.67"
#define YANMENG_PORT 9002
#define YANMENG_PORT2 5003

#define KINGSOFT_IP "42.62.42.166"
#define KINGSOFT_PORT 9002


//using namespace xsjme;

// ��̬��ʼ��
//xsjme::ClientSocket* FEKNetworkTCP::m_iSocket = NULL;
//
//// ����
//FEKNetworkTCP::FEKNetworkTCP()
//{
//	m_iSocket = NULL;
//}
//
//bool FEKNetworkTCP::Init()
//{
//	// 1. ����
//	m_iSocket = new xsjme::ClientSocket();
//
//#ifdef PLATFORM_WINDOWS
//
//	// 2. �������� �� �Ͽ��¼�
//	m_iSocket->onConnect += [this]()
//	{
//		FEKNetworkTCP::bIsConnect = true;
//		UE_LOG(LogScript, Warning, TEXT(" Connect Succeed"));
//		this->ConnectSucceedDelegate.ExecuteIfBound();
//	};
//
//	m_iSocket->onDisconnect += []()
//	{
//		FEKNetworkTCP::bIsConnect = false;
//
//		// Ŀǰ����֧�ֶ�������
//		//FEKNetWorkManager::Connect();
//
//		UE_LOG(LogScript, Warning, TEXT(" Connect Lost!"));
//	};
//
//#endif
//
//
//	// 3�� ����IP�Ͷ˿�
//	m_iSocket->setIpPort(KINGSOFT_IP, PORT);
//
//	// 4. ��ʼ����ע������Э��
//	//for (int i=0; i < ProcessorArray.Num(); i++)
//	//{
//	//	ProcessorArray[i]->RegisterProtocolProcessor();
//	//}
//
//	return true;
//}
//
//void FEKNetworkTCP::SetIPPort(const char* _ip, uint16 _port)
//{
//	m_iSocket->setIpPort(_ip, _port);
//}
//
//bool FEKNetworkTCP::IsConnect()
//{
//	return m_iSocket->isConnected();
//}
//
//bool FEKNetworkTCP::Connect()
//{
//	if (FEKNetworkTCP::bUseNetwork == false)
//		return false;
//
//	// ������ ����ɹ� ���ǻ������ ���ӵ��¼�
//	if (FEKNetworkTCP::m_iSocket->open() == true)
//	{
//		UE_LOG(LogScript, Warning, TEXT(" !! NetWorkFrame Init Succeed !!  [Open]  "));
//	}
//	else
//	{
//		UE_LOG(LogScript, Warning, TEXT(" !! NetWorkFrame Init Failure !!  [Coles]  "));
//	}
//
//	//�����������׽����߳�
//	//bool isRun  = xsjme::SocketContext::getSingleton().run();
//
//	return true;
//}
//
//bool FEKNetworkTCP::SendToSever(ProtocolPacketBase& protocolSerializer, int64_t sessionId)
//{
//	//��������Ϣ��������
//	if (m_iSocket->sendMsg(protocolSerializer) == false)
//	{
//		UE_LOG(LogScript, Warning, TEXT(" !!!! Messager Send Failure !!!!  [No Send]  "));
//		return false;
//	}
//
//	UE_LOG(LogScript, Warning, TEXT(" !!!! Messager Send Succeed !!!!  [Send]  "));
//	return true;
//}
//
//
//void FEKNetworkTCP::RegisterProtocol(ushort protocolId, ProtocolProcessor func)
//{
//	//��ע��Э�鵽����ģ��
//	m_iSocket->registerProtocolProcessor(protocolId, func);
//
//	UE_LOG(LogScript, Warning, TEXT(" !!!! Socket RegisterProtocol !!!!  %d "), (int)protocolId);
//}
//
//void FEKNetworkTCP::Tick(float DeltaSeconds) 
//{
//	FEKNetworkBaes::Tick(DeltaSeconds);
//
//	// ����ģ���߳�Tick
//	if (m_iSocket)
//		m_iSocket->tick();
//}
//
