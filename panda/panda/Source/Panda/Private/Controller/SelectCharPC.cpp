// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "SelectCharPC.h"

//EK
#include "EKGameFrame.h"
#include "EKHUDManager.h"
#include "EKLogManager.h"

ASelectCharPC::ASelectCharPC()
{
	ShowCursor(true);
	bShowMouseCursor = true;
}

ASelectCharPC::~ASelectCharPC()
{

}

void ASelectCharPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input
	InputComponent->BindAction("L1", IE_Pressed, this, &ASelectCharPC::ChangeProvisionalChar);
	InputComponent->BindAction("R1", IE_Pressed, this, &ASelectCharPC::ChangeProvisionalChar);
}

void ASelectCharPC::BeginPlay()
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 登陆
/** Login Select Char HUD */
void ASelectCharPC::LoginEnter()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_SelectChar);

	//auto udid = TCHAR_TO_ANSI(*FPlatformMisc::GetUniqueDeviceId());

	//auto& h = GGameInstance->pandanet->clientZConnection.handler;
	////  创建登录协议协议
	//MsgCGLogin msg;
	//msg.set_mid(eMsg::MSG_CG_LOGIN);
	//msg.set_id(udid);
	//msg.set_account(udid);
	//msg.set_udid(udid);
	//msg.set_name("test name");
	//msg.set_clientversion(100);		//00.10.00
	//msg.set_type(AccountType::PC);
	//PBHelper::Send(*h.shClient, msg);
}

void ASelectCharPC::NetLogin(MsgZCEnter& imsg)
{

	for (int i = 0; i < imsg.playerinfo_size(); i++)
	{
		ASelectCharacterBase* play = NewObject<ASelectCharacterBase>(this);
		play->m_Info = new PlayerInfo(imsg.playerinfo(i)); 

		//play
		SelectCharList.Add(play);
	}


	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_SelectChar);
}

/** Login Select Char HUD */
void ASelectCharPC::BreakLogine()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_Login);
}

//////////////////////////////////////////////////////////////////////////
// 进入带网络的游戏
/** Select Char Enter Game */
void ASelectCharPC::EnterNetGame(FString& host, int32 port)
{
	// 副本
	//FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_World);
	// 主城
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_MainCity);
}

//////////////////////////////////////////////////////////////////////////
// 选人进入游戏
/** Select Char Enter Game */
void ASelectCharPC::EnterGame()
{
	// 副本
	//FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_World);
	// 主城
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_MainCity);
}

/** Select Char CreatChar */
void ASelectCharPC::Create()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_CreaterChar);
}

//////////////////////////////////////////////////////////////////////////
// 创建
/** Create Char Break SelecetChar */
void ASelectCharPC::BreakSelecetChar()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_SelectChar);
}

/** Create Char CreateRole */
void ASelectCharPC::CreateRole()
{
	//////////////////////////////////////////////////////////////////////////
	// 创建完成返回选人
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_SelectChar);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void ASelectCharPC::SelectNextProgress() 
{
	if(CurrentSelectProgress == Select_One)
	{ 
		CurrentSelectProgress = Select_Two;
	}
	else if (CurrentSelectProgress == Select_Two)
	{
		CurrentSelectProgress = Select_Three;
	}
	else if (CurrentSelectProgress == Select_Three)
	{
		CurrentSelectProgress = Select_Four;
	}
	else if (CurrentSelectProgress == Select_Four)
	{
		EnterGame();
		return;
	}

	ChangeSelectProgress(CurrentSelectProgress);
}

void ASelectCharPC::SelectUpProgress() 
{
	if (CurrentSelectProgress == Select_Two)
	{
		CurrentSelectProgress = Select_One;
	}
	else if (CurrentSelectProgress == Select_Three)
	{
		CurrentSelectProgress = Select_Two;
	}
	else if (CurrentSelectProgress == Select_Four)
	{
		CurrentSelectProgress = Select_Three;
		return;
	}

	ChangeSelectProgress(CurrentSelectProgress);
}

void ASelectCharPC::InitSelectCharScene()
{
	// 清空索引
	CurrentSelectCharIndex = LastSelectCharIndex = 0;
	// 清空索引
	CurrentSelectProgress = LastSelectProgress = Select_One;
	// 清空面板
	CeratePanelList.Empty();

	TArray<UWidget*> WidgetList;
	FEKGameFrame::Instance()->HUDManager()->GetCurrentWindowAllUWidget(WidgetList);

	// 遍历所有面板
	for (UWidget* Widget : WidgetList)
	{
		if (Widget->GetClass() == UCanvasPanel::StaticClass())
		{	
			// 找面板
			UCanvasPanel *CanvasPanel = nullptr;
			CanvasPanel = Cast<UCanvasPanel>(Widget);

			if (CanvasPanel->GetName() == "Panel_Main")
			{
				CanvasPanel->SetVisibility(ESlateVisibility::Visible);
				CeratePanelList.Add("Main", CanvasPanel);
			}
			else if (CanvasPanel->GetName() == "Panel_SelectOne")
			{
				CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
				CeratePanelList.Add("One", CanvasPanel);
			}
			else if (CanvasPanel->GetName() == "Panel_SelectTwo")
			{
				CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
				CeratePanelList.Add("Two", CanvasPanel);
			}
			else if (CanvasPanel->GetName() == "Panel_SelectThree")
			{
				CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
				CeratePanelList.Add("Three", CanvasPanel);
			}
			else if (CanvasPanel->GetName() == "Panel_SelectFour")
			{
				CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
				CeratePanelList.Add("Four", CanvasPanel);
			}	
		}
	}

	// 读种族

	// 读职业

	// 
}

void ASelectCharPC::ChangeSelectProgress(SelectProgress inProfession)
{
	LastSelectProgress = CurrentSelectProgress;
	CurrentSelectProgress = inProfession;

	UCanvasPanel* Panel = *CeratePanelList.Find("Main");

	// 初始化控制
	for (int i = 0; i < Panel->GetChildrenCount(); i++)
	{
		UWidget* Widget = Panel->GetChildAt(i);
		UBorder* Border = nullptr;

		if (inProfession == Select_Two)
		{
			if (Widget->GetName() == "Select_One")
			{
				Border = Cast<UBorder>(Widget);
				Border->SetRenderScale(FVector2D(1, 1));

				(*CeratePanelList.Find("One"))->SetVisibility(ESlateVisibility::Hidden);
				(*CeratePanelList.Find("Three"))->SetVisibility(ESlateVisibility::Hidden);
			}
			if (Widget->GetName() == "Select_Two")
			{
				Border = Cast<UBorder>(Widget);
				Border->SetRenderScale(FVector2D(1.2f, 1.2f));

				(*CeratePanelList.Find("Two"))->SetVisibility(ESlateVisibility::Visible);
				// 初始化种族
				InitSeleRace();
			}
		}
		else if (inProfession == Select_Three)
		{
			if (Widget->GetName() == "Select_Two")
			{
				Border = Cast<UBorder>(Widget);
				Border->SetRenderScale(FVector2D(1, 1));

				(*CeratePanelList.Find("Two"))->SetVisibility(ESlateVisibility::Hidden);
				(*CeratePanelList.Find("Four"))->SetVisibility(ESlateVisibility::Hidden);
			}
			if (Widget->GetName() == "Select_Three")
			{
				Border = Cast<UBorder>(Widget);
				Border->SetRenderScale(FVector2D(1.2f, 1.2f));

				(*CeratePanelList.Find("Three"))->SetVisibility(ESlateVisibility::Visible);
				// 初始化职业
				InitSeleProfession();
			}
		}
		else if (inProfession == Select_Four)
		{
			if (Widget->GetName() == "Select_Three")
			{
				Border = Cast<UBorder>(Widget);
				Border->SetRenderScale(FVector2D(1, 1));

				(*CeratePanelList.Find("Three"))->SetVisibility(ESlateVisibility::Hidden);
			}
			if (Widget->GetName() == "Select_Four")
			{
				Border = Cast<UBorder>(Widget);
				Border->SetRenderScale(FVector2D(1.2f, 1.2f));

				(*CeratePanelList.Find("Four"))->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

}

/** R1 */
void ASelectCharPC::CheckR1()
{
	if (CurrentSelectProgress == Select_One)
	{
		if (CurrentSelectCharIndex == 0)
		{
			CurrentSelectCharIndex += 1;
			ChangeSelectChar(CurrentSelectCharIndex);
		}
		else
		{
			CurrentSelectCharIndex += 1;
			ChangeSelectChar(CurrentSelectCharIndex);
		}
		ChangeSelectProfession(Select_Two);
	}
	else  if (CurrentSelectProgress == Select_Two)
	{
		CurrentSelectProfessionIndex += 1;
		ChangeSelectProfession(CurrentSelectProfessionIndex);
	}
}

/** L1 */
void ASelectCharPC::CheckL1()
{
	if (CurrentSelectProgress == Select_One)
	{
		if (CurrentSelectCharIndex == 0)
		{
			CurrentSelectCharIndex += 1;
			ChangeSelectChar(CurrentSelectCharIndex);
		}
		else
		{
			CurrentSelectCharIndex -= 1;
			ChangeSelectChar(CurrentSelectCharIndex);
		}
		ChangeSelectProfession(Select_Two);
	}
	else if (CurrentSelectProgress == Select_Two)
	{
		CurrentSelectProfessionIndex -= 1;
		ChangeSelectProfession(CurrentSelectProfessionIndex);
	}
}

/** R1键 */
void ASelectCharPC::R1Button() 
{
	CheckR1();
}

/** L1键*/
void ASelectCharPC::L1Button() 
{
	CheckL1();
}

// 初始化选择种族的界面
bool ASelectCharPC::InitSeleRace()
{
	FSelectCharacterTableData* Table = (FSelectCharacterTableData*)(FPandaDataPool::Instance()->GetData(DataPool::DataType::DATA_SelectChar));
	SelectRaceList = Table->GetRaceDataList();

	class UCanvasPanel* Panel = *CeratePanelList.Find("Two");

	// 初始化控制
	for (int i = 0; i < Panel->GetChildrenCount(); i++)
	{
		UWidget* Widget = Panel->GetChildAt(i);

		if (Widget->GetName() == "RaceDescribe")
		{
			RaceDescribe = Cast<UTextBlock>(Widget);
		}
		else if (Widget->GetName() == "RaceName")
		{
			RaceName = Cast<UTextBlock>(Widget);
		}
		else if (Widget->GetName() == "TalentSkillList")
		{
			TalentSkillList = Cast<UVerticalBox>(Widget);
		}
	}


	ChangeSelectChar(1);
		
	return true;
}

// 改变选择角色
void ASelectCharPC::ChangeSelectChar(int inIndex)
{
	// 设置当前选择的种族
	if (inIndex >= SelectRaceList.Num())
		inIndex = SelectRaceList.Num() - 1;

	LastSelectCharIndex = CurrentSelectCharIndex;
	CurrentSelectCharIndex = inIndex;
	CurrentSelectRace = SelectRaceList[inIndex];

	InitRaceName();
	InitRaceDescribe();
	InitRaceSkillList();
}

// 放弃选择的角色
void ASelectCharPC::DiscardSeletChar()
{
	
}

// 初始化角色名字
void ASelectCharPC::InitRaceName()
{
	if (RaceName == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find RaceName");
		return;
	}
	RaceName->Text = FText::FromString(CurrentSelectRace->RaceName);
	RaceName->SynchronizeProperties();
}

// 初始化角色描述
void ASelectCharPC::InitRaceDescribe()
{
	if (RaceDescribe == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find RaceDescribe");
		return;
	}
	RaceDescribe->Text = FText::FromString(CurrentSelectRace->RaceDescribe);
	RaceDescribe->SynchronizeProperties();
}

// 初始化角色天赋技能表
void ASelectCharPC::InitRaceSkillList()
{
	if (TalentSkillList == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find TalentSkillList");
		return;
	}

	TalentSkillList->ClearChildren();
	UVerticalBoxSlot* Gridslot = Cast<UVerticalBoxSlot>(TalentSkillList->Slot);
	if (Gridslot != nullptr)
	{
		Gridslot->HorizontalAlignment = EHorizontalAlignment(HAlign_Fill);
		Gridslot->VerticalAlignment = EVerticalAlignment(HAlign_Fill);
		Gridslot->SynchronizeProperties();
	}

	UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/CreateChar/RaceSkill.RaceSkill_C"));
	if (itemObj == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read RaceSkill BP");
		return;
	}

	for (int i = 0; i < CurrentSelectRace->RaceSkillList.Num(); i++)
	{
		FRaceSkill* Skill = CurrentSelectRace->RaceSkillList[i];

		// 创建技能
		UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);

		TArray<UWidget*> WidgetList;
		itemWidget->WidgetTree->GetAllWidgets(WidgetList);
		
		// 遍历Item下的所有控件
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetName() == "SkillIcon")
			{
				UImage *SkillImage = Cast<UImage>(Widget);
				if (SkillImage != nullptr)
				{
					// 读技能图片
					UObject *headIcon = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(Skill->SkillIocnPaht);
					// 设置按钮的图片
					SkillImage->Brush.SetResourceObject(headIcon);
				}
			}
			else if (Widget->GetName() == "SkillName")
			{
				UTextBlock *SkillName = Cast<UTextBlock>(Widget);
				if (SkillName != nullptr)
				{
					SkillName->Text = FText::FromString(Skill->SkillName);
					SkillName->SynchronizeProperties();
				}
			}
		}
		TalentSkillList->SynchronizeProperties();

		TalentSkillList->AddChild(itemWidget);
	}
	
}

bool ASelectCharPC::InitSeleProfession()
{
	FSelectCharacterTableData* Table = (FSelectCharacterTableData*)(FPandaDataPool::Instance()->GetData(DataPool::DataType::DATA_SelectChar));
	SelectProfessionList = Table->GetProfessionDataList();

	class UCanvasPanel* Panel = *CeratePanelList.Find("Three");

	// 初始化控制
	for (int i = 0; i < Panel->GetChildrenCount(); i++)
	{
		UWidget* Widget = Panel->GetChildAt(i);

		if (Widget->GetName() == "ProfessionDescribe")
		{
			ProfessionDescribe = Cast<UTextBlock>(Widget);
		}
		else if (Widget->GetName() == "ProfessionName")
		{
			ProfessionName = Cast<UTextBlock>(Widget);
		}
		else if (Widget->GetName() == "ProfessionSkillList")
		{
			ProfessionSkillList = Cast<UVerticalBox>(Widget);
		}
		else if (Widget->GetName() == "BreakSkillMovie")
		{
			ProfessionSkilLMovie = Cast<UImage>(Widget);
		}
		//else if (Widget->GetName() == "LiLangBar")
		//{
		//	LilangBar = Cast<UProgressBar>(Widget);
		//}
		//else if (Widget->GetName() == "MinJieBar")
		//{
		//	MinjieBar = Cast<UProgressBar>(Widget);
		//}
		//else if (Widget->GetName() == "ZhiHuiBar")
		//{
		//	ZhihuiBar = Cast<UProgressBar>(Widget);
		//}
	}

	ChangeSelectProfession(0);
	return true;
}

void ASelectCharPC::ChangeSelectProfession(int InIndex)
{
	LastSelectProfessionIndex = CurrentSelectProfessionIndex;
	CurrentSelectProfessionIndex = InIndex;

	CurrentSelectProfession = SelectProfessionList[InIndex];

	InitProfessionName();
	InitProfessionDescribe();
	InitProfessionSkillList();
	InitProfessionSkillMovie();
	InitProfessionProperty();
}
// 初始化职业名字
void ASelectCharPC::InitProfessionName()
{
	if (ProfessionName == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find ProfessionName");
		return;
	}
	ProfessionName->Text = FText::FromString(CurrentSelectProfession->ProfessionName);
	ProfessionName->SynchronizeProperties();
}
// 初始化职业描述
void ASelectCharPC::InitProfessionDescribe()
{
	if (ProfessionDescribe == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find ProfessionDescribe");
		return;
	}
	ProfessionDescribe->Text = FText::FromString(CurrentSelectProfession->ProfessionDescribe);
	ProfessionDescribe->SynchronizeProperties();
}
// 初始化角色职业技能表
void ASelectCharPC::InitProfessionSkillList()
{
	if (ProfessionSkillList == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find ProfessionSkillList");
		return;
	}

	ProfessionSkillList->ClearChildren();
	UVerticalBoxSlot* Gridslot = Cast<UVerticalBoxSlot>(ProfessionSkillList->Slot);
	if (Gridslot != nullptr)
	{
		Gridslot->HorizontalAlignment = EHorizontalAlignment(HAlign_Fill);
		Gridslot->VerticalAlignment = EVerticalAlignment(HAlign_Fill);
		Gridslot->SynchronizeProperties();
	}

	UObject *itemObj = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(TEXT("/Game/UI/UMG/CreateChar/ProfessionSkill.ProfessionSkill_C"));
	if (itemObj == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Read ProfessionSkill BP");
		return;
	}

	for (int i = 0; i < CurrentSelectProfession->ProfessionSkillList.Num(); i++)
	{
		FFProfessionSkill* Skill = CurrentSelectProfession->ProfessionSkillList[i];

		// 创建技能
		UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);

		TArray<UWidget*> WidgetList;
		itemWidget->WidgetTree->GetAllWidgets(WidgetList);

		// 遍历Item下的所有控件
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetName() == "SkillIcon")
			{
				UImage *SkillImage = Cast<UImage>(Widget);
				if (SkillImage != nullptr)
				{
					// 读技能图片
					UObject *headIcon = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(Skill->SkillIocnPaht);
					// 设置按钮的图片
					SkillImage->Brush.SetResourceObject(headIcon);
				}
			}
			else if (Widget->GetName() == "SkillDescribe")
			{
				UTextBlock *SkillName = Cast<UTextBlock>(Widget);
				if (SkillName != nullptr)
				{
					SkillName->Text = FText::FromString(Skill->SkillName);
					SkillName->SynchronizeProperties();
				}
			}
		}
		TalentSkillList->SynchronizeProperties();

		TalentSkillList->AddChild(itemWidget);
	}
}
// 初始化角色职业技能的动画片展示
void ASelectCharPC::InitProfessionSkillMovie()
{
	if (ProfessionSkilLMovie == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find ProfessionSkilLMovie");
		return;
	}

	//ProfessionSkilLMovie->Brush.GetResourceObject() = FText::FromString(CurrentSelectProfession->ProfessionDescribe);
	ProfessionSkilLMovie->SynchronizeProperties();
}
// 初始化角色职业属性图表
void ASelectCharPC::InitProfessionProperty()
{
	if (ProfessionPropertyPanel == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find ProfessionProperty");
		return;
	}

	// 初始化属性
	for (int i = 0; i < ProfessionPropertyPanel->GetChildrenCount(); i++)
	{
		UWidget* Widget = ProfessionPropertyPanel->GetChildAt(i);

		if (Widget->GetName() == "LiLangBar")
		{
			// 力量条
			UProgressBar* LilangBar = Cast<UProgressBar>(Widget);
			LilangBar->Percent = CurrentSelectProfession->Liliang;
			LilangBar->SynchronizeProperties();
		}
		else if (Widget->GetName() == "MinJieBar")
		{
			// 敏捷条
			UProgressBar* MinjieBar = Cast<UProgressBar>(Widget);
			MinjieBar->Percent = CurrentSelectProfession->Minjie;
			MinjieBar->SynchronizeProperties();
		}
		else if (Widget->GetName() == "ZhiHuiBar")
		{
			// 智慧
			UProgressBar* ZhihuiBar = Cast<UProgressBar>(Widget);
			ZhihuiBar->Percent = CurrentSelectProfession->Zhili;
			ZhihuiBar->SynchronizeProperties();
		}
	}

	ProfessionPropertyPanel->SynchronizeProperties();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 临时
bool ASelectCharPC::InitProvisionalScene(UWidget* inOne, UWidget* inTwo, UWidget* inThree, UWidget* outOne, UWidget* outTwo, UWidget* outThree)
{
	One = inOne;
	Two = inTwo;
	Three = inThree;

	nOne = outOne;
	nTwo = outTwo;
	nThree = outThree;

	nOne->SetVisibility(ESlateVisibility::Hidden);
	nTwo->SetVisibility(ESlateVisibility::Hidden);
	nThree->SetVisibility(ESlateVisibility::Hidden);

	return true;
}

void ASelectCharPC::ChangeProvisionalChar()
{
	if (One->GetVisibility() == ESlateVisibility::Hidden)
	{
		nOne->SetVisibility(ESlateVisibility::Hidden);
		nTwo->SetVisibility(ESlateVisibility::Hidden);
		nThree->SetVisibility(ESlateVisibility::Hidden);
		One->SetVisibility(ESlateVisibility::Visible);
		Two->SetVisibility(ESlateVisibility::Visible);
		Three->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		nOne->SetVisibility(ESlateVisibility::Visible);
		nTwo->SetVisibility(ESlateVisibility::Visible);
		nThree->SetVisibility(ESlateVisibility::Visible);
		One->SetVisibility(ESlateVisibility::Hidden);
		Two->SetVisibility(ESlateVisibility::Hidden);
		Three->SetVisibility(ESlateVisibility::Hidden);
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////