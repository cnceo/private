// Fill out your copyright notice in the Description page of Project Settings.
//
//  PADataBaseInterface.h
//  Panda
//  
//  Created by White.tian on 16-5-5.
//  Copyright (c) 2016Äê White.tian All rights reserved.
//

#pragma once
#include "NetworkingFwd.h"
#include "PADataBaseInterface.generated.h"

/**
* 
*/
namespace proto3 {
	class UserHeroBaseData;
	class MonsterHeroBaseData;
};

UINTERFACE()
class PANDA_API UPADataBaseInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PANDA_API IPADataBaseInterface
{
	GENERATED_IINTERFACE_BODY()

//public:

	//UFUNCTION(BlueprintNativeEvent)
	//void InitServerData(int32 nServerTag);
	//
	//UFUNCTION(BlueprintNativeEvent)
	//void InitClientData();

	//UFUNCTION(BlueprintNativeEvent)
	//void Init(float fTime, FName AnimName);
};