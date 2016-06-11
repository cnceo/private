// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma  once


#include "EKTypes.h"
#include "EKHUD.generated.h"


UCLASS()
class EASYKIT_API AEKHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY()
	UTexture2D* HUDButton;
	UPROPERTY()
	UTexture2D* HUDButton_Pressed;

	UPROPERTY()
	UMaterialInstanceDynamic*  HealthDynamicMaterial[20];

	/** Main HUD update loop. */
	virtual void DrawHUD() override;

	/**
	 * Sent from pawn hit, used to calculate hit notification overlay for drawing.
	 *
	 * @param	DamageTaken		The amount of damage.
	 * @param	DamageEvent		The actual damage event.
	 * @param	PawnInstigator	The pawn that did the damage.
	 */
	//void NotifyHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator);

	/** Sent from ShooterWeapon, shows NO AMMO text. */
	void NotifyOutOfAmmo();

	/** Notifies we have hit the enemy. */
	void NotifyEnemyHit();
		
protected:
	/** Floor for automatic hud scaling. */
	static const float MinHudScale;

	/** Lighter HUD color. */
	FColor HUDLight;

	/** Darker HUD color. */
	FColor HUDDark;

	/** When we got last notice about out of ammo. */
	float NoAmmoNotifyTime;

	/** How long notice is fading out. */
	float NoAmmoFadeOutTime;

	/** Most recent hit time, used to check if we need to draw hit indicator at all. */
	float LastHitTime;

	/** How long till hit notify fades out completely. */
	float HitNotifyDisplayTime;

	/** When we last time hit the enemy. */
	float LastEnemyHitTime;

	/** How long till enemy hit notify fades out completely. */
	float LastEnemyHitDisplayTime;

	/** Icons for hit indicator. */
	UPROPERTY()
	FCanvasIcon HitNotifyIcon[8];

	/** Match timer and player position background icon. */
	UPROPERTY()
	FCanvasIcon TimePlaceBg;

	/** Primary weapon background icon. */
	UPROPERTY()
	FCanvasIcon PrimaryWeapBg;

	/** Secondary weapon background icon */
	UPROPERTY()
	FCanvasIcon SecondaryWeapBg;

	/** On crosshair indicator that we hit someone. */
	UPROPERTY()
	FCanvasIcon HitNotifyCrosshair;

	/** Death messages background icon. */
	UPROPERTY()
	FCanvasIcon DeathMessagesBg;

	/** Timer icon. */
	UPROPERTY()
	FCanvasIcon TimerIcon;

	/** Podium icon. */
	UPROPERTY()
	FCanvasIcon PlaceIcon;

	/** UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;

	/** Current animation pulse value. */
	float PulseValue;

	/** FontRenderInfo enabling casting shadow.s */
	FFontRenderInfo ShadowedFont;

	/** texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDMainTexture;
	UPROPERTY()
	UTexture2D* HUDMapStar;

	/** Large font - used for ammo display etc. */
	UPROPERTY()
	UFont* BigFont;

	/** Normal font - used for death messages and such. */
	UPROPERTY()
	UFont* NormalFont;

	/** General offset for HUD elements. */
	float Offset;

	/** Is the scoreboard widget on screen? */
	uint32 bIsScoreBoardVisible:1;

	/** Scoreboard widget overlay. */
	TSharedPtr<class SOverlay>	ScoreboardWidgetOverlay;

	/** Scoreboard widget container - used for removing */
	TSharedPtr<class SWidget> ScoreboardWidgetContainer;

	/** Chatbox widget. */
	TSharedPtr<class SChatWidget> ChatWidget;

	/** Array of information strings to render (Waiting to respawn etc) */
	TArray<FCanvasTextItem> InfoItems;

	/** Called every time game is started. */
	virtual void PostInitializeComponents() override;

	/** 
	 * Converts floating point seconds to MM:SS string.
	 *
	 * @param TimeSeconds		The time to get a string for.
	 */
	FString GetTimeString(float TimeSeconds);

	/** Draw death messages. */
	void DrawDeathMessages();

	/** Temporary helper for drawing text-in-a-box. */
	void DrawDebugInfoString(const FString& Text, float PosX, float PosY, bool bAlignLeft, bool bAlignTop, const FColor& TextColor);

	/** helper for getting uv coords in normalized top,left, bottom, right format */
	void MakeUV(FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL);

	/*
	 * Create the chat widget if it doesn't already exist.
	 *
	 * @return		true if the widget was created.
	 */
	bool TryCreateChatWidget();

	/*
	 * Add information string that will be displayed on the hud. They are added as required and rendered together to prevent overlaps 
	 * 
	 * @param InInfoString	InInfoString
	*/
	void AddMatchInfoString(const FCanvasTextItem InfoItem);

	/*
	* Render the info messages.
	*
	* @param YOffset	YOffset from top of canvas to start drawing the messages
	* @param ScaleUI	UI Scale factor
	* @param TextScale	Text scale factor
	*
	* @returns The next Y position to draw any further strings
	*/
	float ShowInfoItems(float YOffset, float ScaleUI, float TextScale);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// 我们自己的
	//
	/** 头像IOCN. */
	UPROPERTY()
	UTexture2D* IocnTexture;

	UPROPERTY()
	UTexture2D* MapTexture;

	virtual void DrawLogo();
	virtual void DrawIcon();
	/** 画血条 */
	virtual void DrawHealth();
	/** 画名字 */
	virtual void DrawName();
	/** 画地图 */
	virtual void DrawMap();
	/** 画按钮 */
	virtual void DrawButton(FVector2D inPostinon, FVector2D inSize);

	void ReceiveHitBoxClick(const FName BoxName);
};