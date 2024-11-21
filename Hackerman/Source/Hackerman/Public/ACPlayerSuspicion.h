// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Data/SuspicionModifier.h"
#include "ACPlayerSuspicion.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKERMAN_API UACPlayerSuspicion : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACPlayerSuspicion();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void AddSuspicion(float inSuspicion) { PendingSuspicion += inSuspicion; }
	void RemoveSuspicion(float inSuspicion) { PendingSuspicion -= inSuspicion; }
	void SetDeclineRate(float inNewDeclineRate) { SuspicionDeclineRate = inNewDeclineRate; }

	void AddModifier(FSuspicionModifier inModifier) { Modifiers.Add(inModifier); }

	void ToggleDebugLogging() { DebugLogging = !DebugLogging; }

private:
	float	SuspicionLevel = 0.0;
	float	SuspicionDeclineRate = 0.2;

	float	PendingSuspicion = 0.0;

	bool	DebugLogging = false;

	TArray<FSuspicionModifier> Modifiers;

};
