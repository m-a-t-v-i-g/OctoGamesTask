// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OGTInterfaceInteraction.h"
#include "OGTTrigger.generated.h"

UCLASS()
class OCTOGAMESTASK_API AOGTTrigger : public AActor, public IOGTInterfaceInteraction
{
	GENERATED_BODY()
	
public:	
	AOGTTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnDetected(bool Switch) override;
	
};
