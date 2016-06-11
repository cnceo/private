// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "FileManager.h"
#include "QuestManager.h"
//#include "JsonObject.h"
//#include "JsonReader.h"
//#include "JsonValue.h"
//#include "JsonSerializer.h"
#include "Json.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"






void UQuestManager::Init()
{
	addTask();
	GetDatafromJson();

}

void UQuestManager::GetDatafromJson()
{
	//FString ManifestText;
	//FString  FilePaths = FPaths::GameContentDir();
	//FilePaths += TEXT("Conf/task.json");
	//if (FFileHelper::LoadFileToString(ManifestText, *FilePaths))
	//{
	//	TSharedPtr<FJsonObject> DescriptorObject = MakeShareable(new FJsonObject());
	//	TSharedRef<TJsonReader<TCHAR>>& Reader = TJsonReaderFactory<TCHAR>::Create(ManifestText);
	//	if (FJsonSerializer::Deserialize(Reader, /*out*/ DescriptorObject) && DescriptorObject.IsValid())
	//	{

	//	}
	//	
	//}
	FString FileContents;
	FString CredentialsFile = FPaths::GameContentDir()+TEXT("Game/Conf/task1.json");
	if (!FFileHelper::LoadFileToString(FileContents, *CredentialsFile))
	{
		//UE_LOG(LogLocalizationService, Log, TEXT("Failed to load OneSky credentials file %s."), *CredentialsFile);
		return;
	}

	//parse as JSON
	TSharedPtr<FJsonObject> JSONObject;

	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(FileContents);
	TSharedPtr<FJsonValue>  JsonValue;

	if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
	{
		TArray<FTestMyStruct>  myStruct;
		FTestMyStruct testStruct;
		const TSharedPtr<FJsonObject>* obj;

		JSONObject->TryGetObjectField(TEXT("18"), obj);
		FJsonObjectConverter::JsonObjectToUStruct<FTestMyStruct>(obj->ToSharedRef(), &testStruct, 0, 0);
		//bool b = FJsonObjectConverter::JsonObjectToUStruct<FTestMyStruct>(JSONObject, &testStruct, 0, 0);
		//bool b = FJsonObjectConverter::JsonArrayStringToUStruct(Reader->GetValueAsString(), &myStruct, 0, 0);


		return;
	}
}

void UQuestManager::addTask()
{
	//FCondition_KillMonster con_killMonster;
	//con_killMonster.m_KillAmount = 10;
	//con_killMonster.m_monsterId = 30001;
	//m_Conditions.Add(con_killMonster);

	//FPrecondition preCondition;
	//preCondition.LevelLimit = 10;
	//m_Preconditions.Add(preCondition);

	//FsTaskInfo taskInfo;
	//taskInfo.TaskId = 10001;
	//taskInfo.TaskName = FString(TEXT("村民的烦恼"));
	//taskInfo.Description = FString(TEXT("村子附近总有一只TaiLung骚扰村民，麻烦大侠帮忙解决它，村民会给与您合适的酬劳。"));
	//taskInfo.NextTaskId = taskInfo.TaskId + 10;

	//m_TaskInfos.Add(taskInfo);
}
