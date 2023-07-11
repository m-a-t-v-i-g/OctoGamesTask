// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OGTGameModeBase.generated.h"

UCLASS()
class OCTOGAMESTASK_API AOGTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOGTGameModeBase();

protected:
	virtual void BeginPlay() override;
};
