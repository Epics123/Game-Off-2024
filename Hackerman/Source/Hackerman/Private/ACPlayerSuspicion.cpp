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
	for (FSuspicionModifier& modifier : Modifiers)
	{
		FDateTime current_time = FDateTime::Now();
		if ( (current_time - modifier.TimeStamp).GetTotalSeconds() > modifier.ModifierDuration)
		{
			Modifiers.RemoveSingle(modifier);
		}

		//FString type;
		switch (modifier.ModifierType)
		{
		case ESuspicionModifierType::Add:
			PendingSuspicion += modifier.ModifierValue;
			//type = "Add";
			break;
		case ESuspicionModifierType::Subtract:
			PendingSuspicion -= modifier.ModifierValue;
			//type = "Subtract";
			break;
		case ESuspicionModifierType::Multiply:
			PendingSuspicion *= modifier.ModifierValue;
			//type = "Multiply";
			break;
		case ESuspicionModifierType::Divide:
			PendingSuspicion -= modifier.ModifierValue;
			//type = "Divide";
			break;
		case ESuspicionModifierType::Invalid:
		default:
			// Remove this because its invalid and cannot be processed
			Modifiers.RemoveSingle(modifier); 
			break;
		}

		if (DebugLogging)
		{
			//FString str = FString::Printf(TEXT("Modifier %s"), TEXT(type));
		}
	}

	// Add suspicion
	SuspicionLevel = FMath::Clamp(SuspicionLevel + PendingSuspicion * DeltaTime * 100, 0.0, 100);
	PendingSuspicion = 0.0; // Reset pending suspicion for next frame

	// Standard decline, maybe we want to handle this differently?
	SuspicionLevel = FMath::Clamp(SuspicionLevel - SuspicionDeclineRate, 0.0, 100);

	if (DebugLogging && GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
		FString TheFloatStr = FString::SanitizeFloat(SuspicionLevel);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *TheFloatStr);
	}
}

