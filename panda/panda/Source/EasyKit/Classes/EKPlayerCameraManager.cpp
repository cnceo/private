
#include "EasyKit.h"
#include "EKPlayerCameraManager.h"

AEKPlayerCameraManager::AEKPlayerCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NormalFOV = 90.0f;
	TargetingFOV = 60.0f;
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
	bAlwaysApplyModifiers = true;

	CameraMode = CAMERA_MODE::CAMERA_FREE;

	MaxArmLength = 1000;
	MinArmLength = 600;
	ArmSpeed = 300;
	DevAngle = 30;
}

void AEKPlayerCameraManager::UpdateCamera(float DeltaTime)
{

	//if (MyPawn && MyPawn->IsFirstPerson())
	//{
	//	const float TargetFOV = MyPawn->IsTargeting() ? TargetingFOV : NormalFOV;
	//	DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 20.0f);
	//}

	Super::UpdateCamera(DeltaTime);

	if (CameraMode == CAMERA_MODE::CAMERA_FREE)
	{
		FreeMode(DeltaTime);
	}
	else if (CameraMode == CAMERA_MODE::CAMERA_SCENE)
	{
		SceneMode(DeltaTime);
	} 
	else if (CameraMode == CAMERA_MODE::CAMERA_SKILL)
	{
		SkillMode(DeltaTime);
	}
	else
	{

	}

	//UE_LOG(LogScript, Warning, TEXT("CameraRotation: %f %f %f"), GetCameraRotation().Vector().X, GetCameraRotation().Vector().Y, GetCameraRotation().Vector().Z);
}

void AEKPlayerCameraManager::NoneMode(float DeltaTime)
{
	AEKCharacter* MyPawn = PCOwner ? Cast<AEKCharacter>(PCOwner->GetPawn()) : NULL;

	if (MyPawn == nullptr)
		return;

	if (MyPawn->CameraBoom)
	{
		//////////////////////////////////////////////////////////////////////////
		// Possess Camera Rotation
		MyPawn->CameraBoom->SetWorldLocation(MyPawn->GetActorLocation());
	}
}

void AEKPlayerCameraManager::FreeMode(float DeltaTime)
{
	AEKCharacter* MyPawn = PCOwner ? Cast<AEKCharacter>(PCOwner->GetPawn()) : NULL;

	if (MyPawn == nullptr)
		return;

	if (MyPawn->CameraBoom)
	{
		//////////////////////////////////////////////////////////////////////////
		// Possess Camera Rotation
		MyPawn->CameraBoom->SetWorldLocation(MyPawn->GetActorLocation());

		FRotator rotate = MyPawn->GetActorRotation();
		FRotator targetRotate = MyPawn->CameraBoom->RelativeRotation;

		if (targetRotate.Yaw != rotate.Yaw)
		{
			float DevRotat = targetRotate.Yaw - rotate.Yaw;

			// 防止抖动
			if (-1.00000f < DevRotat && DevRotat< 1.00000f)
				return;

			if (DevRotat <0)
			{
				DevRotat = 360 + DevRotat;
			}

			if (DevRotat > 180)
			{
				if ((DeltaTime * DevAngle) >= DevRotat)
				{
					targetRotate.Yaw = rotate.Yaw;
				}
				else
				{
					targetRotate.Yaw += DeltaTime * DevAngle;
				}
			}
			else
			{
				if ((DeltaTime * DevAngle) >= DevRotat)
				{
					targetRotate.Yaw = rotate.Yaw;
				}
				else
				{
					targetRotate.Yaw -= DeltaTime * DevAngle;
				}
			}

			MyPawn->CameraBoom->SetWorldRotation(targetRotate);
		}

		//////////////////////////////////////////////////////////////////////////
		// Possess Boom length
		FVector CurrenVector = MyPawn->GetVelocity();
		if (CurrenVector == FVector::ZeroVector)
		{
			if (MyPawn->CameraBoom->TargetArmLength > MinArmLength)
			{
				// 摄像机恢复过快 乘0.8 作为速度衰减
				if (MyPawn->CameraBoom->TargetArmLength - DeltaTime * ArmSpeed*0.8f < MinArmLength)
				{
					MyPawn->CameraBoom->TargetArmLength = MinArmLength;
				}
				else
				{
					MyPawn->CameraBoom->TargetArmLength -= DeltaTime * ArmSpeed*0.8f;
				}

			}
		}
		else
		{
			if (MyPawn->CameraBoom->TargetArmLength < MaxArmLength)
			{
				if (MyPawn->CameraBoom->TargetArmLength + DeltaTime * ArmSpeed > MaxArmLength)
				{
					MyPawn->CameraBoom->TargetArmLength = MaxArmLength;
				}
				else
				{
					MyPawn->CameraBoom->TargetArmLength += DeltaTime * ArmSpeed;
				}

			}
		}
	}
	
}

void AEKPlayerCameraManager::SceneMode(float DeltaTime)
{

}

void AEKPlayerCameraManager::SkillMode(float DeltaTime)
{

}

void AEKPlayerCameraManager::SetCameraMode(CAMERA_MODE inType)
{
	CameraMode = inType;
}

void AEKPlayerCameraManager::SetDevAngle(float inAngle)
{
	DevAngle = inAngle;
}

void AEKPlayerCameraManager::SetMaxArmLength(float inLength)
{
	MaxArmLength = inLength;
}

void AEKPlayerCameraManager::SetMinArmLength(float inLength)
{
	MinArmLength = inLength;
}

void AEKPlayerCameraManager::AddSceneCamera(class ACameraActor* inCamera)
{
	if (SceneCameraList.Find(inCamera) == INDEX_NONE)
	{
		SceneCameraList.Add(inCamera);
	}
}

void AEKPlayerCameraManager::RemoveSceneCamera(class ACameraActor* inCamera)
{
	if (SceneCameraList.Find(inCamera) != INDEX_NONE)
	{
		SceneCameraList.Remove(inCamera);
	}
}
