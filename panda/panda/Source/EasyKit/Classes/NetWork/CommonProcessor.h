//
// CommonProcessor.h
//
// 所以协议的基类主要用作设计模式
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

	// 来个纯虚函数把所有协议注册到 管理器中
	virtual void RegisterProtocolProcessor(FString) = 0;
};