// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SideCPPGameMode.h"
#include "SideCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideCPPGameMode::ASideCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
