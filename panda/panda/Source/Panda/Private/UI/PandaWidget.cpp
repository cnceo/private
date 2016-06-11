// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaWidget.h"
#include "PandaUtils.h"
#include "MainPlayerController.h"
#include "PandaGameInstance.h"


void UPandaWidget::NativeConstruct()
{
	setSettingDim();
	Super::NativeConstruct();

	SetOwningLocalPlayer(UPandaGameInstance::Instance()->GetLocalPlayerByIndex(0));

	//init input
	bStopAction = true; // stopplayerAction

	//DpadLeft
	OnInputleft.BindUFunction(this, FName(TEXT("OnLeft")));
	ListenForInputAction(FName(TEXT("DpadLeft")), IE_Pressed, 1, OnInputleft);
	//DpadRight
	OnInputRight.BindUFunction(this, FName(TEXT("OnRight")));
	ListenForInputAction(FName(TEXT("DpadRight")), IE_Pressed, 1, OnInputRight);
	//DpadUP
	OnInputUp.BindUFunction(this, "OnUp");
	ListenForInputAction(FName(TEXT("DpadUP")), IE_Pressed, 1, OnInputUp);
	//DpadDown
	OnInputDown.BindUFunction(this, FName(TEXT("OnDown")));
	ListenForInputAction(FName(TEXT("DpadDown")), IE_Pressed, 1, OnInputDown);
	//Circle
	OnInput_Circle.BindUFunction(this, "OnCircle");
	ListenForInputAction(FName(TEXT("Quan")), IE_Pressed, 1, OnInput_Circle);
	//cross
	OnInput_Cross.BindUFunction(this, "OnCross");
	ListenForInputAction(FName(TEXT("Cha")), IE_Pressed, 1, OnInput_Cross);
	//square
	OnInput_Square.BindUFunction(this, "OnSquare");
	ListenForInputAction(FName(TEXT("FangKuai")), IE_Pressed, 1, OnInput_Square);
	//triangle
	OnInput_Triangle.BindUFunction(this, "OnTriangle");
	ListenForInputAction(FName(TEXT("SanJiao")), IE_Pressed, 1, OnInput_Triangle);
	//R1
	OnInput_R1.BindUFunction(this, "OnR1");
	ListenForInputAction(FName(TEXT("R1")), IE_Pressed, 1, OnInput_R1);
	//R2
	OnInput_R2.BindUFunction(this, "OnR2");
	ListenForInputAction(FName(TEXT("R2")), IE_Pressed, 1, OnInput_R2);
	//L1
	OnInput_L1.BindUFunction(this, "OnL1");
	ListenForInputAction(FName(TEXT("L1")), IE_Pressed, 1, OnInput_L1);
	//L2
	OnInput_L2.BindUFunction(this, "OnL2");
	ListenForInputAction(FName(TEXT("L2")), IE_Pressed, 1, OnInput_L2);
	//¹Ø±Õbag
	OnInput_closeBag.BindUFunction(this, "OnBag");
	ListenForInputAction(FName(TEXT("bag2")), IE_Pressed, 1, OnInput_closeBag);
	
	
	
}

void UPandaWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateSelf(InDeltaTime);

}


void UPandaWidget::UpdateSelf(float deltaTime)
{
	if (!IsInViewport())
		return;
}

void UPandaWidget::CloseSelf(bool bDestory /*= false*/)
{
	this->RemoveFromViewport();
	SetVisibility(ESlateVisibility::Hidden);	
}

void UPandaWidget::OnCross()
{
	CloseSelf();
	StopListeningForAllInputActions();

	//Destruct();	
}

void UPandaWidget::OnDown()
{
	int a = 0;
}

UWidget* UPandaWidget::getChildByName(UUserWidget* widget, FString fname)
{
	TArray<class UWidget*> Widgets;
	widget->WidgetTree->GetAllWidgets(Widgets);
	FString ExistingName;

	UWrapBox* box_ = nullptr;
	for (UWidget* Widget : Widgets)
	{

		Widget->GetName(ExistingName);
		if (ExistingName.Equals(fname, ESearchCase::IgnoreCase))
		{
			return Widget;
		}
	}
	return nullptr;
}
void UPandaWidget::setSettingDim()
{
	AMainPlayerController* pc = Cast<AMainPlayerController>(UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance()));
	FPostProcessSettings* fps = new FPostProcessSettings();
	fps->DepthOfFieldFocalDistance = 100;
	fps->DepthOfFieldFocalRegion = 100;
	fps->DepthOfFieldNearTransitionRegion = 100;
	fps->DepthOfFieldFarTransitionRegion = 100;
	fps->DepthOfFieldScale = .5f;
	fps->DepthOfFieldMaxBokehSize = 3;
	fps->DepthOfFieldSizeThreshold = .08f;

	pc->GetMainPlayer()->FollowCamera->PostProcessSettings = *fps;

}



