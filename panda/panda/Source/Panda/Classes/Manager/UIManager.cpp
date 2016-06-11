// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "UIManager.h"
#include "PandaUtils.h"


void UIManager::Init()
{
	//OpenUMGAsset(UMGAssetPath_AcceptTask);
}

void UIManager::OpenUMGAsset(FString AssetPath)
{
	FStringAssetReference StringRef = AssetPath;

	//check cache
	auto checkRet = FindInWidgetCache(AssetPath);
	if (checkRet != nullptr)
	{
		checkRet->SetVisibility(ESlateVisibility::Visible);
		if (checkRet->IsInViewport())
		{
			return;
		}
		checkRet->AddToViewport();
		return;
	}

	if (!CreateFromAsset(StringRef))
	{
		//AsynLoad
		StreamableManager.RequestAsyncLoad(StringRef, FStreamableDelegate::CreateUObject(this, &UIManager::OnAsynLoadNotify, StringRef));
	}

}

void UIManager::CloseUMGAsset(FString AssetPath, bool bDestory)
{
	auto ret = FindInWidgetCache(AssetPath);

	if (ret != nullptr)
	{
		ret->RemoveFromViewport();
		if (bDestory)
		{
			m_WidgetCache.Remove(ret);
			ret->ConditionalBeginDestroy();			
		}
	}

}

bool UIManager::CreateFromAsset(FStringAssetReference StringRef)
{
	bool bResult = false;

	UObject* inObject = UPandaUtils::CreateAsset(StringRef.ToString());
	if (inObject)
	{
		UPandaWidget* obj = CreateWidget<UPandaWidget>(GGameInstance, Cast<UClass>(inObject));
		if (obj)
		{
			obj->m_AssetPath = StringRef.ToString();
			m_WidgetCache.Add(obj);
			obj->SetVisibility(ESlateVisibility::Visible);
			obj->AddToViewport();

		}

		bResult = true;
	}

	return bResult;
}

void UIManager::OnAsynLoadNotify(FStringAssetReference StringRef)
{
	CreateFromAsset(StringRef);
}

UPandaWidget* UIManager::FindInWidgetCache(FString AssetPath)
{

	if (m_WidgetCache.Num() == 0)
		return nullptr;

	UPandaWidget* ppWidget = nullptr;
	//UPandaWidget** ppWidget = m_WidgetCache.FindByPredicate(
	//	[&](const UPandaWidget* widget)
	//{
	//	if (widget == nullptr)
	//	{
	//		m_WidgetCache.Remove(**widget);
	//		return nullptr;
	//	}
	//	return widget->m_AssetPath == AssetPath;
	//}
	//);
	for (auto var : m_WidgetCache)
	{
		if (var)
		{
			if(var->m_AssetPath == AssetPath)
				ppWidget = var;
		}
		else
		{
			m_WidgetCache.Remove(var);
		}
	}


	return ppWidget;
}
