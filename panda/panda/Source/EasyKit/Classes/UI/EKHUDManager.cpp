
#include "EasyKit.h"


// Widgets
#include "Visual.h"
#include "PanelSlot.h"
#include "Widget.h"
#include "Anchors.h"
#include "Widget.h"
#include "UserWidget.h"
#include "PanelWidget.h"
#include "WidgetTree.h"
#include "EKGameFrame.h"
#include "EKHUDManager.h"


FEKHUDManager::FEKHUDManager() :
CurrentWindowsName(""),
CurrentWindows(nullptr)
{
	m_UMGWidgetAll.Empty();
}

FEKHUDManager::~FEKHUDManager()
{
	CurrentWindowsName = "";
	CurrentWindows = nullptr;
	
	for (auto window : m_UMGWidgetAll)
	{
		delete window.Value;
		window.Value = nullptr;
	}
}

// 请使用 EKDataPool的派生类 填充WidgetWindowList这里会自动填充，或 传参
bool FEKHUDManager::Init()
{
	//////////////////////////////////////////////////////////////////////////
	// 临时测试  请填充表数据
	FUMGPanel* windos = new FUMGPanel();

	windos->sWidgetName = TEXT("Login");
	windos->sWidgetPath = TEXT("/Game/Resources/HUD/UI/UMG/UI_Login.UI_Login_C");
	windos->bAotoGC = true;
	windos->nMutexLevel = 1;
	//////////////////////////////////////////////////////////////////////////

	m_UMGWidgetAll.Add(windos->sWidgetName, windos);
	//////////////////////////////////////////////////////////////////////////

	return true;
}

// 请使用 EKDataPool的派生类 填充WidgetWindowList 传参
bool FEKHUDManager::Init(TArray<FUMGPanel*>& inHUDTableTArry)
{

	for (auto TableData : inHUDTableTArry)
	{
		m_UMGWidgetAll.Add(TableData->sWidgetName, TableData);
	}

	return true;
}

// 显示一个窗口 如果没有加载先加载
// 参数2：如果是互斥窗口 自动卸载
bool FEKHUDManager::ShowWindow(FString inWindosName, bool inAotuGC)
{
	if (CurrentWindowsName == inWindosName)
		return true;

	FUMGPanel* windos = m_UMGWidgetAll.FindRef(inWindosName);
	
	if (windos == nullptr)
		return false;

	// 如果没有加载 先加载
	if (windos->Window == nullptr)
	{
		// 加载
		UObject* obj = LoadUMGwidget(windos->sWidgetPath);
		if (obj == nullptr)
			return false;

		// 实例化
		UUserWidget* umgWidget = InstancdeUMGwidget(obj);
		if (umgWidget == nullptr)
			return false;

		windos->Window = umgWidget;
	}

	//检查窗口互斥
	CheckMutexUMGWidget(windos);

	windos->Window->SetVisibility(ESlateVisibility::Visible);

	// 设置当前窗口名 和 对象
	CurrentWindowsName = inWindosName;
	CurrentWindows = windos;

	return true;
}

void FEKHUDManager::DestroyWindow()
{
	GetCurrentWidget()->Window->RemoveFromViewport();

	//FUMGPanel* window = m_UMGWidgetAll.FindRef( GetCurrentWidget() );

	//if (window == nullptr && window->Window)
	//	return false;

	//window->Window->SetVisibility(ESlateVisibility::Hidden);

	//if (bDestroy == true)
	//{
	//	window->Window->RemoveFromViewport();
	//	window->Window->BeginDestroy();
	//	window->Window = nullptr;
	//}

}

bool FEKHUDManager::GetWindowIsVisible(FString inWindosName)
{
	FUMGPanel* windos = m_UMGWidgetAll.FindRef(inWindosName);

	if (windos == nullptr && windos->Window == nullptr)
		return false;

	if (windos->Window->GetVisibility() == ESlateVisibility::Visible)
	{
		return true;
	}

	return false;
}

// 隐藏一个窗口 
// 参数2：是否卸载
bool FEKHUDManager::HideWindow(FString inWindowName, bool bDestroy)
{
	FUMGPanel* window = nullptr;
	window = m_UMGWidgetAll.FindRef(inWindowName);

	if (window == nullptr)
		return false;

	if (window->Window == nullptr)
		return false;

	window->Window->SetVisibility(ESlateVisibility::Hidden);
	CurrentWindowsName = "";


	if (bDestroy == true)
	{
		window->Window->RemoveFromViewport();
		//window->Window->BeginDestroy();
		window->Window = nullptr;
		
	}

	return true;
}

// 隐藏所有窗口窗口 
// 参数2：隐藏大于某个级别以上的  默认为0 全部隐藏
void FEKHUDManager::HideAllWindow(int nLevel)
{
	// 检查
	for (auto window : m_UMGWidgetAll)
	{
		if (window.Value->nMutexLevel > nLevel)
		{
			if(window.Value->Window != nullptr)
				window.Value->Window->SetVisibility(ESlateVisibility::Hidden);
		}

	}

}

// 检查创建是否互斥 如果互斥关闭其他窗口
bool FEKHUDManager::CheckMutexUMGWidget(FUMGPanel* inWindow)
{
	if (CurrentWindows == nullptr)
	{
		CurrentWindows = inWindow;
		CurrentWindowsName = inWindow->sWidgetName;

		return true;
	}

	// 检查互斥
	for (auto window : m_UMGWidgetAll)
	{
		if (window.Value->nMutexLevel == inWindow->nMutexLevel)
		{
			// 隐藏窗口
			if (window.Value->Window)
			{
				window.Value->Window->SetVisibility(ESlateVisibility::Hidden);

				// 如果有互斥 并且自动GC的话 卸载当前
				if (window.Value->bAotoGC == true && window.Value != inWindow)
				{
					if (window.Value->Window != nullptr)
					{
						window.Value->Window->RemoveFromViewport();
						//window.Value->Window->BeginDestroy();
						window.Value->Window = nullptr;
					}
				}
			}
		}
	}

	return true;
}

// 加载一个UMG widget
UObject* FEKHUDManager::LoadUMGwidget(FString inPath)
{
	UObject* object = NULL;

	decltype(inPath) Str = inPath;
	object = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(Str);

	return object;
}

// 实例化一个窗口
UUserWidget* FEKHUDManager::InstancdeUMGwidget(UObject* inObject)
{
	if (inObject == NULL)
		return NULL;

	UUserWidget* widget = CreateWidget<UUserWidget>(GWorld, Cast<UClass>(inObject));

	if (widget == nullptr)
		return nullptr;

	widget->AddToViewport();

	return widget;
}

// 增加到互斥窗口
bool FEKHUDManager::AddMutexUMGWidget(UUserWidget* inWidget)
{

	return true;
}

bool FEKHUDManager::AddMutexUMGWidget(UUserWidget* inWidget, bool isShow)
{

	return true;
}

// 获得窗口
UUserWidget* FEKHUDManager::GetUMGWidget(FString inWindowName)
{
	FUMGPanel* window = m_UMGWidgetAll.FindRef(inWindowName);

	if (!window)
		return NULL;

	return window->Window;
}

FUMGPanel* FEKHUDManager::GetCurrentWidget()
{
	return CurrentWindows;
}

UWidget* FEKHUDManager::GetCurrentWindowChild(FString inChildName)
{
	if (CurrentWindows == nullptr)
		return NULL;

	if(CurrentWindows->Window == nullptr)
		return NULL;	

	TArray<class UWidget*> Widgets;
	CurrentWindows->Window->WidgetTree->GetAllWidgets(Widgets);

	FString ExistingName;

	for (UWidget* Widget : Widgets)
	{
		Widget->GetName(ExistingName);
		if (ExistingName.Equals(inChildName, ESearchCase::IgnoreCase))
		{
			return Widget;
		}
	}

	return NULL;
}

// 获得当前窗口 所有子窗口
void FEKHUDManager::GetCurrentWindowAllUWidget(TArray<class UWidget*>& inWindosList)
{
	if (CurrentWindows == nullptr)
		return;

	if (CurrentWindows->Window == nullptr)
		return;

	CurrentWindows->Window->WidgetTree->GetAllWidgets(inWindosList);
}

bool FEKHUDManager::GetCurrentWindowAllChild(TArray<UWidget*>& inWindosList)
{
	if (CurrentWindows == nullptr || !CurrentWindows->Window)
		return false;

	CurrentWindows->Window->WidgetTree->GetChildWidgets(CurrentWindows->Window, inWindosList);

	return true;
}

UWidget* FEKHUDManager::GetWindowChildByName(UUserWidget* inRoot, FString inChildName)
{
	if (!inRoot)
		return NULL;

	TArray<class UWidget*> Widgets;
	GetWindowAllChild(inRoot, Widgets);

	FString ExistingName;

	for (UWidget* Widget : Widgets)
	{
		Widget->GetName(ExistingName);
		if (ExistingName.Equals(inChildName, ESearchCase::IgnoreCase))
		{
			return Widget;
		}
	}

	return NULL;
}

bool FEKHUDManager::GetWindowAllChild(UUserWidget* inRoot, TArray<UWidget*>& inWindosList)
{
	if (!inRoot)
		return false;

	TArray<class UWidget*> Widgets;
	inRoot->WidgetTree->GetChildWidgets(inRoot, inWindosList);

	return true;
}

bool FEKHUDManager::SetWidgetEnable(FString & sName, bool isEnable)
{
	if (GetCurrentWidget() == nullptr)
	{
		return false;
	}

	UWidget* pWidget = GetCurrentWindowChild(sName);
	if (pWidget && pWidget->IsValidLowLevel())
	{
		pWidget->SetIsEnabled(isEnable);
		return true;
	}
	else
	{
		return false;
	}
	//TSharedPtr<SWidget> ptr = FEKGameFrame::Instance()->HUDManager()->GetCurrentWindowChild("Button_Create")->GetCachedWidget();
	//SButton* button = (SButton*)ptr.Get();
	//button->SetOnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked));
}