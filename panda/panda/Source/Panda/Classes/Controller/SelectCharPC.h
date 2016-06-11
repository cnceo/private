// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkingFwd.h"
#include "Components/CanvasPanel.h"
#include "GameFramework/PlayerController.h"
#include "SelectCharPC.generated.h"

class FFProfessionSkill
{
public:
	FString SkillName;
	FString SkillIocnPaht;
	FString SkillVideo;
};

class FProfession
{
public:
	FString ProfessionName;
	FString ProfessionDescribe;

	int Liliang;
	int Minjie;
	int Tili;
	int Zhili;
	int Fangyu;

	TArray<FFProfessionSkill*> ProfessionSkillList;
};

class FRaceSkill
{
public:
	FString SkillName;
	FString SkillIocnPaht;
};

class FRace
{
public:
	FString RaceName;
	FString RaceDescribe;

	TArray<FRaceSkill*> RaceSkillList;
};

UENUM()
enum SelectProgress
{
	Select_One = 0,
	Select_Two,
	Select_Three,
	Select_Four,
};
/**
 * 
 */
UCLASS()
class PANDA_API ASelectCharPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASelectCharPC();
	~ASelectCharPC();

	/** Event when play begins for this actor. */
	virtual void BeginPlay();
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent();

//////////////////////////////////////////////////////////////////////////
	/** Login Select Char HUD */
	UFUNCTION(BlueprintCallable, Category = Login)
	virtual void LoginEnter();

	void NetLogin(class proto3::MsgZCEnter& imsg);

	/** Select Char Break Logine */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void BreakLogine();
	/** Select Char Enter Game */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void EnterGame();
	/** Select Char Enter Game */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void EnterNetGame(FString& host, int32 port);

	/** Select Char CreatChar */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void Create();

	/** Create Char Break SelecetChar */
	UFUNCTION(BlueprintCallable, Category = CreateChar)
	virtual void BreakSelecetChar();
	/** Create Char CreateRole */
	UFUNCTION(BlueprintCallable, Category = CreateChar)
	virtual void CreateRole();

//////////////////////////////////////////////////////////////////////////

	/** ��һ�� */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void SelectNextProgress();

	/** ��һ�� */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void SelectUpProgress();

	/** R1 */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void CheckR1();

	/** L1 */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void CheckL1();

	/** R1�� */
	void R1Button();
	/** L1��*/
	void L1Button();

	// ��ʼ�� ѡ�˳�����������
	void InitSelectCharScene();
private:

	// ��ǰѡ��Ľ���
	SelectProgress CurrentSelectProgress;
	// �ϴ�ѡ��Ľ���
	SelectProgress LastSelectProgress;
	void ChangeSelectProgress(SelectProgress inProfession);

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��ѡ������Ľ���
	bool InitSeleRace();
	// �ı�ѡ���ɫ
	void ChangeSelectChar(int inIndex);
	// ����ѡ��Ľ�ɫ
	void DiscardSeletChar();
	// ��ʼ����ɫ����
	void InitRaceName();
	// ��ʼ����ɫ����
	void InitRaceDescribe();
	// ��ʼ����ɫ�츳���ܱ�
	void InitRaceSkillList();

	// ��ǰѡ���еĽ�ɫ������
	int CurrentSelectCharIndex;
	// �ϴ�ѡ��Ľ�ɫ����
	int LastSelectCharIndex;

	// ��ǰ��ѡ��ɫ�б�
	TArray<class ASelectCharacterBase*>  SelectCharList;

	TArray<class FRace*> SelectRaceList;
	class FRace* CurrentSelectRace;

	//////////////////////////////////////////////////////////////////////////
	//UMG
	// ��������
	UTextBlock* RaceDescribe;
	// ��������
	UTextBlock* RaceName;
	// �츳�����б�
	UVerticalBox* TalentSkillList;

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��ѡ��ְҵ�Ľ���
	bool InitSeleProfession();
	// �ı�ѡ��ְҵ
	void ChangeSelectProfession(int InIndex);
	// ��ʼ��ְҵ����
	void InitProfessionName();
	// ��ʼ��ְҵ����
	void InitProfessionDescribe();
	// ��ʼ����ɫְҵ���ܱ�
	void InitProfessionSkillList();
	// ��ʼ����ɫְҵ���ܵĶ���Ƭչʾ
	void InitProfessionSkillMovie();
	// ��ʼ����ɫְҵ����ͼ��
	void InitProfessionProperty();

	// ��ǰѡ���еĽ�ɫ������
	int CurrentSelectProfessionIndex;
	// �ϴ�ѡ��Ľ�ɫ����
	int LastSelectProfessionIndex;

	TArray<class FProfession*> SelectProfessionList;

	class FProfession* CurrentSelectProfession;
	//////////////////////////////////////////////////////////////////////////
	//UMG
	// ��������
	UTextBlock* ProfessionDescribe;
	// ��������
	UTextBlock* ProfessionName;
	// �츳�����б�
	UVerticalBox* ProfessionSkillList;
	// ����չʾͼƬ
	UImage* ProfessionSkilLMovie;
	// ְҵ�������
	UCanvasPanel* ProfessionPropertyPanel;


//////////////////////////////////////////////////////////////////////////
	//UMG
	TMap<FString, class UCanvasPanel*> CeratePanelList;


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// ��ʱ
public:

	UFUNCTION(BlueprintCallable, Category = Login)
	bool InitProvisionalScene(UWidget* inOne, UWidget* inTwo, UWidget* inThree, UWidget* outOne, UWidget* outTwo, UWidget* outThree);

	void ChangeProvisionalChar();

	UWidget* One;
	UWidget* Two;
	UWidget* Three;
	UWidget* nOne;
	UWidget* nTwo;
	UWidget* nThree;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
};
