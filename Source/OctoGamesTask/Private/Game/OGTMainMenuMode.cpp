// Test task by matvig. All rights reserved.

#include "Game/OGTMainMenuMode.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

AOGTMainMenuMode::AOGTMainMenuMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> BP_OGTPlayerController(TEXT("/Game/Blueprints/Player/BP_OGTPlayerController"));
	if (BP_OGTPlayerController.Class)
	{
		PlayerControllerClass = BP_OGTPlayerController.Class;
	}

	DefaultPawnClass = nullptr;

	HUDClass = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_OGTMainMenu(TEXT("/Game/UI/Menu/WB_OGTMainMenu"));
	if (WB_OGTMainMenu.Class)
	{
		MainMenuWidgetClass = WB_OGTMainMenu.Class;
	}
}

void AOGTMainMenuMode::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	auto CreateMainMenuWidget = CreateWidget<UUserWidget>(PlayerController, MainMenuWidgetClass);
	if (CreateMainMenuWidget)
	{
		MainMenuWidget = CreateMainMenuWidget;
		if (MainMenuWidget && !MainMenuWidget->IsInViewport())
		{
			PlayerController->SetShowMouseCursor(true);
			MainMenuWidget->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, MainMenuWidget);
		}
	}
}
