//
// EKSceneManager.h
//
// 游戏场景管理器 用于加载场景管理地图 无缝加载等
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu, Shen Qian. All Rights Reserved. 
//

#pragma once


#include "EKAnimNotifyState.generated.h"


UCLASS(abstract, Blueprintable, const, hidecategories = Object, collapsecategories)
class EASYKIT_API UEKAnimNotifyState : public UAnimNotifyState
{
	GENERATED_UCLASS_BODY()


#if WITH_EDITORONLY_DATA
	/** If true, render the trail geometry (this should typically be on) */
	UPROPERTY(transient, EditAnywhere, Category = Rendering)
	uint32 bRenderGeometry : 1;

	/** If true, render stars at each spawned particle point along the trail */
	UPROPERTY(transient, EditAnywhere, Category = Rendering)
		uint32 bRenderSpawnPoints : 1;

	/** If true, render a line showing the tangent at each spawned particle point along the trail */
	UPROPERTY(transient, EditAnywhere, Category = Rendering)
		uint32 bRenderTangents : 1;

	/** If true, render the tessellated path between spawned particles */
	UPROPERTY(transient, EditAnywhere, Category = Rendering)
		uint32 bRenderTessellation : 1;
#endif // WITH_EDITORONLY_DATA


	void FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AActor* & OutActor);
	void FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AEKCharacter* & OutPawn);

};




