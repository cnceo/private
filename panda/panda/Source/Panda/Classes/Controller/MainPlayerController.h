// Fill out your copyright notice in the Description page of Project Settings.
//add by yang 主角控制. 按键优先级处理:技能连招 > 组合热键 > NPC交互 > UI呼出 > 默认设置.
#pragma once
#include "CommonDefine.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS(HideDropdown)
class PANDA_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayerController();
	~AMainPlayerController();
	
	void BeginPlayingState();

public:
	UFUNCTION(BlueprintCallable, Category = "AMainPlayerController")
	APlayerCharacter* GetMainPlayer();

public:
	// Test Version KeyDown Deal
	// 打开物品栏测试
	void OnBagOpen();
	void OnBagClose();
	void OnTab();

	// 组队界面
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnOpenTeam();
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void onCloseTeam();
	// 副本界面
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnOpenACT();
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnCloseACT();
	// 选择区域界面
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnOpenSelectRegion();
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnCloseSelectRegion();

	//普攻 【PS4 ○】【PC J】
	void OnQuan();
	void OnQuanClick();
	void OnQuanEnd();
	void OnQuanRepeat();

	//特殊攻击/触发事件 【PS4 ×】【PC K】
	void OnCha();
	void OnChaEnd();

	//跳跃【PS4 □】【PC G】
	void OnFangKuai();
	void OnFangKuaiEnd();

	//防御【PS4 △】【PC H】
	void OnSanJiao();
	void OnSanJiaoEnd();

	//防御【PS4 L1】【PC T】
	void OnL1();
	void OnL1End();

	//锁定追击【PS4 R1】【PC Y】
	void OnR1();
	void OnR1End();

	//锁定【PS4 L2】【PC U】
	void OnL2();
	void OnL2End();

	//防御【PS4 R2】【PC I】
	void OnR2();
	void OnR2End();

	//【PS4 ↑】【PC Z】
	void OnShang();
	void OnShangEnd();

	//【PS4 ↓】【PC X】
	void OnXia();
	void OnXiaEnd();

	//【PS4 ←】【PC C】
	void OnZuo();
	void OnZuoEnd();

	//【PS4 →】【PC V】
	void OnYou();
	void OnYouEnd();

	//行走左右【PS4 L3_X轴】【PC AD】
	void OnL3X(float Value);

	//行走前后【PS4 L3_Y轴】【PC WS】
	void OnL3Y(float Value);

	//视角左右【PS4 R3_X】【PC ←→】
	void OnR3X(float Rate);

	//视角上下【PS4 R3_Y】【PC ↑↓】
	void OnR3Y(float Rate);

public:

private:

	//主角
	APlayerCharacter* m_pPlayer;

	//移动回调代理句柄
	FTimerHandle m_MoveHandle;

	//移动状态回调方法
	void MovedCallback();

	//组合按键封装
	bool m_arrbPressedKey[PLAYER_KEY::PLAYER_KEY_MAX];

	//按键按下抬起
	bool OnPressedKey(PLAYER_KEY emCurKey,bool bPressed);

	//组合键判定
	bool CheckComponentKey();

	//判断是否触发技能连招
	bool CheckNextSkill(PLAYER_KEY emCurKey);

	//临时变量，
	bool m_iscamera;
};
