// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PAWidget_Dungeon_Chapter.h"
#include "PandaGameInstance.h"
#include "EKLogManager.h"
#include "PandaUtils.h"

#define MaxDifficultyLevel 4
#define MaxCountDownTime 60

UPAWidget_Dungeon_Chapter::UPAWidget_Dungeon_Chapter()
: m_nCurrentDungeonGroupID(1)
, m_nCurrentDungeonDifficulty(1)
, m_nCurrentDungeonID(0)
, m_nCurrentLeftAndRightIdx(1)
, m_nCurrentTopAndBottomIdx(1)
, m_nCurrentDungeonGroupHaveMaxDunCounts(0)
{
	m_DungeonData.Reset();
	m_DungeonGroupData.Reset();

	m_CountdownTime = MaxCountDownTime;
}

UPAWidget_Dungeon_Chapter::UPAWidget_Dungeon_Chapter(int32 nDungeonGroupID)
: m_nCurrentDungeonGroupID(nDungeonGroupID)
, m_nCurrentDungeonDifficulty(1)
, m_nCurrentDungeonID(0)
, m_nCurrentLeftAndRightIdx(1)
, m_nCurrentTopAndBottomIdx(1)
, m_nCurrentDungeonGroupHaveMaxDunCounts(0)
{
	m_DungeonData.Reset();
	m_DungeonGroupData.Reset();

	m_CountdownTime = MaxCountDownTime;
}

UPAWidget_Dungeon_Chapter::~UPAWidget_Dungeon_Chapter()
{

}

void UPAWidget_Dungeon_Chapter::NativeConstruct()
{
	Super::NativeConstruct();

	if (GGameInstance)
	{

		// ������ID �� ��������Ϣ_Client
		for (auto& ChapterGroup : GGameInstance->SafeGetDataManager()->m_FsPAChapterGroupData)
		{
			int nID = ChapterGroup.Value.nID;
			auto data = ChapterGroup.Value;
			m_DungeonGroupData.Add(nID, data);
		}

		//// ����ID �� ������Ϣ_Client
		//for (auto& Dungeon : GGameInstance->SafeGetDataManager()->m_FsPADungeonData)
		//{
		//	int nID = Dungeon.Value.nID;
		//	auto data = Dungeon.Value;
		//	m_DungeonData.Add(nID, data);
		//}
	}

	/* Parse UI Controllers */
	ParseUIControllers();
	// Init interface
	InitCurrentInterface(m_nCurrentDungeonGroupID);
	
	// timer 
	UpdateTimeDisplay();

	CountdownReset();
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UPAWidget_Dungeon_Chapter::AdvanceTimer, 1.0f, true);

	// ...
}

void UPAWidget_Dungeon_Chapter::UpdateTimeDisplay()
{
	// ����ʣ�࿪��ʱ�䵹��ʱ_�ı�
	TextBlock_21->SetText(FText::FromString(*FString::Printf(TEXT("%d"), (int32)(m_CountdownTime))));
}

void UPAWidget_Dungeon_Chapter::AdvanceTimer()
{
	--m_CountdownTime;

	UpdateTimeDisplay();

	if (m_CountdownTime < 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();

		//CountdownReset();
	}
}
void UPAWidget_Dungeon_Chapter::CountdownHasFinished_Implementation()
{
	TextBlock_21->SetText(FText::FromString("GO!"));

	// �رոý���
	OnCross();
}
void UPAWidget_Dungeon_Chapter::CountdownReset_Implementation()
{
	m_CountdownTime = MaxCountDownTime;
}

void UPAWidget_Dungeon_Chapter::ParseUIControllers()
{
	// �½ڵı���ͼ_ͼƬ
	Image_background_1 = Cast<UImage>(getChildByName(this, "Image_background_1"));
	// ���½ǵ��½ڽ���ͼ_ͼƬ
	Image_background_2 = Cast<UImage>(getChildByName(this, "Image_background_2"));

	// ����1_��ť
	Image_1 = Cast<UImage>(getChildByName(this, "Image_1"));
	Image_2 = Cast<UImage>(getChildByName(this, "Image_2"));
	// ����2_��ť
	Image_3 = Cast<UImage>(getChildByName(this, "Image_3"));
	Image_4 = Cast<UImage>(getChildByName(this, "Image_4"));
	// ����3_��ť
	Image_5 = Cast<UImage>(getChildByName(this, "Image_5"));
	Image_6 = Cast<UImage>(getChildByName(this, "Image_6"));
	// ����4_��ť
	Image_7 = Cast<UImage>(getChildByName(this, "Image_7"));
	Image_8 = Cast<UImage>(getChildByName(this, "Image_8"));
	// ����5_��ť
	Image_9 = Cast<UImage>(getChildByName(this, "Image_9"));
	Image_10 = Cast<UImage>(getChildByName(this, "Image_10"));	

	// �����Ѷ�Easy_��ť
	Image_difficulty_1 = Cast<UImage>(getChildByName(this, "Image_difficulty_1"));
	Image_difficulty_2 = Cast<UImage>(getChildByName(this, "Image_difficulty_2"));
	// �����Ѷ�Normal_��ť
	Image_difficulty_3 = Cast<UImage>(getChildByName(this, "Image_difficulty_3"));
	Image_difficulty_4 = Cast<UImage>(getChildByName(this, "Image_difficulty_4"));
	// �����Ѷ�Hero_��ť
	Image_difficulty_5 = Cast<UImage>(getChildByName(this, "Image_difficulty_5"));
	Image_difficulty_6 = Cast<UImage>(getChildByName(this, "Image_difficulty_6"));
	// �����Ѷ�Abyss_��ť
	Image_difficulty_7 = Cast<UImage>(getChildByName(this, "Image_difficulty_7"));
	Image_difficulty_8 = Cast<UImage>(getChildByName(this, "Image_difficulty_8"));
	
	// ����ʣ�࿪��ʱ�䵹��ʱ_�ı�
	TextBlock_21 = Cast<UTextBlock>(getChildByName(this, "TextBlock_21"));

	// ��������1_�ı� _��Ӧ����ĸ�����ť
	TextBlock_1 = Cast<UTextBlock>(getChildByName(this, "TextBlock_1"));
	// ��������2_�ı�
	TextBlock_2 = Cast<UTextBlock>(getChildByName(this, "TextBlock_2"));
	// ��������3_�ı�
	TextBlock_3 = Cast<UTextBlock>(getChildByName(this, "TextBlock_3"));
	// ��������4_�ı�
	TextBlock_4 = Cast<UTextBlock>(getChildByName(this, "TextBlock_4"));
	// ��������5_�ı�
	TextBlock_5 = Cast<UTextBlock>(getChildByName(this, "TextBlock_5"));

	// �½�����_�ı�
	TextBlock_11 = Cast<UTextBlock>(getChildByName(this, "TextBlock_11"));
	// ������ǰѡ�е��Ѷ�_�ı�
	TextBlock_12 = Cast<UTextBlock>(getChildByName(this, "TextBlock_12"));
	// �����Ƽ��ȼ�_�ı�
	TextBlock_13 = Cast<UTextBlock>(getChildByName(this, "TextBlock_13"));
	// ��������_�ı�
	TextBlock_14 = Cast<UTextBlock>(getChildByName(this, "TextBlock_14"));
	// ��������_�ı�
	TextBlock_15 = Cast<UTextBlock>(getChildByName(this, "TextBlock_15"));
	
	// �����Ѷ�_Easy_�ı�
	TextBlock_difficulty_1 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_1"));
	// �����Ѷ�_Normal_�ı�
	TextBlock_difficulty_2 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_2"));
	// �����Ѷ�_Hero_�ı�
	TextBlock_difficulty_3 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_3"));
	// �����Ѷ�_Abyss_�ı�
	TextBlock_difficulty_4 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_4"));
}

void UPAWidget_Dungeon_Chapter::InitCurrentInterface(int32 nDungeonGroupID)
{
	// ��ȡ��ǰ������IDΪnDungeonGroupID�ĸ�������Ϣ
	m_CurrentDungeonGroupData = m_DungeonGroupData.Find(nDungeonGroupID);
	
	// �������и�����ID����nDungeonGroupID��ֵ�ĸ�����Ϣ
	for (auto& Dungeon : GGameInstance->SafeGetDataManager()->m_FsPADungeonData)
	{
		int nID = Dungeon.Value.nID;
		auto data = Dungeon.Value;
		if (data.nGroupId == nDungeonGroupID)
		{
			m_DungeonData.Add(nID, data);
		}
	}

	// ͬ����ǰһ���ж��ٸ�����
	m_nCurrentDungeonGroupHaveMaxDunCounts = m_DungeonData.Num();
	// �������еĸ������Ƶ�
	int nCount = 0;
	for (TMap<int32, FsPADungeonData>::TConstIterator It(m_DungeonData); It; ++It)
	{
		auto key = It.Key();
		auto data = It.Value();
		int32 nID = data.nID;
		nCount = nCount + 1;

		// ��һ�ν��븱�����棬���m_nCurrentDungeonID = 0,����m_nCurrentDungeonIDֵΪ���½��е�һ���ĸ���ID
		if (m_nCurrentDungeonID == 0)
		{
			m_nCurrentDungeonID = nID;
		}

		// ��������1_�ı� _��Ӧ����ĸ�����ť
		auto TextBlock_idx = Cast<UTextBlock>(getChildByName(this, (*FString::Printf(TEXT("TextBlock_%d"), (int32)(nCount)))));
		if (TextBlock_idx)
		{
			auto nameIdArray = data.nNameId;
			int nNum = nameIdArray.Num();
			auto stringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(nameIdArray[m_nCurrentDungeonDifficulty-1]);
			TextBlock_idx->SetText(FText::FromString(stringData->strDesc));
		}
	}

	// ͬ����ǰѡ�еĸ�������
	m_CurrentDungeonData = m_DungeonData.Find(m_nCurrentDungeonID);

	if (!m_CurrentDungeonData)
		return;

	// �ַ���ƴ��
	/*FName(*FString::Printf(TEXT("%d_%d"), keyCharacter, keyOther))
	FName(*FString::Printf(TEXT("Collision_%d"), (int32)emType))*/	

	// ���ø�����ı���ͼƬ
	auto resData = GGameInstance->SafeGetDataManager()->m_ResourcesTable.Find(m_CurrentDungeonGroupData->nBackgroundImageID);
	if (resData && Image_background_1)
	{
		UObject* backgroundImg = UPandaUtils::CreateAsset((TEXT("%s"), resData->strPath));
		if (backgroundImg)
			Image_background_1->Brush.SetResourceObject(backgroundImg);
	}

	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
}

void UPAWidget_Dungeon_Chapter::UpdateCurrentInterfaceLR()
{
	float xyScale = 1.2f;
	FVector2D fSacle = FVector2D(xyScale, xyScale);
	// interface update
	switch (m_nCurrentLeftAndRightIdx)
	{
	case 1:
		{
			// ͼƬһ״̬��ʾ����
			Image_1->SetVisibility(ESlateVisibility::Hidden);
			Image_2->SetVisibility(ESlateVisibility::Visible);
			Image_2->SetRenderScale(fSacle);
			// ������ť״̬��ʾ����
			Image_3->SetVisibility(ESlateVisibility::Visible);
			Image_4->SetVisibility(ESlateVisibility::Hidden);
			Image_5->SetVisibility(ESlateVisibility::Visible);
			Image_6->SetVisibility(ESlateVisibility::Hidden);
			Image_7->SetVisibility(ESlateVisibility::Visible);
			Image_8->SetVisibility(ESlateVisibility::Hidden);
			Image_9->SetVisibility(ESlateVisibility::Visible);
			Image_10->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 2:
		{
			// ͼƬ2״̬��ʾ����
			Image_3->SetVisibility(ESlateVisibility::Hidden);
			Image_4->SetVisibility(ESlateVisibility::Visible);
			Image_4->SetRenderScale(fSacle);
			// ������ť״̬��ʾ����
			Image_1->SetVisibility(ESlateVisibility::Visible);
			Image_2->SetVisibility(ESlateVisibility::Hidden);
			Image_5->SetVisibility(ESlateVisibility::Visible);
			Image_6->SetVisibility(ESlateVisibility::Hidden);
			Image_7->SetVisibility(ESlateVisibility::Visible);
			Image_8->SetVisibility(ESlateVisibility::Hidden);
			Image_9->SetVisibility(ESlateVisibility::Visible);
			Image_10->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 3:
		{
			// ͼƬ3״̬��ʾ����
			Image_5->SetVisibility(ESlateVisibility::Hidden);
			Image_6->SetVisibility(ESlateVisibility::Visible);
			Image_6->SetRenderScale(fSacle);
			// ������ť״̬��ʾ����
			Image_1->SetVisibility(ESlateVisibility::Visible);
			Image_2->SetVisibility(ESlateVisibility::Hidden);
			Image_3->SetVisibility(ESlateVisibility::Visible);
			Image_4->SetVisibility(ESlateVisibility::Hidden);
			Image_7->SetVisibility(ESlateVisibility::Visible);
			Image_8->SetVisibility(ESlateVisibility::Hidden);
			Image_9->SetVisibility(ESlateVisibility::Visible);
			Image_10->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 4:
		{
			// ͼƬ4״̬��ʾ����
			Image_7->SetVisibility(ESlateVisibility::Hidden);
			Image_8->SetVisibility(ESlateVisibility::Visible);
			Image_8->SetRenderScale(fSacle);
			// ������ť״̬��ʾ����
			Image_1->SetVisibility(ESlateVisibility::Visible);
			Image_2->SetVisibility(ESlateVisibility::Hidden);
			Image_3->SetVisibility(ESlateVisibility::Visible);
			Image_4->SetVisibility(ESlateVisibility::Hidden);
			Image_5->SetVisibility(ESlateVisibility::Visible);
			Image_6->SetVisibility(ESlateVisibility::Hidden);
			Image_9->SetVisibility(ESlateVisibility::Visible);
			Image_10->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 5:
		{
			// ͼƬ5״̬��ʾ����
			Image_9->SetVisibility(ESlateVisibility::Hidden);
			Image_10->SetVisibility(ESlateVisibility::Visible);
			Image_10->SetRenderScale(fSacle);
			// ������ť״̬��ʾ����
			Image_1->SetVisibility(ESlateVisibility::Visible);
			Image_2->SetVisibility(ESlateVisibility::Hidden);
			Image_3->SetVisibility(ESlateVisibility::Visible);
			Image_4->SetVisibility(ESlateVisibility::Hidden);
			Image_5->SetVisibility(ESlateVisibility::Visible);
			Image_6->SetVisibility(ESlateVisibility::Hidden);
			Image_7->SetVisibility(ESlateVisibility::Visible);
			Image_8->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	default:
		break;
	}

	// ���ø�����ı���ͼƬ
	auto nBackgroundImageIDArray = m_CurrentDungeonData->nBackgroundImageID;
	int32 nCurrBackgroundImageID = nBackgroundImageIDArray[m_nCurrentDungeonDifficulty - 1];
	auto resData = GGameInstance->SafeGetDataManager()->m_ResourcesTable.Find(nCurrBackgroundImageID);
	if (resData && Image_background_2)
	{
		UObject* backgroundImg = UPandaUtils::CreateAsset((TEXT("%s"), resData->strPath));
		if (backgroundImg)
			Image_background_2->Brush.SetResourceObject(backgroundImg);
	}
}

void UPAWidget_Dungeon_Chapter::UpdateCurrentInterfaceTB()
{

	switch (m_nCurrentTopAndBottomIdx)
	{
	case 1:
		{
			// Easy�Ѷ�״̬��ʾѡ��
			Image_difficulty_1->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_2->SetVisibility(ESlateVisibility::Visible);
			// �����Ѷ�״̬��ʾ��ͨ
			Image_difficulty_3->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_4->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_5->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_6->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_7->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_8->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 2:
		{
			// Normal�Ѷ�״̬��ʾѡ��
			Image_difficulty_3->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_4->SetVisibility(ESlateVisibility::Visible);
			// �����Ѷ�״̬��ʾ��ͨ
			Image_difficulty_1->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_2->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_5->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_6->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_7->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_8->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 3:
		{
			// Hero�Ѷ�״̬��ʾѡ��
			Image_difficulty_5->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_6->SetVisibility(ESlateVisibility::Visible);
			// �����Ѷ�״̬��ʾ��ͨ
			Image_difficulty_1->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_2->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_3->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_4->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_7->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_8->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case 4:
		{
			// Aybss�Ѷ�״̬��ʾѡ��
			Image_difficulty_7->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_8->SetVisibility(ESlateVisibility::Visible);
			// �����Ѷ�״̬��ʾ��ͨ
			Image_difficulty_1->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_2->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_3->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_4->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_5->SetVisibility(ESlateVisibility::Visible);
			Image_difficulty_6->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	default:
		break;
	}
	// interface update
	// �����½�����
	if (TextBlock_11)
	{
		auto nNameIdArray = m_CurrentDungeonData->nNameId;
		/*if (nnNameIdArray.Num() >= m_nCurrentDungeonDifficulty)
		{
		}*/
		int32 nCurrNameId = nNameIdArray[0];
		auto stringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(nCurrNameId);
		TextBlock_11->SetText(FText::FromString(stringData->strDesc));
	}

	// ���ø����Ѷ�
	if (TextBlock_12)
	{
		/* Current Dungeon Diffcult, default = 1    /1 ��/ 2 ��ͨ/ 3 Ӣ��/ 4 ��Ԩ, ��ǰѡ�еĸ����Ѷ� */
		auto nDiffArray = m_CurrentDungeonData->nDifficulty;
		int32 nCurrDiffculty = nDiffArray[m_nCurrentDungeonDifficulty - 1];
		switch (nCurrDiffculty)
		{
		case 1:
			TextBlock_12->SetText(FText::FromString("EASY_EASY"));
			break;
		case 2:
			TextBlock_12->SetText(FText::FromString("NORMAL_NORMAL"));
			break;
		case 3:
			TextBlock_12->SetText(FText::FromString("HERO_HERO"));
			break;
		case 4:
			TextBlock_12->SetText(FText::FromString("ABYSS_ABYSS"));
			break;
		default:
			TextBlock_12->SetText(FText::FromString("error_error"));
			break;
		}
	}

	// ���ø����Ƽ��ȼ�
	if (TextBlock_13)
	{
		auto nLevelArray = m_CurrentDungeonData->nLevel;
		int32 nCurrLevel = nLevelArray[m_nCurrentDungeonDifficulty - 1];
		TextBlock_13->SetText(FText::FromString(*FString::Printf(TEXT("Recommend Lv. %d"), (int32)(nCurrLevel))));
	}

	// ���ø�����󹥻�����
	if (TextBlock_14)
	{
		auto nLimitPlayerArray = m_CurrentDungeonData->LimitPlayer;
		int32 nCurrnLimitPlayer = nLimitPlayerArray[m_nCurrentDungeonDifficulty - 1];
		TextBlock_14->SetText(FText::FromString(*FString::Printf(TEXT("Limit %dP"), (int32)(nCurrnLimitPlayer))));
	}

	//���ø�����������
	if (TextBlock_15)
	{
		auto nRebornTimesArray = m_CurrentDungeonData->RebornTimes;
		int32 nCurrnRebornTimes = nRebornTimesArray[m_nCurrentDungeonDifficulty - 1];
		TextBlock_15->SetText(FText::FromString(*FString::Printf(TEXT("Reborn Limit %d Times"), (int32)(nCurrnRebornTimes))));
	}
}

/* ���ݸ��� */
void UPAWidget_Dungeon_Chapter::UpdateCurrentNeedData()
{
	// ����ʹ�õļ�����
	int nCount = 0;
	for (TMap<int32, FsPADungeonData>::TConstIterator It(m_DungeonData); It; ++It)
	{
		nCount = nCount + 1;

		auto key = It.Key();
		auto data = It.Value();
		int32 nID = data.nID;

		if (nCount == m_nCurrentLeftAndRightIdx)
		{
			// ͬ����ǰѡ�еĸ���ID
			m_nCurrentDungeonID = nID;
		}
	}

	// ͬ����ǰѡ�еĸ�������
	m_CurrentDungeonData = m_DungeonData.Find(m_nCurrentDungeonID);

	if (!m_CurrentDungeonData)
		return;
}

void UPAWidget_Dungeon_Chapter::NativeDestruct()
{
	Super::NativeDestruct();

	// ...
}

void UPAWidget_Dungeon_Chapter::UpdateSelf(float deltaTime)
{
	UPandaWidget::UpdateSelf(deltaTime);
}

// Exit
void UPAWidget_Dungeon_Chapter::OnCross()
{
	// �رոý���
	Super::OnCross();

	// ...
}

// Enter
void UPAWidget_Dungeon_Chapter::OnCircle()
{
	Super::OnCircle();

	OnCross();
	// ���ýӿ�_���ô򿪸����Ľӿ�
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_World);

	// ...
}

void UPAWidget_Dungeon_Chapter::OnLeft()
{
	m_nCurrentLeftAndRightIdx--;
	if (m_nCurrentLeftAndRightIdx < 1)
	{
		m_nCurrentLeftAndRightIdx = m_nCurrentDungeonGroupHaveMaxDunCounts;
	}
	m_nCurrentTopAndBottomIdx = 1;
	m_nCurrentDungeonDifficulty = m_nCurrentTopAndBottomIdx;

	// data update
	UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
}

void UPAWidget_Dungeon_Chapter::OnRight()
{
	m_nCurrentLeftAndRightIdx++;
	if (m_nCurrentLeftAndRightIdx > m_nCurrentDungeonGroupHaveMaxDunCounts)
	{
		m_nCurrentLeftAndRightIdx = 1;
	}
	m_nCurrentTopAndBottomIdx = 1;
	m_nCurrentDungeonDifficulty = m_nCurrentTopAndBottomIdx;

	// data update
	UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
}

void UPAWidget_Dungeon_Chapter::OnUp()
{
	m_nCurrentTopAndBottomIdx--;
	if (m_nCurrentTopAndBottomIdx < 1)
	{
		m_nCurrentTopAndBottomIdx = MaxDifficultyLevel;
	}
	m_nCurrentDungeonDifficulty = m_nCurrentTopAndBottomIdx;

	// data update
	UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
}

void UPAWidget_Dungeon_Chapter::OnDown()
{
	m_nCurrentTopAndBottomIdx++;
	if (m_nCurrentTopAndBottomIdx > MaxDifficultyLevel)
	{
		m_nCurrentTopAndBottomIdx = 1;
	}
	m_nCurrentDungeonDifficulty = m_nCurrentTopAndBottomIdx;

	// data update
	UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
}

void UPAWidget_Dungeon_Chapter::SetProto3_ChapterData(proto3::ChapterData data)
{
	Proto3_ChapterData = data;
}

void UPAWidget_Dungeon_Chapter::SetProto3_StageData(proto3::StageData data)
{
	Proto3_StageData = data;
}

void UPAWidget_Dungeon_Chapter::SetProto3_StageLootRewardData(proto3::StageLootRewardData data)
{
	Proto3_StageLootRewardData = data;
}

void UPAWidget_Dungeon_Chapter::SetClient_ChapterData(FsPADungeonGroupData data)
{
	Client_ChapterData = data;
}
void UPAWidget_Dungeon_Chapter::SetClient_StageData(FsPADungeonData data)
{
	Client_StageData = data;
}
void UPAWidget_Dungeon_Chapter::SetClient_StageLootRewardData(FsPAStageLootRewardData data)
{
	Client_StageLootRewardData = data;
}

/* ����������ȡ���ͨ���½���Ϣ */
void UPAWidget_Dungeon_Chapter::GetServerChapterData()
{
	// send request

	/* get and set client data */

	//auto data = servergetChapterdata
	//SetProto3_ChapterData(proto3::ChapterData data);

	// ...
}
/* ����������ȡ���ͨ�عؿ���Ϣ */
void UPAWidget_Dungeon_Chapter::GetServerStageData()
{
	// send request

	/* get and set client data */

	//auto data = servergetStatedata
	//SetProto3_StageData(proto3::StageData data);

	// ...
}
/* ����������·����½���Ϣ */
void UPAWidget_Dungeon_Chapter::ParseServerChapterData()
{
	/*if (Proto3_ChapterData)
	{*/
		//Proto3_ChapterData.nid();		// ������id
		//Proto3_ChapterData.nnameid();	// ����������
		//Proto3_ChapterData.ntype();		// ����
		//Proto3_ChapterData.ndescid();	// ����������
		//Proto3_ChapterData.nlevel();	// �����ȼ�
	//}
}
/* ����������·��Ĺؿ���Ϣ */
void UPAWidget_Dungeon_Chapter::ParseServerStageData()
{
	//Proto3_StageData.nid() = 1;						// ����id
	//Proto3_StageData.nnameid() = 2;					// ��������
	//Proto3_StageData.ngroupid() = 3;				// ������id	
	//Proto3_StageData.nlevel() = 4;					// �����ȼ�
	//Proto3_StageData.ndifficulty() = 5;				// �����Ѷ�
	//Proto3_StageData.nneedmobility() = 6;			// ��������
	//Proto3_StageData.nmapid() = 7;					// ��ͼ��Դ��
	//Proto3_StageData.nrewardexp() = 8;				// ͨ�ؽ������飨��ʱ���ã�
	//Proto3_StageData.nrewardgold() = 9;				// ͨ�ؽ�����ң���ʱ���ã�
	//Proto3_StageData.nrewardexploit() = 10;			// ����ս������ʹ�ã�
	//Proto3_StageData.nrewardcourage() = 11;			// ����������
	//Proto3_StageData.nrewardjustice() = 12;			// ���������

	//Proto3_StageData.nrewardpackid() = 13;			// �����id	
	//Proto3_StageData.nnextinstanceids() = 14;		// ͨ�غ󼤻��¸��ؿ�id	
	//Proto3_StageData.nactivateinstanceid() = 15;	// ��һ��	
	//Proto3_StageData.nfreetimes() = 16;				// �������	
	//Proto3_StageData.ncanbuytimes() = 17;			// �������	
	//Proto3_StageData.nprice() = 18;					// �۸�	
	//Proto3_StageData.nstar() = 19;					// ��������
}
/* ���浽�ͻ������ݽṹ�� */
void UPAWidget_Dungeon_Chapter::SaveClientChapterData()
{

}
/* ���浽�ͻ������ݽṹ�� */
void UPAWidget_Dungeon_Chapter::SaveClientStageData()
{

}
/* ����UI��ʾ���� */
void UPAWidget_Dungeon_Chapter::ShowUIData()
{

}
/* ��ȡ������Ϣ */
void UPAWidget_Dungeon_Chapter::ClientReadJsonChapterData()
{

}
void UPAWidget_Dungeon_Chapter::ClientReadJsonStageData()
{

}

/*
*	Generate Loot Data
*	���ɵ�������
*	����ؿ�ID���һ����������
*	Parameter: state_id
*/
TMap<int32, FsPAItemData*> UPAWidget_Dungeon_Chapter::GetLootDataByStageID(int32 nStageID)
{
	TMap<int32, FsPAItemData*> TmpItemData;
	// StageMonsterPositionData.json
	auto monsterPositionData = GGameInstance->SafeGetDataManager()->m_FsPAStageMonsterPositionData.Find(nStageID);
	if (monsterPositionData)
	{
		UE_LOG(LogTemp, Error, TEXT("monsterPositionData is null"));
		return TmpItemData;
	}
	auto tArrPositions = monsterPositionData->tArrPositions;
	auto num = 0;
	for (int i = 0; i < tArrPositions.Num(); i++)
	{
		if (tArrPositions[i] != 0)
		{
			//num++;

			// MonsterHeroBaseData.json
			auto monsterHeroBaseData = GGameInstance->SafeGetDataManager()->m_FsPAMonsterHeroBaseData.Find(tArrPositions[i]);
			if (monsterHeroBaseData)
			{
				UE_LOG(LogTemp, Error, TEXT("monsterHeroBaseData is null"));
				return TmpItemData;
			}
			// 1��ͨ/2��Ӣ/3BOSS/4NPC/5���
			auto monster_type = monsterHeroBaseData->nType;

			// StageLootRewardData.json
			auto lootData = GGameInstance->SafeGetDataManager()->m_FsPAStageLootRewardData.Find(nStageID);
			if (monsterHeroBaseData)
			{
				UE_LOG(LogTemp, Error, TEXT("lootData is null"));
				return TmpItemData;
			}
			switch (monster_type)
			{
				case 1:
				// 1.��ͨ
				{
					// 1.��ͨ/2.��Ӣ/3.BOSS/4.����/5.�/6.����			
					auto nRewardType_Normal = lootData->nRewardType_Normal;
					auto nItemId_Normal = lootData->nItemId_Normal;
					auto nLoot_random_Normal = lootData->nLoot_random_Normal;
					
					auto lootNum = 0;
					for (int j = 0; j < nItemId_Normal.Num(); j++)
					{
						if (nItemId_Normal[j] != 0)
						{
							// ȡ�������,����ֵ0-1֮��
							float RandFloat = FGenericPlatformMath::SRand();
							// �ж�������伸����
							if (RandFloat <= nLoot_random_Normal[j])
							{
								auto itemData = GGameInstance->SafeGetDataManager()->m_fsPaItemData.Find(nItemId_Normal[j]);
								if (itemData)
								{
									UE_LOG(LogTemp, Error, TEXT("itemData is null"));
									return TmpItemData;
								}
								TmpItemData.Add(num, itemData);

								num++;
								UE_LOG(LogTemp, Log, TEXT("num: %d"), num);
							}							
						}
					}
				}
				break;
				case 2:
				// 2.��Ӣ
				{
					 
					// 1.��ͨ/2.��Ӣ/3.BOSS/4.����/5.�/6.����
					auto nRewardType_Elite = lootData->nRewardType_Elite;
					auto nItemId_Elite = lootData->nItemId_Elite;
					auto nLoot_random_Elite = lootData->nLoot_random_Elite;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_Elite.Num(); j++)
					{
						if (nItemId_Elite[j] != 0)
						{
							// ȡ�������,����ֵ0-1֮��
							float RandFloat = FGenericPlatformMath::SRand();
							// �ж�������伸����
							if (RandFloat <= nLoot_random_Elite[j])
							{
								auto itemData = GGameInstance->SafeGetDataManager()->m_fsPaItemData.Find(nItemId_Elite[j]);
								if (itemData)
								{
									UE_LOG(LogTemp, Error, TEXT("itemData is null"));
									return TmpItemData;
								}
								TmpItemData.Add(num, itemData);

								num++;
								UE_LOG(LogTemp, Log, TEXT("num: %d"), num);
							}
						}
					}
				}
				break;
				case 3:
				// 3.BOSS
				{

					// 1.��ͨ/2.��Ӣ/3.BOSS/4.����/5.�/6.����
					auto nRewardType_BOSS = lootData->nRewardType_BOSS;
					auto nItemId_BOSS = lootData->nItemId_BOSS;
					auto nLoot_random_BOSS = lootData->nLoot_random_BOSS;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_BOSS.Num(); j++)
					{
						if (nItemId_BOSS[j] != 0)
						{
							// ȡ�������,����ֵ0-1֮��
							float RandFloat = FGenericPlatformMath::SRand();
							// �ж�������伸����
							if (RandFloat <= nLoot_random_BOSS[j])
							{
								auto itemData = GGameInstance->SafeGetDataManager()->m_fsPaItemData.Find(nItemId_BOSS[j]);
								if (itemData)
								{
									UE_LOG(LogTemp, Error, TEXT("itemData is null"));
									return TmpItemData;
								}
								TmpItemData.Add(num, itemData);

								num++;
								UE_LOG(LogTemp, Log, TEXT("num: %d"), num);
							}
						}
					}
				}
				break;
				case 4: 
				// 4.����
				{}break;				
				case 5:
				// 5.�
				{

					// 1.��ͨ/2.��Ӣ/3.BOSS/4.����/5.�/6.����
					auto nRewardType_Activity = lootData->nRewardType_Activity;
					auto nItemId_Activity = lootData->nItemId_Activity;
					auto nLoot_random_Activity = lootData->nLoot_random_Activity;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_Activity.Num(); j++)
					{
						if (nItemId_Activity[j] != 0)
						{
							// ȡ�������,����ֵ0-1֮��
							float RandFloat = FGenericPlatformMath::SRand();
							// �ж�������伸����
							if (RandFloat <= nLoot_random_Activity[j])
							{
								auto itemData = GGameInstance->SafeGetDataManager()->m_fsPaItemData.Find(nItemId_Activity[j]);
								if (itemData)
								{
									UE_LOG(LogTemp, Error, TEXT("itemData is null"));
									return TmpItemData;
								}
								TmpItemData.Add(num, itemData);

								num++;
								UE_LOG(LogTemp, Log, TEXT("num: %d"), num);
							}
						}
					}
				}
				break;
				case 6:
				// 6.����
				{

					// 1.��ͨ/2.��Ӣ/3.BOSS/4.����/5.�/6.����
					auto nRewardType_Task = lootData->nRewardType_Task;
					auto nItemId_Task = lootData->nItemId_Task;
					auto nLoot_random_Task = lootData->nLoot_random_Task;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_Task.Num(); j++)
					{
						if (nItemId_Task[j] != 0)
						{
							// ȡ�������,����ֵ0-1֮��
							float RandFloat = FGenericPlatformMath::SRand();
							// �ж�������伸����
							if (RandFloat <= nLoot_random_Task[j])
							{
								auto itemData = GGameInstance->SafeGetDataManager()->m_fsPaItemData.Find(nItemId_Task[j]);
								if (itemData)
								{
									UE_LOG(LogTemp, Error, TEXT("itemData is null"));
									return TmpItemData;
								}
								TmpItemData.Add(num, itemData);

								num++;
								UE_LOG(LogTemp, Log, TEXT("num: %d"), num);
							}
						}
					}
				}
				break;
				default:
					break;
			}
		}
	}

	
	return TmpItemData;
}