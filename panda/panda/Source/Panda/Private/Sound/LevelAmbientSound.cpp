// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "LevelAmbientSound.h"
#include "Manager/DataManager.h"
#include "Sound/SoundCue.h"

ALevelAmbientSound::ALevelAmbientSound()
	: m_pSound(nullptr)
{

	FString DirPathString = FPaths::GameContentDir();
	auto data = DirPathString.GetCharArray();
	auto stringData = data.GetData();
	DirPathString.Append("Sound/Starter_Birds01");
	data = DirPathString.GetCharArray();
	stringData = data.GetData();
	if(GWorld != nullptr)
	{
		auto w = GWorld->GetCurrentLevel();
	}
	//if (world != nullptr)
	//{
	//	auto mapName =  world->GetName();
	//	mapName;
	//}
	static ConstructorHelpers::FObjectFinder<USoundBase> USoundBase(TEXT("/Game/Sound/Starter_Birds01.Starter_Birds01"));
	m_pSound = USoundBase.Object;
}

ALevelAmbientSound::~ALevelAmbientSound()
{

}

void ALevelAmbientSound::BeginPlay()
{
	//TArray<uint8> rawFileData;
	//FFileHelper::LoadFileToArray(rawFileData, TEXT("/Game/Sound/Starter_Birds01.Starter_Birds01"));
	//AAmbientSound* InCarGear = CreateDefaultSubobject<AAmbientSound>(TEXT("AmbientSound"));
	GetAudioComponent()->SetSound(m_pSound);
	GetAudioComponent()->Play();
	auto world = GetWorld();
	if(GWorld == world)
	{
		int aa = 10;
	}
	if(world != nullptr)
	{
		auto mapName =  world->GetName();
		mapName;
	}
	//PANDA_DataManager;
	//FString DirPathString = FPaths::GameContentDir();
	//auto data = DirPathString.GetCharArray();
	//auto stringData = data.GetData();
	//DirPathString.Append("Sound/Starter_Birds01");
	//data = DirPathString.GetCharArray();
	//stringData = data.GetData();
	////static ConstructorHelpers::FObjectFinder<USoundCue> SoundCue(TEXT("/Game/Sound/dead_daodi_Cue.dead_daodi_Cue"));
	////static ConstructorHelpers::FObjectFinder<USoundCue> SoundCue(TEXT("E:/panda/Content/Sound/Starter_Birds01"));
	//static ConstructorHelpers::FObjectFinder<USoundCue> SoundCue(TEXT("/Game/Sound/dead_daodi_Cue.dead_daodi_Cue"));
	//this->GetAudioComponent()->SetSound(SoundCue.Object);
	////USoundBase* p = CreateDefaultSubobject<USoundBase>(TEXT("E:/panda/Content/Sound/dead_daodi_Cue.dead_daodi_Cue");
}
