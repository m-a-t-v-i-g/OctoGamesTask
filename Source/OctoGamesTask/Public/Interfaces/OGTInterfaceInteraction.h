// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OGTInterfaceInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UOGTInterfaceInteraction : public UInterface
{
	GENERATED_BODY()
};

class OCTOGAMESTASK_API IOGTInterfaceInteraction
{
	GENERATED_BODY()

public:
	virtual void OnDetected(bool Switch);
};
