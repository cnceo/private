// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKHUD.h"
#include "EKGameFrame.h"
#include "EKSceneManager.h"
#include "Materials/MaterialInstanceDynamic.h"


const float AEKHUD::MinHudScale = 0.5f;

AEKHUD::AEKHUD(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	NoAmmoFadeOutTime =  1.0f;
	HitNotifyDisplayTime = 0.75f;
	LastEnemyHitDisplayTime = 0.2f;
	NoAmmoNotifyTime = -NoAmmoFadeOutTime;
	LastEnemyHitTime = -LastEnemyHitDisplayTime;

	//static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/Resoures/UI/HUD/HUDMain"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> IocnTextureOb(TEXT("/Game/Resoures/UI/HUD/Textures/T_Tou_Iocn"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> MapTextureOb(TEXT("/Game/Resoures/UI/HUD/Textures/Map"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> HealthMaterial(TEXT("/Game/Resoures/UI/HUD/Materials/M_HUD_Health_Bar"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMapStarOb(TEXT("/Game/Resoures/UI/HUD/Textures/T_Objective"));

	//static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/Resoures/UI/Font/Roboto51"));
	//static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/Resoures/UI/Font/Roboto18"));

	//static ConstructorHelpers::FObjectFinder<UTexture2D> Button(TEXT("/Game/Resoures/UI/HUD/Textures/T_Button"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> Button_Pressed(TEXT("/Game/Resoures/UI/HUD/Textures/T_Button_Pressed"));

	//HUDMainTexture = HUDMainTextureOb.Object;
	//HUDMapStar = HUDMapStarOb.Object;
	//BigFont = BigFontOb.Object;
	//NormalFont = NormalFontOb.Object;

	//HUDButton = Button.Object;
	//HUDButton_Pressed = Button_Pressed.Object;

	//// 生命的材质
	//for (int i = 0; i < 20;i++)
	//{
	//	HealthDynamicMaterial[i] = UMaterialInstanceDynamic::Create(HealthMaterial.Object, this);
	//}
	//IocnTexture = IocnTextureOb.Object;
	//MapTexture = MapTextureOb.Object;


	//TimePlaceBg  = UCanvas::MakeIcon(HUDMainTexture, 262, 16, 255, 62);
	//PrimaryWeapBg = UCanvas::MakeIcon(HUDMainTexture, 543, 17, 441, 81);
	//SecondaryWeapBg = UCanvas::MakeIcon(HUDMainTexture, 676, 111, 293, 50);

	//DeathMessagesBg = UCanvas::MakeIcon(HUDMainTexture, 502, 177, 342, 187);
	//TimerIcon = UCanvas::MakeIcon(HUDMainTexture, 381, 93, 24, 24);
	//PlaceIcon = UCanvas::MakeIcon(HUDMainTexture, 250, 468, 21, 28);


	//HitNotifyCrosshair = UCanvas::MakeIcon(HUDMainTexture, 54, 453, 50, 50); 

	Offset = 20.0f;
	HUDLight = FColor(175,202,213,255);
	HUDDark = FColor(110,124,131,255);
	ShadowedFont.bEnableShadow = true;
}


FString AEKHUD::GetTimeString(float TimeSeconds)
{
	// only minutes and seconds are relevant
	const int32 TotalSeconds = 1;
	const int32 NumMinutes = TotalSeconds / 60;
	const int32 NumSeconds = TotalSeconds % 60;

	const FString TimeDesc = FString::Printf(TEXT("%02d:%02d"), NumMinutes, NumSeconds);
	return TimeDesc;
}

void AEKHUD::DrawHealth()
{

}

void AEKHUD::DrawName()
{
	// 血条大小 和 偏移
	float fHealthWidth = Canvas->SizeX*0.14f;
	float fHealthHeight = Canvas->SizeY*0.02f;
	float fHealthOffsetX = Canvas->SizeX*0.14f*0.5f;

	FLinearColor NameColor = FLinearColor(1, 1, 1, 1);
	FLinearColor EnemyColor = FLinearColor(1, 0.1f, 0.1f, 1);

	//　画自己
	AEKCharacter* MyPawnPC = Cast<AEKCharacter>(GetOwningPawn());
	if (MyPawnPC)
	{
		APlayerController* Pc = Cast<APlayerController>(MyPawnPC->Controller);

		if (Pc != NULL)
		{
			FVector vec = MyPawnPC->GetActorLocation();
			vec.Z += Canvas->SizeY*0.15f;
			FVector post = Project(vec);
			float width, height = 0.0f;
			GetTextSize("CHINA_CEO", width, height, NULL);
			DrawText("CHINA_CEO", FLinearColor(1, 0.2, 0.2, 1), post.X , post.Y, NULL, 1.2);

			vec.Z -= 17;
			post = Project(vec);
			GetTextSize(MyPawnPC->fsName, width, height, NULL);
			DrawText(MyPawnPC->fsName, NameColor, post.X , post.Y, NULL, 1.1);

			vec.Z -= 23;
			post = Project(vec);
			HealthDynamicMaterial[0]->SetScalarParameterValue("Current health", MyPawnPC->Health / MyPawnPC->MaxHealth * 100);
			DrawMaterialSimple(HealthDynamicMaterial[0], post.X - fHealthOffsetX, post.Y, fHealthWidth, fHealthHeight, 1);

		}
	}

	// 画其他所有人
	std::unordered_map<int64_t, AEKCharacter*> map = FEKGameFrame::Instance()->SceneManager()->liveCharacterPool;

	int EmenyNum = 0;
	for (auto & player : map)
	{
		AEKCharacter* EmenyPawn = Cast<AEKCharacter>(player.second);
		if (EmenyPawn)
		{
			FVector DevVec = EmenyPawn->GetActorLocation() - MyPawnPC->GetActorLocation();
            if(DevVec.SizeSquared2D() > 7000000)
                continue;

			// 点乘朝向
			if ((FVector::DotProduct(DevVec, MyPawnPC->Controller->GetControlRotation().Vector()) > 0) || (DevVec.SizeSquared2D() < 22500))
			{
				AController* Pc = Cast<AController>(EmenyPawn->Controller);

				if (Pc != NULL)
				{
					EmenyNum++;

					if (EmenyNum < 19)
					{
						FVector vec = EmenyPawn->GetActorLocation();
						vec.Z += Canvas->SizeY*0.22f;
						FVector post = Project(vec);
						float width, height = 0.0f;
						GetTextSize("CHINA_CEO", width, height);
						DrawText("CHINA_CEO", FLinearColor(1, 0.2, 0.2, 1), post.X , post.Y, NULL, 1.2);

//						FString sLocation = FString::SanitizeFloat(EmenyPawn->GetActorLocation().X) + " " + FString::SanitizeFloat(EmenyPawn->GetActorLocation().Y) + " " + FString::SanitizeFloat(EmenyPawn->GetActorLocation().Z);
//						GetTextSize(sLocation, width, height, NormalFont);
//						DrawText(sLocation, EnemyColor, post.X - width*0.5f, post.Y, NormalFont, 1.2);

						vec.Z -= 17;
						post = Project(vec);
						GetTextSize(EmenyPawn->fsName, width, height);
						DrawText(EmenyPawn->fsName, EnemyColor, post.X , post.Y, NULL, 1.1);

//						FString sGUID = FString::SanitizeFloat(EmenyPawn->nGUID);
//						GetTextSize(sGUID, width, height, NormalFont);
//						DrawText(sGUID, EnemyColor, post.X - width*0.5f, post.Y, NormalFont, 1.2);

						vec.Z -= 23;
						post = Project(vec);
						HealthDynamicMaterial[EmenyNum]->SetScalarParameterValue("Current health", EmenyPawn->Health / EmenyPawn->MaxHealth * 100);
						DrawMaterialSimple(HealthDynamicMaterial[EmenyNum], post.X - fHealthOffsetX, post.Y, fHealthWidth, fHealthHeight, 1);
					}
				}
			}
		}
	}
}

void AEKHUD::NotifyOutOfAmmo()
{
	NoAmmoNotifyTime = GetWorld()->GetTimeSeconds();
}

void AEKHUD::NotifyEnemyHit()
{
	LastEnemyHitTime = GetWorld()->GetTimeSeconds();
}

void AEKHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawName();
	//DrawLogo();
	//DrawIcon();

	// 最后画
	//DrawMap();
}

void AEKHUD::DrawDebugInfoString(const FString& Text, float PosX, float PosY, bool bAlignLeft, bool bAlignTop, const FColor& TextColor)
{
#if !UE_BUILD_SHIPPING
	float SizeX, SizeY;
	Canvas->StrLen(NormalFont, Text, SizeX, SizeY);

	const float UsePosX = bAlignLeft ? PosX : PosX - SizeX;
	const float UsePosY = bAlignTop ? PosY : PosY - SizeY;

	const float BoxPadding = 5.0f;

	FColor DrawColor(HUDDark.R, HUDDark.G, HUDDark.B, HUDDark.A * 0.2f);
	const float X = UsePosX - BoxPadding * ScaleUI;
	const float Y = UsePosY - BoxPadding * ScaleUI;
	FCanvasTileItem TileItem( FVector2D( X, Y ), FVector2D( (SizeX + BoxPadding * 2.0f) * ScaleUI, (SizeY + BoxPadding * 2.0f) * ScaleUI ), DrawColor );
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );

	FCanvasTextItem TextItem( FVector2D( UsePosX, UsePosY), FText::FromString( Text ), NormalFont, TextColor );
	TextItem.EnableShadow( FLinearColor::Black );
	TextItem.FontRenderInfo = ShadowedFont;
	TextItem.Scale = FVector2D( ScaleUI, ScaleUI );
	Canvas->DrawItem( TextItem );
#endif
}

void AEKHUD::DrawDeathMessages()
{
	if (PlayerOwner == NULL)
	{
		return;
	}
	
	float OffsetX = 20;
	float OffsetY = 20;

	Canvas->SetDrawColor(FColor::White);
	float DeathMsgsPosX = Canvas->OrgX + Offset * ScaleUI;
	float DeathMsgsPosY = Canvas->ClipY - (OffsetY + DeathMessagesBg.VL) * ScaleUI;
	FVector Scale(ScaleUI, ScaleUI, 0.f);
	// hardcoded value to make sure the box is big enough to hold 16 W's for both players' names
	Scale.X *= 1.85;
	Canvas->DrawScaledIcon(DeathMessagesBg, DeathMsgsPosX, DeathMsgsPosY, Scale);

	const FColor BlueTeamColor = FColor(70, 70, 152, 255);
	const FColor RedTeamColor = FColor(152, 70, 70, 255);
	const FColor OwnerColor = HUDLight;

	const FString KilledText = "";
	FVector2D KilledTextSize(0.0f, 0.0f);

	const float GameTime = GetWorld()->GetTimeSeconds();
	const float LinePadding = 6.0f;
	const float BoxPadding = 2.0f;
	const float MaxLineX = 300.0f;
	const float InitialX = Offset * 2.0f * ScaleUI;
	const float InitialY = DeathMsgsPosY + (DeathMessagesBg.VL - Offset * 2.5f) * ScaleUI ;

	// draw messages
	float CurrentY = InitialY;

	Canvas->StrLen(NormalFont, KilledText, KilledTextSize.X, KilledTextSize.Y);
}

//void AEKHUD::NotifyHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator)
//{
//	const float CurrentTime = GetWorld()->GetTimeSeconds();
//	
//	LastHitTime = CurrentTime;
//}

void AEKHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	bIsScoreBoardVisible = false;
}

void AEKHUD::MakeUV(FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL)
{
	if (Icon.Texture)
	{
		const float Width = Icon.Texture->GetSurfaceWidth();
		const float Height = Icon.Texture->GetSurfaceHeight();
		UV0 = FVector2D(U / Width, V / Height);
		UV1 = UV0 + FVector2D(UL / Width, VL / Height);
	}
}

void AEKHUD::AddMatchInfoString(const FCanvasTextItem InInfoItem )
{
	InfoItems.Add(InInfoItem);
}

float AEKHUD::ShowInfoItems(float YOffset, float ScaleUI, float TextScale)
{
	float Y = YOffset;
	float CanvasCentre = Canvas->ClipX / 2.0f;

	for (int32 iItem = 0; iItem < InfoItems.Num() ; iItem++)
	{
		float X = 0.0f;
		float SizeX, SizeY; 
		Canvas->StrLen(InfoItems[iItem].Font, InfoItems[iItem].Text.ToString(), SizeX, SizeY);
		X = CanvasCentre - ( SizeX * InfoItems[iItem].Scale.X)/2.0f;
		Canvas->DrawItem(InfoItems[iItem], X, Y);
		Y += SizeY * InfoItems[iItem].Scale.Y;
	}
	return Y;
}


void AEKHUD::DrawLogo()
{
	FVector2D vec2D = FVector2D(Canvas->SizeX*0.1, Canvas->SizeY*0.9);
	this->DrawText("EasyKit Runtime", FColor::White, vec2D.X, vec2D.Y, NULL, 2);
}

void AEKHUD::DrawIcon()
{
	DrawTextureSimple(IocnTexture, 0, 0, 0.5f);
}

void AEKHUD::DrawButton(FVector2D inPostinon, FVector2D inSize)
{
	DrawTextureSimple(HUDButton, inPostinon.X, inPostinon.Y);

	float width, height;

	GetTextSize("Junmp", width, height, NormalFont);
	DrawText("Junmp", FColor(1, 1, 1, 1), inPostinon.X - width*0.5f, inPostinon.Y - height*0.5f, NormalFont, 1.2);

	AddHitBox(inPostinon, inSize, "Junmp", true, 5);
}

void AEKHUD::DrawMap()
{
	AEKCharacter* MyPawnPC = Cast<AEKCharacter>(GetOwningPawn());
	if (MyPawnPC)
	{
		if (MyPawnPC->bOpenMap == true)
		{
			FVector vec = MyPawnPC->GetActorLocation();
			FVector2D PlayerStartPont = FVector2D(63779, 42256);

			float SizeX = 1280;
			float SizeY = 720;

			SizeX = Canvas->SizeX / SizeX;
			SizeY = Canvas->SizeY / SizeY;

			float x = (vec.X + PlayerStartPont.X)*0.00001f;
			float y = (vec.Y - PlayerStartPont.Y)*0.00001f;

			UE_LOG(LogScript, Warning, TEXT("Canvas SizeY %d"), Canvas->SizeX);
			UE_LOG(LogScript, Warning, TEXT("Canvas SizeX %d"), Canvas->SizeY);

			if (Canvas->SizeX == 1366 && Canvas->SizeY == 768)
			{
				DrawTextureSimple(MapTexture, -Canvas->SizeX*(0.03 + x*2.05f), -Canvas->SizeY*(0.74 + y*2.25f), 1);
				DrawTextureSimple(HUDMapStar, Canvas->SizeX*0.5, Canvas->SizeY*0.5, 0.8);
			}
			else
			{
				DrawTextureSimple(MapTexture, -Canvas->SizeX*(0.15 + x), -Canvas->SizeY*(0.81 + y)*SizeY, 1.2);
				DrawTextureSimple(HUDMapStar, Canvas->SizeX*0.5, Canvas->SizeY*0.5, 0.8);
			}

		}
	}
}

void AEKHUD::ReceiveHitBoxClick(const FName BoxName)
{
	Super::ReceiveHitBoxClick(BoxName);
}

#undef LOCTEXT_NAMESPACE
