// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/OGTGameModeBase.h"
#include "Game/OGTHUD.h"

AOGTGameModeBase::AOGTGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> BP_OGTCharacter(TEXT("/Game/Blueprints/Player/BP_OGTCharacter"));
	if (BP_OGTCharacter.Class != nullptr)
	{
		DefaultPawnClass = BP_OGTCharacter.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APlayerController> BP_OGTPlayerController(TEXT("/Game/Blueprints/Player/BP_OGTPlayerController"));
	if (BP_OGTPlayerController.Class != nullptr)
	{
		PlayerControllerClass = BP_OGTPlayerController.Class;
	}

	HUDClass = AOGTHUD::StaticClass();
}
