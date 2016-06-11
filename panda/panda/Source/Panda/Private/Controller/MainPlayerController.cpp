// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "MainPlayerController.h"
#include "Utils/PandaUtils.h"
#include "PandaGameInstance.h"
#include "WidgetBlueprintLibrary.h"
#include "PandaWidget_Bag1.h"
#include "ResDefine.h"

AMainPlayerController::AMainPlayerController()
	: m_pPlayer(nullptr)
{
	m_iscamera = false;
	for(int i = 0; i < (int32)PLAYER_KEY::PLAYER_KEY_MAX; ++i)
	{
		m_arrbPressedKey[i] = false;
	}
}

AMainPlayerController::~AMainPlayerController()
{

}

void AMainPlayerController::BeginPlayingState()
{
	InputComponent = NewObject<UInputComponent>(this,TEXT("Main_InputComponent"));
	InputComponent->RegisterComponent();
	check(InputComponent);

	InputComponent->BindAction("FangKuai",IE_Pressed,this,&AMainPlayerController::OnFangKuai);
	InputComponent->BindAction("FangKuai",IE_Released,this,&AMainPlayerController::OnFangKuaiEnd);

	InputComponent->BindAction("Quan",IE_Pressed,this,&AMainPlayerController::OnQuan);
	InputComponent->BindAction("Quan",IE_Released,this,&AMainPlayerController::OnQuanEnd);

	InputComponent->BindAction("SanJiao",IE_Pressed,this,&AMainPlayerController::OnSanJiao);
	InputComponent->BindAction("SanJiao",IE_Released,this,&AMainPlayerController::OnSanJiaoEnd);

	InputComponent->BindAction("Cha",IE_Pressed,this,&AMainPlayerController::OnCha);
	InputComponent->BindAction("Cha",IE_Released,this,&AMainPlayerController::OnChaEnd);

	InputComponent->BindAction("L1",IE_Pressed,this,&AMainPlayerController::OnL1);
	InputComponent->BindAction("L1",IE_Released,this,&AMainPlayerController::OnL1End);

	InputComponent->BindAction("R1",IE_Pressed,this,&AMainPlayerController::OnR1);
	InputComponent->BindAction("R1",IE_Released,this,&AMainPlayerController::OnR1End);

	InputComponent->BindAction("L2",IE_Pressed,this,&AMainPlayerController::OnL2);
	InputComponent->BindAction("L2",IE_Released,this,&AMainPlayerController::OnL2End);

	InputComponent->BindAction("R2",IE_Pressed,this,&AMainPlayerController::OnR2);
	InputComponent->BindAction("R2",IE_Released,this,&AMainPlayerController::OnR2End);

	InputComponent->BindAction("Shang", IE_Pressed, this, &AMainPlayerController::OnShang);
	InputComponent->BindAction("Shang", IE_Released, this, &AMainPlayerController::OnShangEnd);

	InputComponent->BindAction("Xia", IE_Pressed, this, &AMainPlayerController::OnXia);
	InputComponent->BindAction("Xia", IE_Released, this, &AMainPlayerController::OnXiaEnd);

	InputComponent->BindAction("Zuo", IE_Pressed, this, &AMainPlayerController::OnZuo);
	InputComponent->BindAction("Zuo", IE_Released, this, &AMainPlayerController::OnZuoEnd);

	InputComponent->BindAction("You", IE_Pressed, this, &AMainPlayerController::OnYou);
	InputComponent->BindAction("You", IE_Released, this, &AMainPlayerController::OnYouEnd);

	InputComponent->BindAxis("MoveForward",this,&AMainPlayerController::OnL3Y);
	InputComponent->BindAxis("MoveRight",this,&AMainPlayerController::OnL3X);

	InputComponent->BindAxis("TurnRate",this,&AMainPlayerController::OnR3X);
	InputComponent->BindAxis("LookUpRate",this,&AMainPlayerController::OnR3Y);

	InputComponent->BindAction("bag", IE_Pressed, this, &AMainPlayerController::OnBagOpen);
	InputComponent->BindAction("bag2", IE_Pressed, this, &AMainPlayerController::OnBagClose);
	InputComponent->BindAction("tab", IE_Pressed, this, &AMainPlayerController::OnTab);
	Super::PushInputComponent(InputComponent);

}

void AMainPlayerController::OnOpenACT()
{
	if (GGameInstance)
		GGameInstance->SafeGetUIManager()->OpenUMGAsset(UI_Dungeon_ACT);
}

void AMainPlayerController::OnCloseACT()
{
	if (GGameInstance)
		GGameInstance->SafeGetUIManager()->CloseUMGAsset(UI_Dungeon_ACT);
}

void AMainPlayerController::OnOpenTeam()
{
	if (GGameInstance)
		GGameInstance->SafeGetUIManager()->OpenUMGAsset(UI_CREATE_TEAM);
}

void AMainPlayerController::onCloseTeam()
{
	if (GGameInstance)
		GGameInstance->SafeGetUIManager()->CloseUMGAsset(UI_CREATE_TEAM);
}

void AMainPlayerController::OnOpenSelectRegion()
{
	if (GGameInstance)
		GGameInstance->SafeGetUIManager()->OpenUMGAsset(UI_Dungeon_SelectRegion);
}

void AMainPlayerController::OnCloseSelectRegion()
{
	if (GGameInstance)
		GGameInstance->SafeGetUIManager()->CloseUMGAsset(UI_Dungeon_SelectRegion);
}

void AMainPlayerController::OnBagOpen()
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		gameInstance->SafeGetUIManager()->OpenUMGAsset(TEXT("/Game/BPInstance/UI/bag/bag.bag_C"));
	}
	/*TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, UPandaWidget_Bag1::StaticClass(), true);*/
}

void AMainPlayerController::OnBagClose()
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		gameInstance->SafeGetUIManager()->CloseUMGAsset(TEXT("/Game/BPInstance/UI/bag/bag.bag_C"));
	}
}
void AMainPlayerController::OnTab()
{
	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance)
	{
		gameInstance->SafeGetUIManager()->OpenUMGAsset(TEXT("/Game/BPInstance/UI/Weapon/WeaponChange.WeaponChange_C"));
	}

// 	if (!m_iscamera)
// 	{
// 		auto gameInstance = UPandaGameInstance::Instance();
// 		if (gameInstance)
// 		{
// 			gameInstance->SafeGetUIManager()->OpenUMGAsset(TEXT("/Game/BPInstance/UI/Weapon/WeaponChange.WeaponChange_C"));
// 		}
// 		m_iscamera = true;
// 	}
// 	else
// 	{
// 		auto gameInstance = UPandaGameInstance::Instance();
// 		if (gameInstance)
// 		{
// 			gameInstance->SafeGetUIManager()->CloseUMGAsset(TEXT("/Game/BPInstance/UI/Weapon/WeaponChange.WeaponChange_C"));
// 		}
// 		m_iscamera = false;
// 	}

}
void AMainPlayerController::OnQuan()
{
	//J on keyboard
	UE_LOG(LogTemp,Warning,TEXT("--------i am J"));
	if(auto p=GetMainPlayer())p->RPCClientDumpPlayers();
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_QUAN, true))
	{
		if (GetMainPlayer())
		{
			if (GetMainPlayer()->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying)
			{
				GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_SKYATTACK));
			}
			else
			{
				GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_ATTACK));
			}
		}
	}
}

void AMainPlayerController::OnQuanEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_QUAN,false);
}

void AMainPlayerController::OnCha()
{
	//K on keyboard
	UE_LOG(LogTemp,Warning,TEXT("--------i am K"));
	if(auto p=GetMainPlayer())p->RPCServerDumpPlayers();
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_CHA, true))
	{

	}
}

void AMainPlayerController::OnChaEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_CHA,false);
}

void AMainPlayerController::OnFangKuai()
{
	//G on keyboard
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_FANGKUAI, true))
	{
		if (GetMainPlayer())GetMainPlayer()->OnJump(true);
	}
}

void AMainPlayerController::OnFangKuaiEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_FANGKUAI,false);
	if(GetMainPlayer())GetMainPlayer()->OnJump(false);
}

void AMainPlayerController::OnSanJiao()
{
	if (GetMainPlayer()->TargetNPC)
	{
		if (GetMainPlayer())
			GetMainPlayer()->Talk2Npc();
	}
	else
	{
		//H on keyboard
		if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_SANJIAO, true))
		{
			GetMainPlayer()->ChangeStateToDefence();
		}
	}

}

void AMainPlayerController::OnSanJiaoEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_SANJIAO,false);
	GetMainPlayer()->ClearDefence();
}

void AMainPlayerController::OnL1()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_L1,true);
	//UPandaUtils::SlowCamera(GetMainPlayer(), 0.2f);
}

void AMainPlayerController::OnL1End()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_L1,false);
	//UPandaUtils::SlowCamera(GetMainPlayer(), 1.0f);
}

void AMainPlayerController::OnR1()
{
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_R1, true))
	{
		if (GetMainPlayer())
		{
			GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_CHASE));
		}
	}

}

void AMainPlayerController::OnR1End()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_R1,false);
}

void AMainPlayerController::OnL2()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_L2,true);
	GetMainPlayer()->SetTarget(GetMainPlayer()->FindTarget());
	if(GetMainPlayer()->HasTarget()) GetMainPlayer()->TurnAtTarget();
	UE_LOG(LogTemp, Log, TEXT("OnL2() !!!"));
}

void AMainPlayerController::OnL2End()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_L2,false);
	GetMainPlayer()->ClearTarget();
}

void AMainPlayerController::OnR2()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_R2,true);
	if(GetMainPlayer())GetMainPlayer()->setMaxWalkSpeed(800);
}

void AMainPlayerController::OnR2End()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_R2,false);
	if(GetMainPlayer())GetMainPlayer()->setMaxWalkSpeed(350);
}

void AMainPlayerController::OnShang()
{
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_SHANG, true))
	{
		if (GetMainPlayer())
		{
			GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP1));
		}
	}
}

void AMainPlayerController::OnShangEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_SHANG, false);
}

void AMainPlayerController::OnXia()
{
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_XIA, true))
	{
		if (GetMainPlayer())
		{
			GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP2));
		}
	}
}

void AMainPlayerController::OnXiaEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_XIA, false);
}

void AMainPlayerController::OnZuo()
{
	if(!OnPressedKey(PLAYER_KEY::PLAYER_KEY_ZUO, true))
	{
		if (GetMainPlayer())
		{
			GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP3));
		}
	}
}

void AMainPlayerController::OnZuoEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_ZUO, false);
}

void AMainPlayerController::OnYou()
{
	if (!OnPressedKey(PLAYER_KEY::PLAYER_KEY_YOU, true))
	{
		if (GetMainPlayer())
		{
			GetMainPlayer()->PlaySkillInstance(GetMainPlayer()->GetBaseSkill(PLAYER_SKILL_TYPE::PLAYER_SKILL_TEMP4));
		}
	}
}

void AMainPlayerController::OnYouEnd()
{
	OnPressedKey(PLAYER_KEY::PLAYER_KEY_YOU, false);
}


//前/后移动
void AMainPlayerController::OnL3Y(float Value)
{
	if (Value > -0.0001f && Value < 0.0001f) return;

	if (GetMainPlayer() && GetMainPlayer()->ChangeStateToMove())
	{
		FTimerDelegate MovedTimer;
		MovedTimer.BindUObject(this, &AMainPlayerController::MovedCallback);
		GetWorld()->GetTimerManager().SetTimer(m_MoveHandle, MovedTimer, 0.1f, false);

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X)/**0.001*/;
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
		if (GetMainPlayer()->HasTarget()) GetMainPlayer()->TurnAtTarget();
	}

}

//右/左移动
void AMainPlayerController::OnL3X(float Value)
{
	if (Value > -0.0001f && Value < 0.0001f) return;

	if (GetMainPlayer() && GetMainPlayer()->ChangeStateToMove())
	{
		FTimerDelegate MovedTimer;
		MovedTimer.BindUObject(this, &AMainPlayerController::MovedCallback);
		GetWorld()->GetTimerManager().SetTimer(m_MoveHandle, MovedTimer, 0.1f, false);

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector 
		const FVector Direction = (FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y))/**0.001*/;
		// add movement in that direction
		GetMainPlayer()->AddMovementInput(Direction, Value);
		if (GetMainPlayer()->HasTarget()) GetMainPlayer()->TurnAtTarget();
	}
	else
	{
		if (GetMainPlayer() && GetMainPlayer()->GetState() == CHARACTER_STATE::CHARACTER_STATE_SKILL
			&& GetMainPlayer()->GetCurSkill() && GetMainPlayer()->GetCurSkill()->IsBeFuse() && !GetMainPlayer()->HasTarget())
		{
			GetMainPlayer()->AddControllerYawInput(Value * 30.0f * GetWorld()->GetDeltaSeconds());
			const FRotator Rotation = GetMainPlayer()->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			GetMainPlayer()->SetActorRotation(YawRotation);
		}

	}
}

//调整左右视角
void AMainPlayerController::OnR3X(float Rate)
{
	
	if(Rate>-0.0001f && Rate<0.0001f) return;
	if (GetMainPlayer()->HasTarget())
	{
		GetMainPlayer()->SetTarget(GetMainPlayer()->FindTarget(Rate));
		return;
	}

	if (GetMainPlayer())GetMainPlayer()->AddControllerYawInput(Rate * 30.0f * GetWorld()->GetDeltaSeconds());

	const FRotator Rotation = GetMainPlayer()->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	GetMainPlayer()->SetActorRotation(YawRotation);
}

//调整上下视角
void AMainPlayerController::OnR3Y(float Rate)
{
	if(Rate>-0.0001f && Rate<0.0001f) return;
	if (GetMainPlayer())GetMainPlayer()->AddControllerPitchInput(Rate * 30.0f * GetWorld()->GetDeltaSeconds());
}

APlayerCharacter* AMainPlayerController::GetMainPlayer()
{
	if (!m_pPlayer)
		m_pPlayer = Cast<APlayerCharacter>(GetPawn());

	return m_pPlayer;
}

void AMainPlayerController::MovedCallback()
{
	if (GetMainPlayer() && GetMainPlayer()->GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_MOVE)
	{
		GetMainPlayer()->SetState(CHARACTER_SUB_STATE::SUB_STATE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_NORMAL);
	}

}

bool AMainPlayerController::OnPressedKey(PLAYER_KEY emCurKey, bool bPressed)
{
	m_arrbPressedKey[(int32)emCurKey] = bPressed;
	if(bPressed)
	{
		if (CheckNextSkill(emCurKey))
			return true;

		return CheckComponentKey();
	}

	return false;
}

bool AMainPlayerController::CheckComponentKey()
{
	if(m_arrbPressedKey[(int32)PLAYER_KEY::PLAYER_KEY_QUAN] && m_arrbPressedKey[(int32)PLAYER_KEY::PLAYER_KEY_CHA])
	{
		UE_LOG(LogTemp,Log,TEXT("QUAN+CHA !!!"));
	}

	return false;
}

bool AMainPlayerController::CheckNextSkill(PLAYER_KEY emCurKey)
{
	if (GetMainPlayer() && GetMainPlayer()->GetCurSkill())
	{
		int32 nIndex = GetMainPlayer()->GetCurSkill()->CheckPlayNextByInputKey(m_arrbPressedKey, emCurKey);
		if (nIndex > 0)
		{
			return GetMainPlayer()->GetCurSkill()->PlayNextSkill(nIndex);
		}
	}

	return false;
}