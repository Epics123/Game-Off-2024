// Fill out your copyright notice in the Description page of Project Settings.


#include "ACPlayerSuspicion.h"

// Sets default values for this component's properties
UACPlayerSuspicion::UACPlayerSuspicion()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACPlayerSuspicion::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UACPlayerSuspicion::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// This logic may need to be changed but for now we are going to handle modiers in the order they are added. 
	for (FSuspicionModifier& modifier : mModifiers)
	{
		FDateTime current_time = FDateTime::Now();
		if ( (current_time - modifier.mTimeStamp).GetTotalSeconds() > modifier.mModifierDuration)
		{
			mModifiers.RemoveSingle(modifier);
		}

		//FString type;
		switch (modifier.mModifierType)
		{
		case ESuspicionModifierType::Add:
			mPendingSuspicion += modifier.mModifierValue;
			//type = "Add";
			break;
		case ESuspicionModifierType::Subtract:
			mPendingSuspicion -= modifier.mModifierValue;
			//type = "Subtract";
			break;
		case ESuspicionModifierType::Multiply:
			mPendingSuspicion *= modifier.mModifierValue;
			//type = "Multiply";
			break;
		case ESuspicionModifierType::Divide:
			mPendingSuspicion -= modifier.mModifierValue;
			//type = "Divide";
			break;
		case ESuspicionModifierType::Invalid:
		default:
			// Remove this because its invalid and cannot be processed
			mModifiers.RemoveSingle(modifier); 
			break;
		}

		if (mDebugLogging)
		{
			//FString str = FString::Printf(TEXT("Modifier %s"), TEXT(type));
		}
	}

	// Add suspicion
	mSuspicionLevel = FMath::Clamp(mSuspicionLevel + mPendingSuspicion * DeltaTime * 100, 0.0, 100);
	mPendingSuspicion = 0.0; // Reset pending suspicion for next frame

	// Standard decline, maybe we want to handle this differently?
	mSuspicionLevel = FMath::Clamp(mSuspicionLevel - mSuspicionDeclineRate, 0.0, 100);

	if (mDebugLogging && GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
		FString TheFloatStr = FString::SanitizeFloat(mSuspicionLevel);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *TheFloatStr);
	}
}

