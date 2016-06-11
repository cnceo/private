// Fill out your copyright notice in the Description page of Project Settings.
// add by yang
#pragma once
#include "CommonDefine.h"
#include "GameFramework/Character.h"
#include "ActiveActorInterface.h"
#include "DelayImpulseComponent.h"
#include "BaseAnimInstance.h"
#include "AttachWeapon.h"
#include "DataManger/PAUserHeroBaseData.h"
#include "BaseCharacter.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInputDelegate, int32, nButton);
UCLASS(BlueprintType, Blueprintable,HideDropdown,meta = (ShortTooltip = "Base Character"))
class PANDA_API ABaseCharacter : public ACharacter, public IActiveActorInterface
{
	GENERATED_BODY()

public:
	void OnAnimBegin_Implementation(float fTime, const FString& AnimName);
	void OnAnimTick_Implementation(float fTime, const FString& AnimName);
	void OnAnimEnd_Implementation(const FString& AnimName);
	void OnHit_Implementation(AActor* HitCauser, FsSkillHitResult sHitResult);

	// Anim Begin notify
	// fTime = fTotalTime
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnAnimBegin_BP(float fTime, const FString& AnimName);

	// Anim Tick notify
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnAnimTick_BP(float fTime, const FString& AnimName);
	
	// Anim end notify
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnAnimEnd_BP(const FString& AnimName);

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Allow actors to initialize themselves on the C++ side
	virtual void PostInitializeComponents() override;

public:

	//播放受击
	virtual void PlayHit(AActor* HitCauser, FsSkillHitResult sHitResult) {};

	//根据传入的受击效果,获取应当播放的效果
	virtual CHARACTER_SUB_STATE GetPlayHitSubState(CHARACTER_SUB_STATE emSubState) { return emSubState; }

	//播放死亡被击飞的效果
	virtual void PlayDeadFly(AActor* HitCauser) {};

	//设置被击飞(挑飞到空中)效果的相应数据
	virtual void PlayBeHitFly(AActor* HitCauser);

	//持续播放被击飞(挑飞到空中)效果
	virtual void OnBeHitFly(float DeltaSeconds);

	//打开角色物理
	void TurnOnRagDoll(bool bSetValue);

	//change weapon
	UFUNCTION(BlueprintCallable, Category = "CharacterWeapon")
	void EquipWeapon(FString ResPath,FName SocketName = TEXT(""));

	//call before Weapon has been changed
	virtual void PostEquipWeapon() {}

	//destroy weapon
	UFUNCTION(BlueprintCallable, Category = "CharacterWeapon")
	void UnequipWeapon();

	//获得当前使用的武器类型.空手返回 WEAPON_NONE
	UFUNCTION(BlueprintCallable, Category = "CharacterWeapon")
	CHARACTER_WEAPON_TYPE GetWeaponType();

	//根据collision类型获得组件
	UFUNCTION(BlueprintCallable, Category = "CollisionComponent")
	UShapeComponent* GetCollisionComponent(CHARACTER_COLLISION_TYPE emType);

	//获得检测球
	UFUNCTION(BlueprintCallable, Category = "CollisionComponent")
	UShapeComponent* GetCheckSphere(FName strTag = TEXT("CheckSphere"));

	//根据collision类型设置collision是否触发overlip事件
	UFUNCTION(BlueprintCallable, Category = "CollisionComponent")
	void SetCollisionOverlapEvents(CHARACTER_COLLISION_TYPE emType, bool bEvent);

	//转向Actor
	UFUNCTION(BlueprintCallable, Category = "Target")
	void TurnAtActor(AActor *pActor);

	//设置当前锁定的目标
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void SetTarget(ABaseCharacter* pTarget) { m_pTargetActor = pTarget; }

	//获得当前锁定的目标
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual ABaseCharacter* GetTarget() { return m_pTargetActor; }

	//清理当前锁定的目标
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void ClearTarget() { m_pTargetActor = nullptr; }

	//是否有锁定的目标
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual bool HasTarget() { return m_pTargetActor != nullptr; }

	//添加一个技能实例到角色
	UFUNCTION(BlueprintCallable, Category = "CharacterSkill")
	ASkillIInstance* AppendSkill(int32 nID);

	//使用技能实例
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	virtual bool PlaySkillInstance(ASkillIInstance* pSkill);

	//获得当前使用技能
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	ASkillIInstance*  GetCurSkill() { return m_pCurSkill; }

	//设置当前使用技能
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	void SetCurSkill(ASkillIInstance* pSkill) { m_pCurSkill = pSkill; }

	//清理当前使用技能
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	void  ClearCurSkill() { m_pCurSkill = nullptr; }

	//获得当前技能原子的蒙太奇
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	UAnimMontage* GetCurSkillMontage();

	//获得当前技能原子的动画序列
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	UAnimSequence* GetCurSkillSequence();

	//暂停AI
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	virtual void PauseAI() {}

	//继续启用AI
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	virtual void RestartAI() {}

public:
	// Get Current User State
	UFUNCTION(BlueprintCallable,Category = "CharacterState")
	CHARACTER_STATE GetState(){return m_emState;}

	// Get Current User State
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	CHARACTER_SUB_STATE GetSubState() { return m_emSubState; }
	
	// Get CharacterBaseData
	UFUNCTION(BlueprintCallable,Category = "CharacterState")
	FsPAPlayerHeroBaseData GetCharacterBaseData(){return m_tBaseData;}

	// Set Current User State
	UFUNCTION(Server,Reliable,WithValidation,BlueprintCallable,Category = "CharacterState")
	virtual void SetState(CHARACTER_SUB_STATE emSubState, CHARACTER_STATE emState = CHARACTER_STATE::CHARACTER_STATE_NONE);

	//给角色一个延迟受力
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void DelayImpulse(float fDelayTime, FVector vDirection, int32 nForce);

	//暂时未使用的方法.如果需要做攻击点的详细处理则需要实现此方法
	UFUNCTION(BlueprintCallable,Category = "SkillHit")
	void OnSkillHitEvent(CHARACTER_COLLISION_TYPE emType, AActor* pOtherActor, UPrimitiveComponent* pOtherComp, int32 OtherBodyIndex, bool FromSweep, FHitResult SweepResult);

public:

	//角色类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	CHARACTER_TYPE m_emType;

	//是否死亡
	UPROPERTY(BlueprintReadWrite, Category = "CharacterState")
	bool m_bDead;

	//当前是否进入战斗
	UPROPERTY(BlueprintReadWrite, Category = "CharacterState")
	bool m_bFighting;

protected:

	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	virtual void OnRep_State();

	UPROPERTY(replicatedUsing=OnRep_State)
	CHARACTER_STATE  m_emState;					//character state

	UPROPERTY(replicatedUsing = OnRep_State)
	CHARACTER_SUB_STATE m_emSubState;				//character sub state

	UPROPERTY(EditAnywhere,replicated)
	FsPAPlayerHeroBaseData m_tBaseData;				//character base data

	ABaseCharacter* m_pTargetActor;					//cur target actor.

	//当前使用的武器
	AAttachWeapon* m_CurWeapon;

	//检测球组件
	UShapeComponent* m_CheckSphere;

	//当前释放的技能
	ASkillIInstance* m_pCurSkill;

	//延迟受力组件
	class UDelayImpulseComponent* m_DelayImpulseComponent;

	//被击飞经过的时间
	float m_fBeHitFlyTime;

	//被击飞需要调整的角度
	float m_fAngle;

public:
	UFUNCTION(Server,Reliable,WithValidation)
	void RPCServerDumpPlayers();
	UFUNCTION(Client,Reliable)
	void RPCClientDumpPlayers();
};

