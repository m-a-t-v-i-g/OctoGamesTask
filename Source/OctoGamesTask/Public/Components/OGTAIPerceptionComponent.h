// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "OGTAIPerceptionComponent.generated.h"

UCLASS()
class OCTOGAMESTASK_API UOGTAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetClosestActor() const;
};
