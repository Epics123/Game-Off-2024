// Copyright Epic Games, Inc. All Rights Reserved.

#include "HackermanGameMode.h"
#include "HackermanCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHackermanGameMode::AHackermanGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
