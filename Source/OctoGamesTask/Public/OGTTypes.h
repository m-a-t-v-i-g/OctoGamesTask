// Test task by matvig. All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OGTTypes.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Aiming UMETA(DisplayName = "Aiming"),
	NotAiming UMETA(DisplayName = "Not aiming")
};

UENUM(BlueprintType)
enum class EMovementDir : uint8
{
	MovingF UMETA(DisplayName = "Forward"),
	MovingB UMETA(DisplayName = "Backward")
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),

	Human UMETA(DisplayName = "Human"),
	Item UMETA(DisplayName = "Item"),
	Trigger UMETA(DisplayName = "Trigger")
};

UCLASS()
class OCTOGAMESTASK_API UOGTTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
