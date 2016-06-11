
#include "Easykit.h"
#include "EKLogManager.h"


FEKLogManager* FEKLogManager::g_pLogManager = nullptr;

FEKLogManager::FEKLogManager()
{
}

FEKLogManager::~FEKLogManager()
{
}

FEKLogManager* FEKLogManager::Instance()
{
	if (g_pLogManager == nullptr)
	{
		g_pLogManager = new FEKLogManager();
	}

	return g_pLogManager;
}


//　日志类型　日志内存　字体颜色　日志等级
void FEKLogManager::Log(EKLog::LogType inType, FString inStr, EKLog::LogLevel inLevel, FColor inColor)
{
	switch (inLevel)
	{
	case EKLog::LogLevel::Debug:
	{
		LogofDebug(inType, inStr, inColor);
	}break;
	case EKLog::LogLevel::EasyKit:
	{
		LogofEasyKit(inType, inStr, inColor);
	}break;
	case EKLog::LogLevel::Releaes:
	{
		LogofReleaes(inType, inStr, inColor);
	}break;
	case EKLog::LogLevel::Shopping:
	{
		LogofShopping(inType, inStr, inColor);
	}break;
	}

}


void FEKLogManager::LogofDebug(EKLog::LogType inType, FString inStr, FColor inColor)
{
	switch (inType)
	{
	case EKLog::LogType::Warning:
	{
		UE_LOG(LogScript, Warning, TEXT(" %s "), *inStr);
	}break;
	case EKLog::LogType::Error:
	{
		UE_LOG(LogScript, Error, TEXT(" %s "), *inStr);
	}break;
	case EKLog::LogType::OutPut:
	{
		UE_LOG(LogScript, Log, TEXT(" %s "), *inStr);
	}break;
	case EKLog::LogType::Listening:
	{
		UE_LOG(LogScript, Display, TEXT(" %s "), *inStr);
	}break;
	}
}
void FEKLogManager::LogofEasyKit(EKLog::LogType inType, FString inStr, FColor inColor)
{
	switch (inType)
	{
	case EKLog::LogType::Warning:
	{
		//
	}break;
	case EKLog::LogType::Error:
	{
		//
	}break;
	case EKLog::LogType::OutPut:
	{
		//
	}break;
	case EKLog::LogType::Listening:
	{
		//
	}break;
	}
}
void FEKLogManager::LogofReleaes(EKLog::LogType inType, FString inStr, FColor inColor)
{
	switch (inType)
	{
	case EKLog::LogType::Warning:
	{
		//
	}break;
	case EKLog::LogType::Error:
	{
		//
	}break;
	case EKLog::LogType::OutPut:
	{
		//
	}break;
	case EKLog::LogType::Listening:
	{
		//
	}break;
	}
}
void FEKLogManager::LogofShopping(EKLog::LogType inType, FString inStr, FColor inColor)
{
	switch (inType)
	{
	case EKLog::LogType::Warning:
	{
		//
	}break;
	case EKLog::LogType::Error:
	{
		//
	}break;
	case EKLog::LogType::OutPut:
	{
		//
	}break;
	case EKLog::LogType::Listening:
	{
		//
	}break;
	}
}