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


	void AddSuspicion(float inSuspicion) { mPendingSuspicion += inSuspicion; }
	void RemoveSuspicion(float inSuspicion) { mPendingSuspicion -= inSuspicion; }
	void SetDeclineRate(float inNewDeclineRate) { mSuspicionDeclineRate = inNewDeclineRate; }

	void AddModifier(FSuspicionModifier inModifier) { mModifiers.Add(inModifier); }

	void ToggleDebugLogging() { mDebugLogging = !mDebugLogging; }

private:
	float	mSuspicionLevel = 0.0;
	float	mSuspicionDeclineRate = 0.2;

	float	mPendingSuspicion = 0.0;

	bool	mDebugLogging = false;

	TArray<FSuspicionModifier> mModifiers;

};
