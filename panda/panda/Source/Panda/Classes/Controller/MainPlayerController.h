// Fill out your copyright notice in the Description page of Project Settings.
//add by yang ���ǿ���. �������ȼ�����:�������� > ����ȼ� > NPC���� > UI���� > Ĭ������.
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
	// ����Ʒ������
	void OnBagOpen();
	void OnBagClose();
	void OnTab();

	// ��ӽ���
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnOpenTeam();
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void onCloseTeam();
	// ��������
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnOpenACT();
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnCloseACT();
	// ѡ���������
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnOpenSelectRegion();
	UFUNCTION(BlueprintCallable, Category = CreateTeam)
	void OnCloseSelectRegion();

	//�չ� ��PS4 �𡿡�PC J��
	void OnQuan();
	void OnQuanClick();
	void OnQuanEnd();
	void OnQuanRepeat();

	//���⹥��/�����¼� ��PS4 ������PC K��
	void OnCha();
	void OnChaEnd();

	//��Ծ��PS4 ������PC G��
	void OnFangKuai();
	void OnFangKuaiEnd();

	//������PS4 ������PC H��
	void OnSanJiao();
	void OnSanJiaoEnd();

	//������PS4 L1����PC T��
	void OnL1();
	void OnL1End();

	//����׷����PS4 R1����PC Y��
	void OnR1();
	void OnR1End();

	//������PS4 L2����PC U��
	void OnL2();
	void OnL2End();

	//������PS4 R2����PC I��
	void OnR2();
	void OnR2End();

	//��PS4 ������PC Z��
	void OnShang();
	void OnShangEnd();

	//��PS4 ������PC X��
	void OnXia();
	void OnXiaEnd();

	//��PS4 ������PC C��
	void OnZuo();
	void OnZuoEnd();

	//��PS4 ������PC V��
	void OnYou();
	void OnYouEnd();

	//�������ҡ�PS4 L3_X�᡿��PC AD��
	void OnL3X(float Value);

	//����ǰ��PS4 L3_Y�᡿��PC WS��
	void OnL3Y(float Value);

	//�ӽ����ҡ�PS4 R3_X����PC ������
	void OnR3X(float Rate);

	//�ӽ����¡�PS4 R3_Y����PC ������
	void OnR3Y(float Rate);

public:

private:

	//����
	APlayerCharacter* m_pPlayer;

	//�ƶ��ص�������
	FTimerHandle m_MoveHandle;

	//�ƶ�״̬�ص�����
	void MovedCallback();

	//��ϰ�����װ
	bool m_arrbPressedKey[PLAYER_KEY::PLAYER_KEY_MAX];

	//��������̧��
	bool OnPressedKey(PLAYER_KEY emCurKey,bool bPressed);

	//��ϼ��ж�
	bool CheckComponentKey();

	//�ж��Ƿ񴥷���������
	bool CheckNextSkill(PLAYER_KEY emCurKey);

	//��ʱ������
	bool m_iscamera;
};
