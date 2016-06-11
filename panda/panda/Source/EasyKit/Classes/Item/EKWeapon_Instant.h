//
// EKWeapon_Instant.h
//
// 所有武器实例基类
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "EKWeapon.h"
#include "EKWeapon_Instant.generated.h"

/**
*
*/
UCLASS(Abstract)
class EASYKIT_API AEKWeapon_Instant : public AEKWeapon
{
	GENERATED_UCLASS_BODY()


	/** [local] weapon specific fire implementation */
	virtual void FireWeapon() override;
};