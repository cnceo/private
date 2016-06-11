// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PAWidget_Dungeon_SelectRegion.h"

void UPAWidget_Dungeon_SelectRegion::InitData()
{
	m_bLeft = true;
	m_bRight = false;
	m_nCurrentLeftIdx = 1;
	m_nCurrentRightIdx = 1;
	m_DungeonCenterAreaData.Reset();
	m_CurrentDungeonGroupData.Reset();
}

void UPAWidget_Dungeon_SelectRegion::NativeConstruct()
{
	Super::NativeConstruct();

	// Init current interface data
	InitData();

	// m_DungeonCenterAreaData: 左边的List显示需要用到的数据
	// 


	if (GGameInstance)
	{
		// 所有的中间区域ID 和 中间区域信息_Client
		for (auto& CenterAreaData : GGameInstance->SafeGetDataManager()->m_FsPADungeonCenterAreaData)
		{
			int nID = CenterAreaData.Value.nID;
			auto data = CenterAreaData.Value;
			auto nDungeonIdArray = data.nDungeonId;
			m_DungeonCenterAreaData.Add(nID, data);
		}

		// data update
		UpdateCurrentNeedData();

	
		//// 副本ID 和 副本信息_Client
		//for (auto& Dungeon : GGameInstance->SafeGetDataManager()->m_FsPADungeonData)
		//{
		//	int nID = Dungeon.Value.nID;
		//	auto data = Dungeon.Value;
		//	m_DungeonData.Add(nID, data);
		//}
	}

	// 解析UI控件
	ParseUIControllers();
	// 初始化界面
	InitCurrentInterface(0);
	// ...
}

void UPAWidget_Dungeon_SelectRegion::InitCurrentInterface(int32 nDungeonGroupID)
{
	// 全部中间区域的个数
	auto num = m_DungeonCenterAreaData.Num();

	// 初始化所有的中间区域
	if (ScrollBox_RegionList_Left)
	{
		int nCount = 0;
		for (TMap<int32, FsPADungeonCenterAreaData>::TConstIterator It(m_DungeonCenterAreaData); It; ++It)
		{
			auto key = It.Key();
			auto data = It.Value();
			int32 nID = data.nID;
			nCount = nCount + 1;

			// 创建子层
			auto UCanvasPanelSingle = NewObject<UCanvasPanel>(this, *FString::Printf(TEXT("UCanvasPanel_Left_%d"), nCount), RF_MarkAsRootSet);
			//UCanvasPanelSingle->

			// 创建UTextBlock
			auto textblock = NewObject<UTextBlock>(this, *FString::Printf(TEXT("DungeonText_Left_%d"), nCount), RF_MarkAsRootSet);
			auto nNameIdArray = data.nNameId;
			auto nNameId = nNameIdArray[0];
			auto stringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(nNameId);
			textblock->SetText(FText::FromString(stringData->strDesc));
			auto a = UCanvasPanelSingle->AddChildToCanvas(textblock);
			a->SetAutoSize(true);

			//创建Image
			auto ImageBack1 = NewObject<UImage>(this, *FString::Printf(TEXT("DungeonBackground1_Left_%d"), nCount), RF_MarkAsRootSet);
			UObject* backgroundImg1 = UPandaUtils::CreateAsset((TEXT("/Game/UITextures/Team/ui_dungeons_difficulty_01.ui_dungeons_difficulty_01")));
			if (ImageBack1 && backgroundImg1)
			{
				if (nCount == 1)
				{
					ImageBack1->SetVisibility(ESlateVisibility::Visible);
				}
				else {
					ImageBack1->SetVisibility(ESlateVisibility::Hidden);
				}
				ImageBack1->Brush.SetResourceObject(backgroundImg1);
				auto b = UCanvasPanelSingle->AddChildToCanvas(ImageBack1);
				b->SetAutoSize(false);
				FVector2D fSize = FVector2D(600, 30);
				b->SetSize(fSize);
			}

			//创建Image
			auto ImageBack2 = NewObject<UImage>(this, *FString::Printf(TEXT("DungeonBackground2_Left_%d"), nCount), RF_MarkAsRootSet);
			UObject* backgroundImg2 = UPandaUtils::CreateAsset((TEXT("/Game/UITextures/Team/ui_dungeons_difficulty_02.ui_dungeons_difficulty_02")));
			if (ImageBack2 && backgroundImg2)
			{
				if (nCount == 1)
				{
					ImageBack2->SetVisibility(ESlateVisibility::Visible);
				}
				else {
					ImageBack2->SetVisibility(ESlateVisibility::Hidden);
				}
				ImageBack2->Brush.SetResourceObject(backgroundImg2);
				auto c = UCanvasPanelSingle->AddChildToCanvas(ImageBack2);
				c->SetAutoSize(false);
				FVector2D fSize = FVector2D(600, 30);
				c->SetSize(fSize);
			}

			// 将子层加入到ScrollBox中
			ScrollBox_RegionList_Left->AddChild(UCanvasPanelSingle);
		}
	}

	if (ScrollBox_RegionList_Right)
	{
		int nCount = 0;
		for (TMap<int32, FsPADungeonGroupData>::TConstIterator It(m_CurrentDungeonGroupData); It; ++It)
		{
			auto key = It.Key();
			auto data = It.Value();
			int32 nID = data.nID;
			nCount = nCount + 1;

			// 创建子层
			auto UCanvasPanelSingle = NewObject<UCanvasPanel>(this, *FString::Printf(TEXT("UCanvasPanel_Right_%d"), nCount), RF_MarkAsRootSet);
			//UCanvasPanelSingle->

			// 创建UTextBlock
			auto textblock = NewObject<UTextBlock>(this, *FString::Printf(TEXT("DungeonText_Right_%d"), nCount), RF_MarkAsRootSet);
			auto nNameId = data.nNameId;
			auto stringData = GGameInstance->SafeGetDataManager()->m_StringTable.Find(nNameId);
			textblock->SetText(FText::FromString(stringData->strDesc));
			auto a = UCanvasPanelSingle->AddChildToCanvas(textblock);
			a->SetAutoSize(true);

			//创建Image
			auto ImageBack1 = NewObject<UImage>(this, *FString::Printf(TEXT("DungeonBackground1_Right_%d"), nCount), RF_MarkAsRootSet);
			UObject* backgroundImg1 = UPandaUtils::CreateAsset((TEXT("/Game/UITextures/Team/ui_dungeons_difficulty_01.ui_dungeons_difficulty_01")));
			if (ImageBack1 && backgroundImg1)
			{
				if (nCount == 1)
				{
					ImageBack1->SetVisibility(ESlateVisibility::Visible);
				}
				else {
					ImageBack1->SetVisibility(ESlateVisibility::Hidden);
				}
				
				ImageBack1->Brush.SetResourceObject(backgroundImg1);
				auto b = UCanvasPanelSingle->AddChildToCanvas(ImageBack1);
				b->SetAutoSize(false);
				FVector2D fSize = FVector2D(600, 30);
				b->SetSize(fSize);
			}

			//创建Image
			auto ImageBack2 = NewObject<UImage>(this, *FString::Printf(TEXT("DungeonBackground2_Right_%d"), nCount), RF_MarkAsRootSet);
			UObject* backgroundImg2 = UPandaUtils::CreateAsset((TEXT("/Game/UITextures/Team/ui_dungeons_difficulty_02.ui_dungeons_difficulty_02")));
			if (ImageBack2 && backgroundImg2)
			{
				if (nCount == 1)
				{
					ImageBack2->SetVisibility(ESlateVisibility::Visible);
				}
				else {
					ImageBack2->SetVisibility(ESlateVisibility::Hidden);
				}
				ImageBack2->Brush.SetResourceObject(backgroundImg2);
				auto c = UCanvasPanelSingle->AddChildToCanvas(ImageBack2);
				c->SetAutoSize(false);
				FVector2D fSize = FVector2D(600, 30);
				c->SetSize(fSize);
			}

			// 将子层加入到ScrollBox中
			ScrollBox_RegionList_Right->AddChild(UCanvasPanelSingle);
		}
	}

	//// data update
	//UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();

	// ...
}

void UPAWidget_Dungeon_SelectRegion::NativeDestruct()
{
	Super::NativeDestruct();

	// ...
}

void UPAWidget_Dungeon_SelectRegion::UpdateSelf(float deltaTime)
{
	UPandaWidget::UpdateSelf(deltaTime);
}

// Exit
void UPAWidget_Dungeon_SelectRegion::OnCross()
{
	// 关闭该界面
	Super::OnCross();

	// ...
}

// Enter
void UPAWidget_Dungeon_SelectRegion::OnCircle()
{
	Super::OnCircle();

	// 首先关闭该UI
	OnCross();
	
	// 执行切换场景
	// 主城
	FEKGameFrame::Instance()->ProcedureManager()->ChangeCurrentProcedure(GeometrySpace::Procedure::PT_CenterArea);

	// ...
}

void UPAWidget_Dungeon_SelectRegion::UpdateCurrentNeedData()
{

	// 当前中间区域
	int nCount = 0;
	for (TMap<int32, FsPADungeonCenterAreaData>::TConstIterator It(m_DungeonCenterAreaData); It; ++It)
	{
		auto key = It.Key();
		auto data = It.Value();
		int32 nDungeonCenterAreaID = data.nID;
		nCount = nCount + 1;

		if (nCount == m_nCurrentLeftIdx)
		{
			// 过滤每一个中间区域内的副本组ID数组,把符合条件的副本组ID筛选出来
			for (TArray<int32>::TConstIterator It(data.nDungeonId); It; ++It)
			{
				int32 nDungeonId_GroundID = *It;
				//nCount = nCount + 1;

				// 过滤所有符合条件的 副本组ID 和 副本组信息_Client
				for (auto& ChapterGroup : GGameInstance->SafeGetDataManager()->m_FsPAChapterGroupData)
				{
					int nChapterGroupID = ChapterGroup.Value.nID;

					if (nDungeonId_GroundID == nChapterGroupID)
					{
						auto data = ChapterGroup.Value;
						m_CurrentDungeonGroupData.Add(nChapterGroupID, data);
					}
				}
			}
		}

	}
}

void UPAWidget_Dungeon_SelectRegion::UpdateCurrentInterfaceLR()
{

}

void UPAWidget_Dungeon_SelectRegion::UpdateCurrentInterfaceTB()
{
	if (m_bLeft)
	{
		if (ScrollBox_RegionList_Left)
		{
			for (int i = 1; i <= m_DungeonCenterAreaData.Num(); i++)
			{
				auto DungeonBackground1_Right_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground1_Left_%d"), (int32)(i)))));
				auto DungeonBackground2_Right_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground2_Left_%d"), (int32)(i)))));
				DungeonBackground1_Right_Image->SetVisibility(ESlateVisibility::Hidden);
				DungeonBackground2_Right_Image->SetVisibility(ESlateVisibility::Hidden);
			}

			auto DungeonBackground1_Left_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground1_Left_%d"), (int32)(m_nCurrentLeftIdx)))));
			auto DungeonBackground2_Left_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground2_Left_%d"), (int32)(m_nCurrentLeftIdx)))));
			DungeonBackground1_Left_Image->SetVisibility(ESlateVisibility::Visible);
			DungeonBackground2_Left_Image->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if (m_bRight)
	{
		if (ScrollBox_RegionList_Right)
		{
			for (int i = 1; i <= m_CurrentDungeonGroupData.Num(); i++)
			{
				auto DungeonBackground1_Right_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground1_Right_%d"), (int32)(i)))));
				auto DungeonBackground2_Right_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground2_Right_%d"), (int32)(i)))));
				DungeonBackground1_Right_Image->SetVisibility(ESlateVisibility::Hidden);
				DungeonBackground2_Right_Image->SetVisibility(ESlateVisibility::Hidden);
			}

			auto DungeonBackground1_Right_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground1_Right_%d"), (int32)(m_nCurrentRightIdx)))));
			auto DungeonBackground2_Right_Image = Cast<UImage>(getChildByName(this, (*FString::Printf(TEXT("DungeonBackground2_Right_%d"), (int32)(m_nCurrentRightIdx)))));
			DungeonBackground1_Right_Image->SetVisibility(ESlateVisibility::Visible);
			DungeonBackground2_Right_Image->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UPAWidget_Dungeon_SelectRegion::OnLeft()
{
	if (!m_bLeft)
	{
		m_bLeft = true;
		m_bRight = false;
		m_nCurrentLeftIdx = 1;
		m_nCurrentRightIdx = 1;

		// data update
		//UpdateCurrentNeedData();
		// interface update
		UpdateCurrentInterfaceLR();
		UpdateCurrentInterfaceTB();
	}
	// ...
}

void UPAWidget_Dungeon_SelectRegion::OnRight()
{
	if (!m_bRight)
	{
		m_bRight = true;
		m_bLeft = false;
		m_nCurrentLeftIdx = 1;
		m_nCurrentRightIdx = 1;

		// data update
		//UpdateCurrentNeedData();
		// interface update
		UpdateCurrentInterfaceLR();
		UpdateCurrentInterfaceTB();
	}
	// ...
}

void UPAWidget_Dungeon_SelectRegion::OnUp()
{
	if (m_bLeft)
	{
		m_CurrentDungeonGroupData.Reset();
		m_nCurrentLeftIdx--;
		if (m_nCurrentLeftIdx <= 0)
		{
			m_nCurrentLeftIdx = m_DungeonCenterAreaData.Num();
		}

		// data update
		UpdateCurrentNeedData();
	}
	else if(m_bRight)
	{
		m_nCurrentRightIdx--;
		if (m_nCurrentRightIdx <= 0)
		{
			m_nCurrentRightIdx = m_CurrentDungeonGroupData.Num();
		}

		// data update
		UpdateCurrentNeedData();
	}

	// data update
	//UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
	// ...
}

void UPAWidget_Dungeon_SelectRegion::OnDown()
{
	if (m_bLeft)
	{
		m_CurrentDungeonGroupData.Reset();
		m_nCurrentLeftIdx++;
		if (m_nCurrentLeftIdx > m_DungeonCenterAreaData.Num())
		{
			m_nCurrentLeftIdx = 1;
		}

		// data update
		UpdateCurrentNeedData();
	}
	else if (m_bRight)
	{
		m_nCurrentRightIdx++;
		if (m_nCurrentRightIdx > m_CurrentDungeonGroupData.Num())
		{
			m_nCurrentRightIdx = 1;
		}

		// data update
		UpdateCurrentNeedData();
	}

	// data update
	//UpdateCurrentNeedData();
	// interface update
	UpdateCurrentInterfaceLR();
	UpdateCurrentInterfaceTB();
	// ...
}

void UPAWidget_Dungeon_SelectRegion::ParseUIControllers()
{
	// 背景图_图片
	Image_background_1 = Cast<UImage>(getChildByName(this, "Image_background_1"));
	// 背景图_图片
	Image_background_2 = Cast<UImage>(getChildByName(this, "Image_background_2"));
	// 按键提示_图片
	Image_KeyTips = Cast<UImage>(getChildByName(this, "Image_KeyTips"));

	// 副本名称1_文本 (Mirkwood   LV.15)
	TextBlock_11 = Cast<UTextBlock>(getChildByName(this, "TextBlock_11"));
	// 副本名称2_文本 (Mirkwood   LV.15)
	TextBlock_12 = Cast<UTextBlock>(getChildByName(this, "TextBlock_12"));
	// 副本名称3_文本 (Mirkwood   LV.15)
	TextBlock_13 = Cast<UTextBlock>(getChildByName(this, "TextBlock_13"));
	// 副本名称4_文本 (Mirkwood   LV.15)
	TextBlock_14 = Cast<UTextBlock>(getChildByName(this, "TextBlock_14"));
	// 副本名称5_文本 (Mirkwood   LV.15)
	TextBlock_15 = Cast<UTextBlock>(getChildByName(this, "TextBlock_15"));

	// Region dungeons
	TextBlock_5 = Cast<UTextBlock>(getChildByName(this, "TextBlock_5"));

	// 中间区域List_滚动条
	ScrollBox_RegionList_Left = Cast<UScrollBox>(getChildByName(this, "ScrollBox_RegionList_Left"));

	// 中间区域List_滚动条
	ScrollBox_RegionList_Right = Cast<UScrollBox>(getChildByName(this, "ScrollBox_RegionList_Right"));

	// TextBlock_TipsName
	TextBlock_TipsName = Cast<UTextBlock>(getChildByName(this, "TextBlock_TipsName"));

	// every time need to clear items
	if (ScrollBox_RegionList_Left)
		ScrollBox_RegionList_Left->ClearChildren();
	
	// every time need to clear items
	if (ScrollBox_RegionList_Right)
		ScrollBox_RegionList_Right->ClearChildren();
}