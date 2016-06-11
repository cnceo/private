// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "BaseAnimInstance.h"

UBaseAnimInstance::UBaseAnimInstance()
	:m_fMaxAnimTime(0)
	, m_fFlowAnimTime(0)
{

}

UBaseAnimInstance::~UBaseAnimInstance()
{

}

void UBaseAnimInstance::OnAnimTick_Implementation(float fTime, const FString& AnimName)
{

}

void UBaseAnimInstance::OnAnimBegin_Implementation(float fTime, const FString& AnimName)
{

}

void UBaseAnimInstance::OnAnimEnd_Implementation(const FString& AnimName)
{

}

void UBaseAnimInstance::OnAnimTickBP(float fTime, const FString& AnimName)
{
	m_fFlowAnimTime += fTime;
	this->Execute_OnAnimTick(this, fTime, AnimName);
}

void UBaseAnimInstance::OnAnimBeginBP(float fTime, const FString& AnimName)
{
	m_fMaxAnimTime = fTime;
	m_fFlowAnimTime = 0;
	this->Execute_OnAnimBegin(this, fTime, AnimName);
}

void UBaseAnimInstance::OnAnimEndBP(const FString& AnimName)
{
	this->Execute_OnAnimEnd(this, AnimName);
}
