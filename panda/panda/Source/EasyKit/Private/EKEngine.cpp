
#include "EasyKit.h"

#include "EKGameFrame.h"
#include "EKSceneManager.h"
#include "EKResourceManager.h"
#include "EKNetWorkManager.h"
#include "EKEngine.h"

#include "EKGameInstance.h"
#include "Kismet/GameplayStatics.h"


UEKEngine::UEKEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bUseNetwork(true)
{

}

void UEKEngine::Init(class IEngineLoop* InEngineLoop)
{
	EKGame = FEKGameFrame::Instance();

	UE_LOG(LogScript, Warning, TEXT("AEasyKit Init !"));

	// 检查下网络是否可以开启
	//if (bUseNetwork == true)
	//	EKGame->NetWorkManager()->SetNetworkUseState(bUseNetwork);


	Super::Init(InEngineLoop);

	EKGameInstance = Cast<UEKGameInstance>(GameInstance);
	check(EKGameInstance);

	EKGame->SceneManager()->SetWorld(GWorld);

	// Init objects that required GWorld.
	EKGameInstance->PostInit();
}

bool UEKEngine::LoadMap(FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error)
{
	if (GWorld)
	{
		EKGame->SceneManager()->SetWorld(GWorld);
	}
	Super::LoadMap(WorldContext, URL, Pending, Error);
	return true;
}

void UEKEngine::Tick(float DeltaSeconds, bool bIdleMode)
{
	Super::Tick(DeltaSeconds, bIdleMode);

	if (EKGame != NULL)
		EKGame->Tick(DeltaSeconds, bIdleMode);
}

