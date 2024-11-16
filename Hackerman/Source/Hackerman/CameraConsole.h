// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraConsole.generated.h"

UENUM(BlueprintType)
enum class ECameraCycleDirection : uint8
{
	LEFT	UMETA(DisplayName = "Left"),
	RIGHT	UMETA(DisplayName = "Right")
};

UCLASS()
class HACKERMAN_API ACameraConsole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraConsole();

	UFUNCTION(BlueprintCallable)
	void DisableAllSceneCaptures();

	// Sets the active camera and tells it to start capturing the scene
	UFUNCTION(BlueprintCallable)
	void ActivateCamera(int32 CameraIndex);
	
	UFUNCTION(BlueprintCallable)
	void DeactivateCamera(int32 CameraIndex);

	// Start capturing the scene with the current active camera
	UFUNCTION(BlueprintCallable)
	void ActivateActiveCamera();

	// Stop capturing the scene with the current active camera
	UFUNCTION(BlueprintCallable)
	void DeactivateActiveCamera();

	UFUNCTION(BlueprintCallable)
	void CycleCamera(ECameraCycleDirection Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SceneCapture)
	TArray<TObjectPtr<class ASceneCapture2D>> Cameras;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SceneCapture)
	TObjectPtr<class UTextureRenderTarget2D> RenderTarget;

private:
	class ASceneCapture2D* ActiveCamera = nullptr;
};
