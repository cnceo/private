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

		// 副本组ID 和 副本组信息_Client
		for (auto& ChapterGroup : GGameInstance->SafeGetDataManager()->m_FsPAChapterGroupData)
		{
			int nID = ChapterGroup.Value.nID;
			auto data = ChapterGroup.Value;
			m_DungeonGroupData.Add(nID, data);
		}

		//// 副本ID 和 副本信息_Client
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
	// 副本剩余开启时间倒计时_文本
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

	// 关闭该界面
	OnCross();
}
void UPAWidget_Dungeon_Chapter::CountdownReset_Implementation()
{
	m_CountdownTime = MaxCountDownTime;
}

void UPAWidget_Dungeon_Chapter::ParseUIControllers()
{
	// 章节的背景图_图片
	Image_background_1 = Cast<UImage>(getChildByName(this, "Image_background_1"));
	// 右下角的章节介绍图_图片
	Image_background_2 = Cast<UImage>(getChildByName(this, "Image_background_2"));

	// 副本1_按钮
	Image_1 = Cast<UImage>(getChildByName(this, "Image_1"));
	Image_2 = Cast<UImage>(getChildByName(this, "Image_2"));
	// 副本2_按钮
	Image_3 = Cast<UImage>(getChildByName(this, "Image_3"));
	Image_4 = Cast<UImage>(getChildByName(this, "Image_4"));
	// 副本3_按钮
	Image_5 = Cast<UImage>(getChildByName(this, "Image_5"));
	Image_6 = Cast<UImage>(getChildByName(this, "Image_6"));
	// 副本4_按钮
	Image_7 = Cast<UImage>(getChildByName(this, "Image_7"));
	Image_8 = Cast<UImage>(getChildByName(this, "Image_8"));
	// 副本5_按钮
	Image_9 = Cast<UImage>(getChildByName(this, "Image_9"));
	Image_10 = Cast<UImage>(getChildByName(this, "Image_10"));	

	// 副本难度Easy_按钮
	Image_difficulty_1 = Cast<UImage>(getChildByName(this, "Image_difficulty_1"));
	Image_difficulty_2 = Cast<UImage>(getChildByName(this, "Image_difficulty_2"));
	// 副本难度Normal_按钮
	Image_difficulty_3 = Cast<UImage>(getChildByName(this, "Image_difficulty_3"));
	Image_difficulty_4 = Cast<UImage>(getChildByName(this, "Image_difficulty_4"));
	// 副本难度Hero_按钮
	Image_difficulty_5 = Cast<UImage>(getChildByName(this, "Image_difficulty_5"));
	Image_difficulty_6 = Cast<UImage>(getChildByName(this, "Image_difficulty_6"));
	// 副本难度Abyss_按钮
	Image_difficulty_7 = Cast<UImage>(getChildByName(this, "Image_difficulty_7"));
	Image_difficulty_8 = Cast<UImage>(getChildByName(this, "Image_difficulty_8"));
	
	// 副本剩余开启时间倒计时_文本
	TextBlock_21 = Cast<UTextBlock>(getChildByName(this, "TextBlock_21"));

	// 副本名称1_文本 _对应上面的副本按钮
	TextBlock_1 = Cast<UTextBlock>(getChildByName(this, "TextBlock_1"));
	// 副本名称2_文本
	TextBlock_2 = Cast<UTextBlock>(getChildByName(this, "TextBlock_2"));
	// 副本名称3_文本
	TextBlock_3 = Cast<UTextBlock>(getChildByName(this, "TextBlock_3"));
	// 副本名称4_文本
	TextBlock_4 = Cast<UTextBlock>(getChildByName(this, "TextBlock_4"));
	// 副本名称5_文本
	TextBlock_5 = Cast<UTextBlock>(getChildByName(this, "TextBlock_5"));

	// 章节名称_文本
	TextBlock_11 = Cast<UTextBlock>(getChildByName(this, "TextBlock_11"));
	// 副本当前选中的难度_文本
	TextBlock_12 = Cast<UTextBlock>(getChildByName(this, "TextBlock_12"));
	// 副本推荐等级_文本
	TextBlock_13 = Cast<UTextBlock>(getChildByName(this, "TextBlock_13"));
	// 人数限制_文本
	TextBlock_14 = Cast<UTextBlock>(getChildByName(this, "TextBlock_14"));
	// 重生次数_文本
	TextBlock_15 = Cast<UTextBlock>(getChildByName(this, "TextBlock_15"));
	
	// 副本难度_Easy_文本
	TextBlock_difficulty_1 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_1"));
	// 副本难度_Normal_文本
	TextBlock_difficulty_2 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_2"));
	// 副本难度_Hero_文本
	TextBlock_difficulty_3 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_3"));
	// 副本难度_Abyss_文本
	TextBlock_difficulty_4 = Cast<UTextBlock>(getChildByName(this, "TextBlock_difficulty_4"));
}

void UPAWidget_Dungeon_Chapter::InitCurrentInterface(int32 nDungeonGroupID)
{
	// 获取当前副本组ID为nDungeonGroupID的副本组信息
	m_CurrentDungeonGroupData = m_DungeonGroupData.Find(nDungeonGroupID);
	
	// 过滤所有副本组ID等于nDungeonGroupID该值的副本信息
	for (auto& Dungeon : GGameInstance->SafeGetDataManager()->m_FsPADungeonData)
	{
		int nID = Dungeon.Value.nID;
		auto data = Dungeon.Value;
		if (data.nGroupId == nDungeonGroupID)
		{
			m_DungeonData.Add(nID, data);
		}
	}

	// 同步当前一共有多少个副本
	m_nCurrentDungeonGroupHaveMaxDunCounts = m_DungeonData.Num();
	// 设置所有的副本名称等
	int nCount = 0;
	for (TMap<int32, FsPADungeonData>::TConstIterator It(m_DungeonData); It; ++It)
	{
		auto key = It.Key();
		auto data = It.Value();
		int32 nID = data.nID;
		nCount = nCount + 1;

		// 第一次进入副本界面，如果m_nCurrentDungeonID = 0,设置m_nCurrentDungeonID值为该章节中的一个的副本ID
		if (m_nCurrentDungeonID == 0)
		{
			m_nCurrentDungeonID = nID;
		}

		// 副本名称1_文本 _对应上面的副本按钮
		auto TextBlock_idx = Cast<UTextBlock>(getChildByName(this, (*FString::Printf(TEXT("TextBlock_%d"), (int32)(nCount)))));
		if (TextBlock_idx)
		{
			auto nameIdArray = data.nNameId;
			int nNum = nameIdArray.Num();
			auto stringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(nameIdArray[m_nCurrentDungeonDifficulty-1]);
			TextBlock_idx->SetText(FText::FromString(stringData->strDesc));
		}
	}

	// 同步当前选中的副本数据
	m_CurrentDungeonData = m_DungeonData.Find(m_nCurrentDungeonID);

	if (!m_CurrentDungeonData)
		return;

	// 字符串拼接
	/*FName(*FString::Printf(TEXT("%d_%d"), keyCharacter, keyOther))
	FName(*FString::Printf(TEXT("Collision_%d"), (int32)emType))*/	

	// 设置副本组的背景图片
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
			// 图片一状态显示按下
			Image_1->SetVisibility(ESlateVisibility::Hidden);
			Image_2->SetVisibility(ESlateVisibility::Visible);
			Image_2->SetRenderScale(fSacle);
			// 其他按钮状态显示正常
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
			// 图片2状态显示按下
			Image_3->SetVisibility(ESlateVisibility::Hidden);
			Image_4->SetVisibility(ESlateVisibility::Visible);
			Image_4->SetRenderScale(fSacle);
			// 其他按钮状态显示正常
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
			// 图片3状态显示按下
			Image_5->SetVisibility(ESlateVisibility::Hidden);
			Image_6->SetVisibility(ESlateVisibility::Visible);
			Image_6->SetRenderScale(fSacle);
			// 其他按钮状态显示正常
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
			// 图片4状态显示按下
			Image_7->SetVisibility(ESlateVisibility::Hidden);
			Image_8->SetVisibility(ESlateVisibility::Visible);
			Image_8->SetRenderScale(fSacle);
			// 其他按钮状态显示正常
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
			// 图片5状态显示按下
			Image_9->SetVisibility(ESlateVisibility::Hidden);
			Image_10->SetVisibility(ESlateVisibility::Visible);
			Image_10->SetRenderScale(fSacle);
			// 其他按钮状态显示正常
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

	// 设置副本组的背景图片
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
			// Easy难度状态显示选中
			Image_difficulty_1->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_2->SetVisibility(ESlateVisibility::Visible);
			// 其他难度状态显示普通
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
			// Normal难度状态显示选中
			Image_difficulty_3->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_4->SetVisibility(ESlateVisibility::Visible);
			// 其他难度状态显示普通
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
			// Hero难度状态显示选中
			Image_difficulty_5->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_6->SetVisibility(ESlateVisibility::Visible);
			// 其他难度状态显示普通
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
			// Aybss难度状态显示选中
			Image_difficulty_7->SetVisibility(ESlateVisibility::Hidden);
			Image_difficulty_8->SetVisibility(ESlateVisibility::Visible);
			// 其他难度状态显示普通
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
	// 设置章节名称
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

	// 设置副本难度
	if (TextBlock_12)
	{
		/* Current Dungeon Diffcult, default = 1    /1 简单/ 2 普通/ 3 英雄/ 4 深渊, 当前选中的副本难度 */
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

	// 设置副本推荐等级
	if (TextBlock_13)
	{
		auto nLevelArray = m_CurrentDungeonData->nLevel;
		int32 nCurrLevel = nLevelArray[m_nCurrentDungeonDifficulty - 1];
		TextBlock_13->SetText(FText::FromString(*FString::Printf(TEXT("Recommend Lv. %d"), (int32)(nCurrLevel))));
	}

	// 设置副本最大攻击人数
	if (TextBlock_14)
	{
		auto nLimitPlayerArray = m_CurrentDungeonData->LimitPlayer;
		int32 nCurrnLimitPlayer = nLimitPlayerArray[m_nCurrentDungeonDifficulty - 1];
		TextBlock_14->SetText(FText::FromString(*FString::Printf(TEXT("Limit %dP"), (int32)(nCurrnLimitPlayer))));
	}

	//设置副本重生人数
	if (TextBlock_15)
	{
		auto nRebornTimesArray = m_CurrentDungeonData->RebornTimes;
		int32 nCurrnRebornTimes = nRebornTimesArray[m_nCurrentDungeonDifficulty - 1];
		TextBlock_15->SetText(FText::FromString(*FString::Printf(TEXT("Reborn Limit %d Times"), (int32)(nCurrnRebornTimes))));
	}
}

/* 数据更新 */
void UPAWidget_Dungeon_Chapter::UpdateCurrentNeedData()
{
	// 遍历使用的计数器
	int nCount = 0;
	for (TMap<int32, FsPADungeonData>::TConstIterator It(m_DungeonData); It; ++It)
	{
		nCount = nCount + 1;

		auto key = It.Key();
		auto data = It.Value();
		int32 nID = data.nID;

		if (nCount == m_nCurrentLeftAndRightIdx)
		{
			// 同步当前选中的副本ID
			m_nCurrentDungeonID = nID;
		}
	}

	// 同步当前选中的副本数据
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
	// 关闭该界面
	Super::OnCross();

	// ...
}

// Enter
void UPAWidget_Dungeon_Chapter::OnCircle()
{
	Super::OnCircle();

	OnCross();
	// 调用接口_调用打开副本的接口
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

/* 服务端请求获取玩家通关章节信息 */
void UPAWidget_Dungeon_Chapter::GetServerChapterData()
{
	// send request

	/* get and set client data */

	//auto data = servergetChapterdata
	//SetProto3_ChapterData(proto3::ChapterData data);

	// ...
}
/* 服务端请求获取玩家通关关卡信息 */
void UPAWidget_Dungeon_Chapter::GetServerStageData()
{
	// send request

	/* get and set client data */

	//auto data = servergetStatedata
	//SetProto3_StageData(proto3::StageData data);

	// ...
}
/* 解析服务端下发的章节信息 */
void UPAWidget_Dungeon_Chapter::ParseServerChapterData()
{
	/*if (Proto3_ChapterData)
	{*/
		//Proto3_ChapterData.nid();		// 副本组id
		//Proto3_ChapterData.nnameid();	// 副本组名称
		//Proto3_ChapterData.ntype();		// 类型
		//Proto3_ChapterData.ndescid();	// 副本组描述
		//Proto3_ChapterData.nlevel();	// 副本等级
	//}
}
/* 解析服务端下发的关卡信息 */
void UPAWidget_Dungeon_Chapter::ParseServerStageData()
{
	//Proto3_StageData.nid() = 1;						// 副本id
	//Proto3_StageData.nnameid() = 2;					// 副本名称
	//Proto3_StageData.ngroupid() = 3;				// 副本组id	
	//Proto3_StageData.nlevel() = 4;					// 副本等级
	//Proto3_StageData.ndifficulty() = 5;				// 副本难度
	//Proto3_StageData.nneedmobility() = 6;			// 消费体力
	//Proto3_StageData.nmapid() = 7;					// 地图资源组
	//Proto3_StageData.nrewardexp() = 8;				// 通关奖励经验（暂时不用）
	//Proto3_StageData.nrewardgold() = 9;				// 通关奖励金币（暂时不用）
	//Proto3_StageData.nrewardexploit() = 10;			// 增加战功（不使用）
	//Proto3_StageData.nrewardcourage() = 11;			// 增加勇气点
	//Proto3_StageData.nrewardjustice() = 12;			// 增加正义点

	//Proto3_StageData.nrewardpackid() = 13;			// 掉落包id	
	//Proto3_StageData.nnextinstanceids() = 14;		// 通关后激活下个关卡id	
	//Proto3_StageData.nactivateinstanceid() = 15;	// 上一关	
	//Proto3_StageData.nfreetimes() = 16;				// 进入次数	
	//Proto3_StageData.ncanbuytimes() = 17;			// 购买次数	
	//Proto3_StageData.nprice() = 18;					// 价格	
	//Proto3_StageData.nstar() = 19;					// 副本评价
}
/* 保存到客户端数据结构中 */
void UPAWidget_Dungeon_Chapter::SaveClientChapterData()
{

}
/* 保存到客户端数据结构中 */
void UPAWidget_Dungeon_Chapter::SaveClientStageData()
{

}
/* 设置UI显示数据 */
void UPAWidget_Dungeon_Chapter::ShowUIData()
{

}
/* 读取本地信息 */
void UPAWidget_Dungeon_Chapter::ClientReadJsonChapterData()
{

}
void UPAWidget_Dungeon_Chapter::ClientReadJsonStageData()
{

}

/*
*	Generate Loot Data
*	生成掉落数据
*	传入关卡ID输出一个掉落数组
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
			// 1普通/2精英/3BOSS/4NPC/5伙伴
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
				// 1.普通
				{
					// 1.普通/2.精英/3.BOSS/4.特殊/5.活动/6.任务			
					auto nRewardType_Normal = lootData->nRewardType_Normal;
					auto nItemId_Normal = lootData->nItemId_Normal;
					auto nLoot_random_Normal = lootData->nLoot_random_Normal;
					
					auto lootNum = 0;
					for (int j = 0; j < nItemId_Normal.Num(); j++)
					{
						if (nItemId_Normal[j] != 0)
						{
							// 取随机数字,返回值0-1之间
							float RandFloat = FGenericPlatformMath::SRand();
							// 判断随机掉落几率在
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
				// 2.精英
				{
					 
					// 1.普通/2.精英/3.BOSS/4.特殊/5.活动/6.任务
					auto nRewardType_Elite = lootData->nRewardType_Elite;
					auto nItemId_Elite = lootData->nItemId_Elite;
					auto nLoot_random_Elite = lootData->nLoot_random_Elite;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_Elite.Num(); j++)
					{
						if (nItemId_Elite[j] != 0)
						{
							// 取随机数字,返回值0-1之间
							float RandFloat = FGenericPlatformMath::SRand();
							// 判断随机掉落几率在
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

					// 1.普通/2.精英/3.BOSS/4.特殊/5.活动/6.任务
					auto nRewardType_BOSS = lootData->nRewardType_BOSS;
					auto nItemId_BOSS = lootData->nItemId_BOSS;
					auto nLoot_random_BOSS = lootData->nLoot_random_BOSS;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_BOSS.Num(); j++)
					{
						if (nItemId_BOSS[j] != 0)
						{
							// 取随机数字,返回值0-1之间
							float RandFloat = FGenericPlatformMath::SRand();
							// 判断随机掉落几率在
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
				// 4.特殊
				{}break;				
				case 5:
				// 5.活动
				{

					// 1.普通/2.精英/3.BOSS/4.特殊/5.活动/6.任务
					auto nRewardType_Activity = lootData->nRewardType_Activity;
					auto nItemId_Activity = lootData->nItemId_Activity;
					auto nLoot_random_Activity = lootData->nLoot_random_Activity;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_Activity.Num(); j++)
					{
						if (nItemId_Activity[j] != 0)
						{
							// 取随机数字,返回值0-1之间
							float RandFloat = FGenericPlatformMath::SRand();
							// 判断随机掉落几率在
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
				// 6.任务
				{

					// 1.普通/2.精英/3.BOSS/4.特殊/5.活动/6.任务
					auto nRewardType_Task = lootData->nRewardType_Task;
					auto nItemId_Task = lootData->nItemId_Task;
					auto nLoot_random_Task = lootData->nLoot_random_Task;

					auto lootNum = 0;
					for (int j = 0; j < nItemId_Task.Num(); j++)
					{
						if (nItemId_Task[j] != 0)
						{
							// 取随机数字,返回值0-1之间
							float RandFloat = FGenericPlatformMath::SRand();
							// 判断随机掉落几率在
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