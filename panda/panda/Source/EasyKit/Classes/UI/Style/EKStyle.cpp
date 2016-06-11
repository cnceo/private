// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKStyle.h"
#include "SlateGameResources.h"

//TSharedPtr< FSlateStyleSet > FEKStyle::EKStyleInstance = NULL;
//
//void FEKStyle::Initialize()
//{
//	if (!EKStyleInstance.IsValid())
//	{
//		EKStyleInstance = Create();
//		FSlateStyleRegistry::RegisterSlateStyle(*EKStyleInstance);
//	}
//}
//
//void FEKStyle::Shutdown()
//{
//	FSlateStyleRegistry::UnRegisterSlateStyle(*EKStyleInstance);
//	ensure(EKStyleInstance.IsUnique());
//	EKStyleInstance.Reset();
//}
//
//FName FEKStyle::GetStyleSetName()
//{
//	static FName StyleSetName(TEXT("FEKStyle"));
//	return StyleSetName;
//}
//
//#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
//#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
//#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
//#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
//#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )
//
//TSharedRef< FSlateStyleSet > FEKStyle::Create()
//{
//	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FEKStyle::GetStyleSetName(), "/Game/UI/Styles", "/Game/UI/Styles");
//	FSlateStyleSet& Style = StyleRef.Get();
//
//	// Fonts still need to be specified in code for now
//	Style.Set("VehicleGame.MenuTextStyle", FTextBlockStyle()
//		.SetFont(TTF_FONT("Fonts/Roboto-Black", 20))
//		.SetColorAndOpacity(FLinearColor::White)
//		.SetShadowColorAndOpacity(FLinearColor::Black)
//		.SetShadowOffset(FIntPoint(-1,1))
//		);
//
//	return StyleRef;
//}
//
//#undef IMAGE_BRUSH
//#undef BOX_BRUSH
//#undef BORDER_BRUSH
//#undef TTF_FONT
//#undef OTF_FONT
//
//void FEKStyle::ReloadTextures()
//{
//	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
//}
//
//const ISlateStyle& FEKStyle::Get()
//{
//	return *EKStyleInstance;
//}
