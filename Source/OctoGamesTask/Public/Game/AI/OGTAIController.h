// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "OGTAIController.generated.h"

class UOGTAIPerceptionComponent;

UCLASS()
class OCTOGAMESTASK_API AOGTAIController : public AAIController
{
	GENERATED_BODY()

public:
	AOGTAIController();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	TObjectPtr<UOGTAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName PlayerActorKeyName = "PlayerActor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName GreetingKeyName = "Greeting";
	
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	AActor* GetFocusOnActor() const;
};
