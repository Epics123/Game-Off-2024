// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraConsole.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
ACameraConsole::ACameraConsole()
{
	
}

void ACameraConsole::DisableAllSceneCaptures()
{
	for(const ASceneCapture2D* Camera : Cameras)
	{
		Camera->GetCaptureComponent2D()->bCaptureEveryFrame = false;
	}
}

void ACameraConsole::ActivateCamera(int32 CameraIndex)
{
	check(CameraIndex < Cameras.Num());

	if(IsValid(RenderTarget))
	{
		ActiveCamera = Cameras[CameraIndex];
		ActivateActiveCamera();
	}
}

void ACameraConsole::DeactivateCamera(int32 CameraIndex)
{
	check(CameraIndex < Cameras.Num());
	Cameras[CameraIndex]->GetCaptureComponent2D()->bCaptureEveryFrame = false;
}

void ACameraConsole::ActivateActiveCamera()
{
	if(ActiveCamera && IsValid(RenderTarget))
	{
		ActiveCamera->GetCaptureComponent2D()->bCaptureEveryFrame = true;
		ActiveCamera->GetCaptureComponent2D()->TextureTarget = RenderTarget;
	}
}

void ACameraConsole::DeactivateActiveCamera()
{
	if (ActiveCamera)
	{
		ActiveCamera->GetCaptureComponent2D()->bCaptureEveryFrame = false;
		ActiveCamera->GetCaptureComponent2D()->TextureTarget = nullptr;
	}
}

void ACameraConsole::CycleCamera(ECameraCycleDirection Direction)
{
	if(!ActiveCamera) // if no camera is active, just use the first camera that we have
	{
		ActivateCamera(0);
		return;
	}

	const int32 CurrentCameraIndex = Cameras.IndexOfByKey(ActiveCamera);
	int32 NewCameraIndex = CurrentCameraIndex;

	switch (Direction)
	{
	case ECameraCycleDirection::LEFT:
		NewCameraIndex--;
		break;
	case ECameraCycleDirection::RIGHT:
		NewCameraIndex++;
		break;
	}

	if(NewCameraIndex < 0)
	{
		NewCameraIndex = Cameras.Num() - 1;
	}
	else if(NewCameraIndex >= Cameras.Num())
	{
		NewCameraIndex = 0;
	}

	DeactivateActiveCamera();
	ActivateCamera(NewCameraIndex);
}

// Called when the game starts or when spawned
void ACameraConsole::BeginPlay()
{
	Super::BeginPlay();
	DisableAllSceneCaptures();
}

// Called every frame
void ACameraConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

