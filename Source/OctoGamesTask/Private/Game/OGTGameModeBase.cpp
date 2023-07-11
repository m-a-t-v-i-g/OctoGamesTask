// Test task by matvig. All rights reserved.

#include "Game/OGTGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/OGTHUD.h"

AOGTGameModeBase::AOGTGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APlayerController> BP_OGTPlayerController(TEXT("/Game/Blueprints/Player/BP_OGTPlayerController"));
	if (BP_OGTPlayerController.Class)
	{
		PlayerControllerClass = BP_OGTPlayerController.Class;
	}
	
	static ConstructorHelpers::FClassFinder<AHUD> BP_OGTHUD(TEXT("/Game/Blueprints/Player/BP_OGTHUD"));
	if (BP_OGTHUD.Class)
	{
		HUDClass = BP_OGTHUD.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APawn> BP_OGTCharacter(TEXT("/Game/Blueprints/Player/BP_OGTCharacter"));
	if (BP_OGTCharacter.Class)
	{
		DefaultPawnClass = BP_OGTCharacter.Class;
	}
}

void AOGTGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}
