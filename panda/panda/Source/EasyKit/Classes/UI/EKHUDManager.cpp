
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

// ��ʹ�� EKDataPool�������� ���WidgetWindowList������Զ���䣬�� ����
bool FEKHUDManager::Init()
{
	//////////////////////////////////////////////////////////////////////////
	// ��ʱ����  ����������
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

// ��ʹ�� EKDataPool�������� ���WidgetWindowList ����
bool FEKHUDManager::Init(TArray<FUMGPanel*>& inHUDTableTArry)
{

	for (auto TableData : inHUDTableTArry)
	{
		m_UMGWidgetAll.Add(TableData->sWidgetName, TableData);
	}

	return true;
}

// ��ʾһ������ ���û�м����ȼ���
// ����2������ǻ��ⴰ�� �Զ�ж��
bool FEKHUDManager::ShowWindow(FString inWindosName, bool inAotuGC)
{
	if (CurrentWindowsName == inWindosName)
		return true;

	FUMGPanel* windos = m_UMGWidgetAll.FindRef(inWindosName);
	
	if (windos == nullptr)
		return false;

	// ���û�м��� �ȼ���
	if (windos->Window == nullptr)
	{
		// ����
		UObject* obj = LoadUMGwidget(windos->sWidgetPath);
		if (obj == nullptr)
			return false;

		// ʵ����
		UUserWidget* umgWidget = InstancdeUMGwidget(obj);
		if (umgWidget == nullptr)
			return false;

		windos->Window = umgWidget;
	}

	//��鴰�ڻ���
	CheckMutexUMGWidget(windos);

	windos->Window->SetVisibility(ESlateVisibility::Visible);

	// ���õ�ǰ������ �� ����
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

// ����һ������ 
// ����2���Ƿ�ж��
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

// �������д��ڴ��� 
// ����2�����ش���ĳ���������ϵ�  Ĭ��Ϊ0 ȫ������
void FEKHUDManager::HideAllWindow(int nLevel)
{
	// ���
	for (auto window : m_UMGWidgetAll)
	{
		if (window.Value->nMutexLevel > nLevel)
		{
			if(window.Value->Window != nullptr)
				window.Value->Window->SetVisibility(ESlateVisibility::Hidden);
		}

	}

}

// ��鴴���Ƿ񻥳� �������ر���������
bool FEKHUDManager::CheckMutexUMGWidget(FUMGPanel* inWindow)
{
	if (CurrentWindows == nullptr)
	{
		CurrentWindows = inWindow;
		CurrentWindowsName = inWindow->sWidgetName;

		return true;
	}

	// ��黥��
	for (auto window : m_UMGWidgetAll)
	{
		if (window.Value->nMutexLevel == inWindow->nMutexLevel)
		{
			// ���ش���
			if (window.Value->Window)
			{
				window.Value->Window->SetVisibility(ESlateVisibility::Hidden);

				// ����л��� �����Զ�GC�Ļ� ж�ص�ǰ
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

// ����һ��UMG widget
UObject* FEKHUDManager::LoadUMGwidget(FString inPath)
{
	UObject* object = NULL;

	decltype(inPath) Str = inPath;
	object = FEKGameFrame::Instance()->ResourceManager()->GetEKObject(Str);

	return object;
}

// ʵ����һ������
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

// ���ӵ����ⴰ��
bool FEKHUDManager::AddMutexUMGWidget(UUserWidget* inWidget)
{

	return true;
}

bool FEKHUDManager::AddMutexUMGWidget(UUserWidget* inWidget, bool isShow)
{

	return true;
}

// ��ô���
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

// ��õ�ǰ���� �����Ӵ���
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