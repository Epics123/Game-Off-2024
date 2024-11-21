// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuspicionModifier.generated.h"


UENUM(BlueprintType) // Make the enum accessible in Blueprints
enum class ESuspicionModifierType : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	Multiply UMETA(DisplayName = "Multiply"),
	Divide UMETA(DisplayName = "Divide"),
	Add UMETA(DisplayName = "Add"),
	Subtract UMETA(DisplayName = "Subtract")
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct HACKERMAN_API FSuspicionModifier 
{
	GENERATED_USTRUCT_BODY()

	bool operator==(const FSuspicionModifier& other) const
	{
		if (TimeStamp == other.TimeStamp && ModifierType == other.ModifierType)
			return true;
		return false;
	}
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESuspicionModifierType ModifierType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ModifierValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ModifierDuration;

	FDateTime TimeStamp;
};
