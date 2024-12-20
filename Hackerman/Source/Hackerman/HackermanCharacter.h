// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Public/ACPlayerSuspicion.h"
#include "HackermanCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UACPlayerSuspicion;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHackermanCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	AHackermanCharacter();

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	// SUSPICION DEBUG
	UFUNCTION(exec)
	void ToggleSuspicionDebugLogs() { SuspicionComponent->ToggleDebugLogging(); }
	UFUNCTION(exec)
	void AddSuspicion(float inSuspicion) { SuspicionComponent->AddSuspicion(inSuspicion); }
	UFUNCTION(exec)
	void SetSuspicionDeclineRate(float inNewDeclineRate) { SuspicionComponent->SetDeclineRate(inNewDeclineRate); }

	UFUNCTION(exec)
	void AddSuspicionModifier(ESuspicionModifierType inType, float inValue, float inDuration);

protected:
	virtual void BeginPlay();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	// Data asset containing the input actions for this character
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputData> InputData;

	// Data asset containing the input actions for this character
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UACPlayerSuspicion> SuspicionComponent;
};

