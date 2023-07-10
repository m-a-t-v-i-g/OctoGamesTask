// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OGTMainMenuMode.generated.h"

UCLASS()
class OCTOGAMESTASK_API AOGTMainMenuMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOGTMainMenuMode();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	
	TObjectPtr<UUserWidget> MainMenuWidget;
	
};
