//
// CommonProcessor.h
//
// ����Э��Ļ�����Ҫ�������ģʽ
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//


#pragma once

#include "Foundation/Platform.h"
#include "Net/Session.h"



class FProcessor
{
public:

	// �������麯��������Э��ע�ᵽ ��������
	virtual void RegisterProtocolProcessor(FString) = 0;
};