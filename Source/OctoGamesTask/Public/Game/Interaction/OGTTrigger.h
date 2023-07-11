// Test task by matvig. All rights reserved.

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
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
