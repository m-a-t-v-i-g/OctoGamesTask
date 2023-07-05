// Fill out your copyright notice in the Description page of Project Settings.

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

UCLASS()
class OCTOGAMESTASK_API UOGTTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
