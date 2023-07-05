// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OGTInterfaceInteraction.h"
#include "OGTTrigger.generated.h"

class UBoxComponent;

UCLASS()
class OCTOGAMESTASK_API AOGTTrigger : public AActor, public IOGTInterfaceInteraction
{
	GENERATED_BODY()
	
public:	
	AOGTTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UBoxComponent> InteractionZone;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnDetected(bool Switch) override;

	virtual bool IsInteractable() override;
	
	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void CallInteract();
	
	UFUNCTION()
	void OnInteractionZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OutInteractionZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
