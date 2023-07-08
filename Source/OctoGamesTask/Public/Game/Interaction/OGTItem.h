// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OGTInterfaceInteraction.h"
#include "OGTItem.generated.h"

UCLASS()
class AOGTItem : public AActor, public IOGTInterfaceInteraction
{
	GENERATED_BODY()
	
public:	
	AOGTItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnDetected(bool Switch) override;

	virtual bool IsInteractable() override;
	
	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void CallInteract();
	
};
