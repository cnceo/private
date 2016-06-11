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

	/** 下一步 */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void SelectNextProgress();

	/** 上一步 */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void SelectUpProgress();

	/** R1 */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void CheckR1();

	/** L1 */
	UFUNCTION(BlueprintCallable, Category = SelectChar)
	virtual void CheckL1();

	/** R1键 */
	void R1Button();
	/** L1键*/
	void L1Button();

	// 初始化 选人场景所有数据
	void InitSelectCharScene();
private:

	// 当前选择的进度
	SelectProgress CurrentSelectProgress;
	// 上次选择的进度
	SelectProgress LastSelectProgress;
	void ChangeSelectProgress(SelectProgress inProfession);

//////////////////////////////////////////////////////////////////////////
	// 初始化选择种族的界面
	bool InitSeleRace();
	// 改变选择角色
	void ChangeSelectChar(int inIndex);
	// 放弃选择的角色
	void DiscardSeletChar();
	// 初始化角色名字
	void InitRaceName();
	// 初始化角色描述
	void InitRaceDescribe();
	// 初始化角色天赋技能表
	void InitRaceSkillList();

	// 当前选择中的角色的索引
	int CurrentSelectCharIndex;
	// 上次选择的角色索引
	int LastSelectCharIndex;

	// 当前可选角色列表
	TArray<class ASelectCharacterBase*>  SelectCharList;

	TArray<class FRace*> SelectRaceList;
	class FRace* CurrentSelectRace;

	//////////////////////////////////////////////////////////////////////////
	//UMG
	// 种族描述
	UTextBlock* RaceDescribe;
	// 种族名字
	UTextBlock* RaceName;
	// 天赋技能列表
	UVerticalBox* TalentSkillList;

//////////////////////////////////////////////////////////////////////////
	// 初始化选择职业的界面
	bool InitSeleProfession();
	// 改变选择职业
	void ChangeSelectProfession(int InIndex);
	// 初始化职业名字
	void InitProfessionName();
	// 初始化职业描述
	void InitProfessionDescribe();
	// 初始化角色职业技能表
	void InitProfessionSkillList();
	// 初始化角色职业技能的动画片展示
	void InitProfessionSkillMovie();
	// 初始化角色职业属性图表
	void InitProfessionProperty();

	// 当前选择中的角色的索引
	int CurrentSelectProfessionIndex;
	// 上次选择的角色索引
	int LastSelectProfessionIndex;

	TArray<class FProfession*> SelectProfessionList;

	class FProfession* CurrentSelectProfession;
	//////////////////////////////////////////////////////////////////////////
	//UMG
	// 种族描述
	UTextBlock* ProfessionDescribe;
	// 种族名字
	UTextBlock* ProfessionName;
	// 天赋技能列表
	UVerticalBox* ProfessionSkillList;
	// 技能展示图片
	UImage* ProfessionSkilLMovie;
	// 职业属性面板
	UCanvasPanel* ProfessionPropertyPanel;


//////////////////////////////////////////////////////////////////////////
	//UMG
	TMap<FString, class UCanvasPanel*> CeratePanelList;


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// 临时
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
