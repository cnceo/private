//
// EKAnimNotification.h
//
// ��Ϸ���������� ���ڼ��س��������ͼ �޷���ص�
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu, Shen Qian. All Rights Reserved. 
//

#pragma once


#include "EKAnimNotification.generated.h"


UCLASS(abstract, Blueprintable, const, hidecategories = Object, collapsecategories)
class EASYKIT_API UEKAnimNotification : public UAnimNotify
{
	GENERATED_UCLASS_BODY()

	void FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AActor* & OutActor);
	void FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AEKCharacter* & OutPawn);
};




