// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "Engine.h"
#include "MonsterCharacter.h"
#include "PlayerCharacter.h"



AMonsterCharacter::AMonsterCharacter()
{
	m_emType = CHARACTER_TYPE::CHARACTER_TYPE_MONSTER;
}

AMonsterCharacter::~AMonsterCharacter()
{

}

void AMonsterCharacter::OnHit_Implementation(AActor* HitCauser, FsSkillHitResult sHitResult)
{
	if (sHitResult.sTableData.bDamage)
	{

		//是否防御此次攻击
		if (GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_DEFENCE && sHitResult.sTableData.nHitLevel < int32(EFFECT_HIT_LEVEL::EFFECT_HIT_POFANG))
		{
			return;
		}

		//是否触发架招
		if (sHitResult.sTableData.nHitLevel < int32(EFFECT_HIT_LEVEL::EFFECT_HIT_POJIAZHAO) && GetCurSkill())
		{
			if (GetCurSkill()->IsBeCounterattack() && GetCurSkill()->PlayNextSkill())
			{
				return;
			}
		}

		//是否闪避此次攻击
		if (GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_DODGE && sHitResult.sTableData.nHitLevel < int32(EFFECT_HIT_LEVEL::EFFECT_HIT_POSHANBI))
		{
			return;
		}

	}

	//属性更改
	if (!m_bDead)
	{
		m_tBaseData.fHP += sHitResult.nCurHP;
		m_tBaseData.fMP += sHitResult.nCurMP;
		// += sHitResult.nCurPower;
	}

	//死亡设置
	if (!m_bDead && m_tBaseData.fHP <= 0)
	{
		m_bDead = true;
	}

	//死亡判断
	if (m_bDead)
	{
		//强制触发连击
		if (sHitResult.sTableData.nBreak >= 0 && sHitResult.sTableData.bCombo)
		{
			PlayHit(HitCauser, sHitResult);
		}
		//死亡处理
		else
		{
			CHARACTER_SUB_STATE emHit = CHARACTER_SUB_STATE(sHitResult.sTableData.nSubState);
			if (emHit == CHARACTER_SUB_STATE::SUB_STATE_BEHEAVY || emHit == CHARACTER_SUB_STATE::SUB_STATE_BEHITFLY)
			{
				PlayDeadFly(HitCauser);
			}
			else
			{
				SetState(CHARACTER_SUB_STATE::SUB_STATE_DIE_NORMAL, CHARACTER_STATE::CHARACTER_STATE_DIE);
			}

			//通知主角任务杀怪计数(临时的方法)
			auto pPlayer = Cast<APlayerCharacter>(HitCauser);
			auto pMainPlayer = Cast<APlayerCharacter>(GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
			if (pPlayer && pPlayer == pMainPlayer)
			{
				pPlayer->GetQuestHandler()->KillNPC(GetNPCId());
			}
						
		}
	}
	else
	{
		//打断值满足
		if (sHitResult.sTableData.nBreak >= 0)
		{
			PlayHit(HitCauser, sHitResult);
		}
	}

}

CHARACTER_SUB_STATE AMonsterCharacter::GetPlayHitSubState(CHARACTER_SUB_STATE emSubState)
{
	if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT1 || emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT2)
	{
		if (GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Falling)
			return CHARACTER_SUB_STATE::SUB_STATE_BEHIT1;
	}
	else if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_HITFALL)
	{
		if (GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Falling)
			return CHARACTER_SUB_STATE::SUB_STATE_TUMBLE;
	}

	return emSubState;
}

void AMonsterCharacter::PlayHit(AActor* HitCauser, FsSkillHitResult sHitResult)
{
	CHARACTER_SUB_STATE emSubState = GetPlayHitSubState(CHARACTER_SUB_STATE(sHitResult.sTableData.nSubState));
	UE_LOG(LogTemp, Warning, TEXT("PlayHit SubState=%d, GetPlayHitSubState=%d"), sHitResult.sTableData.nSubState, (int32)emSubState);
	PauseAI();

	//普通受伤
	if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHIT1 || emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHIT2)
	{
		CHARACTER_SUB_STATE emNextState = GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_BEHIT1 ? CHARACTER_SUB_STATE::SUB_STATE_BEHIT2 : CHARACTER_SUB_STATE::SUB_STATE_BEHIT1;
		SetState(emNextState, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
	}
	//被重击
	else if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHEAVY)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
		SetState(CHARACTER_SUB_STATE::SUB_STATE_BEHEAVY, CHARACTER_STATE::CHARACTER_STATE_BEHIT);

	}
	//被击飞(挑飞到高空)
	else if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_BEHITFLY)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_BEHITFLY, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
		PlayBeHitFly(HitCauser);
	}
	//空中受击
	else if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT1 || emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT2)
	{
		CHARACTER_SUB_STATE emNextState = GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT1 ? CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT2 : CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT1;
		SetState(emNextState, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
	}
	//空中被击落
	else if (emSubState == CHARACTER_SUB_STATE::SUB_STATE_FLY_HITFALL)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_FLY_HITFALL, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
	}

	if (sHitResult.sTableData.nForce > 0)
	{
		FRotationMatrix CauserMatrix(HitCauser->GetActorRotation());
		FVector Impulse = FVector(CauserMatrix.TransformVector(sHitResult.sTableData.vDirection)).GetSafeNormal() * sHitResult.sTableData.nForce;
		GetCharacterMovement()->AddImpulse(Impulse, true);
	}

	if (sHitResult.sTableData.vVelocity != FVector::ZeroVector)
	{
		FRotationMatrix CauserMatrix(HitCauser->GetActorRotation());
		FVector vVelocity = FVector(CauserMatrix.TransformVector(sHitResult.sTableData.vVelocity));
		GetCharacterMovement()->Velocity = vVelocity;
	}

}

void AMonsterCharacter::Landed(const FHitResult& Hit)
{
	//死亡飞行着陆
	if (GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_DIE_FLY)
	{
		TurnOnRagDoll(true);
	}
	//被重击后着陆
	else if (GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_BEHEAVY)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Block);
		SetState(CHARACTER_SUB_STATE::SUB_STATE_TUMBLE, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
	}
	//被击飞到空中后着陆
	else if (GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_BEHITFLY || GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_HITFLY_FLOATING
			|| GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT1 || GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_FLY_BEHIT2
			|| GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_HITFLY_FALLING)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_REEL1, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
		DelayImpulse(0.3f, FVector(-100, 0, 0), 2000);
	}
	else if (GetSubState() == CHARACTER_SUB_STATE::SUB_STATE_FLY_HITFALL)
	{
		SetState(CHARACTER_SUB_STATE::SUB_STATE_FLY_HITROLL, CHARACTER_STATE::CHARACTER_STATE_BEHIT);
	}

}

void AMonsterCharacter::PlayDeadFly(AActor* HitCauser)
{
	Super::PlayDeadFly(HitCauser);
	if (HitCauser)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
		FRotationMatrix CauserMatrix(HitCauser->GetActorRotation());
		FVector Impulse = FVector(CauserMatrix.TransformVector(FVector(100, 0, 80))).GetSafeNormal() * 1000;
		GetCharacterMovement()->AddImpulse(Impulse, true);
		SetState(CHARACTER_SUB_STATE::SUB_STATE_DIE_FLY, CHARACTER_STATE::CHARACTER_STATE_DIE);
	}

}
