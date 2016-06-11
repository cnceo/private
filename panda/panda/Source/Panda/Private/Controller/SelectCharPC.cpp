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
// ��½
/** Login Select Char HUD */
void ASelectCharPC::LoginEnter()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_SelectChar);

	//auto udid = TCHAR_TO_ANSI(*FPlatformMisc::GetUniqueDeviceId());

	//auto& h = GGameInstance->pandanet->clientZConnection.handler;
	////  ������¼Э��Э��
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
// ������������Ϸ
/** Select Char Enter Game */
void ASelectCharPC::EnterNetGame(FString& host, int32 port)
{
	// ����
	//FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_World);
	// ����
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_MainCity);
}

//////////////////////////////////////////////////////////////////////////
// ѡ�˽�����Ϸ
/** Select Char Enter Game */
void ASelectCharPC::EnterGame()
{
	// ����
	//FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_World);
	// ����
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_MainCity);
}

/** Select Char CreatChar */
void ASelectCharPC::Create()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_CreaterChar);
}

//////////////////////////////////////////////////////////////////////////
// ����
/** Create Char Break SelecetChar */
void ASelectCharPC::BreakSelecetChar()
{
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_SelectChar);
}

/** Create Char CreateRole */
void ASelectCharPC::CreateRole()
{
	//////////////////////////////////////////////////////////////////////////
	// ������ɷ���ѡ��
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
	// �������
	CurrentSelectCharIndex = LastSelectCharIndex = 0;
	// �������
	CurrentSelectProgress = LastSelectProgress = Select_One;
	// ������
	CeratePanelList.Empty();

	TArray<UWidget*> WidgetList;
	FEKGameFrame::Instance()->HUDManager()->GetCurrentWindowAllUWidget(WidgetList);

	// �����������
	for (UWidget* Widget : WidgetList)
	{
		if (Widget->GetClass() == UCanvasPanel::StaticClass())
		{	
			// �����
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

	// ������

	// ��ְҵ

	// 
}

void ASelectCharPC::ChangeSelectProgress(SelectProgress inProfession)
{
	LastSelectProgress = CurrentSelectProgress;
	CurrentSelectProgress = inProfession;

	UCanvasPanel* Panel = *CeratePanelList.Find("Main");

	// ��ʼ������
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
				// ��ʼ������
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
				// ��ʼ��ְҵ
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

/** R1�� */
void ASelectCharPC::R1Button() 
{
	CheckR1();
}

/** L1��*/
void ASelectCharPC::L1Button() 
{
	CheckL1();
}

// ��ʼ��ѡ������Ľ���
bool ASelectCharPC::InitSeleRace()
{
	FSelectCharacterTableData* Table = (FSelectCharacterTableData*)(FPandaDataPool::Instance()->GetData(DataPool::DataType::DATA_SelectChar));
	SelectRaceList = Table->GetRaceDataList();

	class UCanvasPanel* Panel = *CeratePanelList.Find("Two");

	// ��ʼ������
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

// �ı�ѡ���ɫ
void ASelectCharPC::ChangeSelectChar(int inIndex)
{
	// ���õ�ǰѡ�������
	if (inIndex >= SelectRaceList.Num())
		inIndex = SelectRaceList.Num() - 1;

	LastSelectCharIndex = CurrentSelectCharIndex;
	CurrentSelectCharIndex = inIndex;
	CurrentSelectRace = SelectRaceList[inIndex];

	InitRaceName();
	InitRaceDescribe();
	InitRaceSkillList();
}

// ����ѡ��Ľ�ɫ
void ASelectCharPC::DiscardSeletChar()
{
	
}

// ��ʼ����ɫ����
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

// ��ʼ����ɫ����
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

// ��ʼ����ɫ�츳���ܱ�
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

		// ��������
		UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);

		TArray<UWidget*> WidgetList;
		itemWidget->WidgetTree->GetAllWidgets(WidgetList);
		
		// ����Item�µ����пؼ�
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetName() == "SkillIcon")
			{
				UImage *SkillImage = Cast<UImage>(Widget);
				if (SkillImage != nullptr)
				{
					// ������ͼƬ
					UObject *headIcon = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(Skill->SkillIocnPaht);
					// ���ð�ť��ͼƬ
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

	// ��ʼ������
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
// ��ʼ��ְҵ����
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
// ��ʼ��ְҵ����
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
// ��ʼ����ɫְҵ���ܱ�
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

		// ��������
		UUserWidget *itemWidget = FEKGameFrame::Instance()->HUDManager()->InstancdeUMGwidget(itemObj);

		TArray<UWidget*> WidgetList;
		itemWidget->WidgetTree->GetAllWidgets(WidgetList);

		// ����Item�µ����пؼ�
		for (UWidget* Widget : WidgetList)
		{
			if (Widget->GetName() == "SkillIcon")
			{
				UImage *SkillImage = Cast<UImage>(Widget);
				if (SkillImage != nullptr)
				{
					// ������ͼƬ
					UObject *headIcon = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(Skill->SkillIocnPaht);
					// ���ð�ť��ͼƬ
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
// ��ʼ����ɫְҵ���ܵĶ���Ƭչʾ
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
// ��ʼ����ɫְҵ����ͼ��
void ASelectCharPC::InitProfessionProperty()
{
	if (ProfessionPropertyPanel == nullptr)
	{
		FEKLogManager::Instance()->Log(EKLog::Error, "Can not Find ProfessionProperty");
		return;
	}

	// ��ʼ������
	for (int i = 0; i < ProfessionPropertyPanel->GetChildrenCount(); i++)
	{
		UWidget* Widget = ProfessionPropertyPanel->GetChildAt(i);

		if (Widget->GetName() == "LiLangBar")
		{
			// ������
			UProgressBar* LilangBar = Cast<UProgressBar>(Widget);
			LilangBar->Percent = CurrentSelectProfession->Liliang;
			LilangBar->SynchronizeProperties();
		}
		else if (Widget->GetName() == "MinJieBar")
		{
			// ������
			UProgressBar* MinjieBar = Cast<UProgressBar>(Widget);
			MinjieBar->Percent = CurrentSelectProfession->Minjie;
			MinjieBar->SynchronizeProperties();
		}
		else if (Widget->GetName() == "ZhiHuiBar")
		{
			// �ǻ�
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
// ��ʱ
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