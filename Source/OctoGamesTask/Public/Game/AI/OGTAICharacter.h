// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/OGTInterfaceInteraction.h"
#include "OGTAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class OCTOGAMESTASK_API AOGTAICharacter : public ACharacter, public IOGTInterfaceInteraction
{
	GENERATED_BODY()

public:
	AOGTAICharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviourTreeAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> GreetingMontage;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsInteractable() override;

	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void CallInteract();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI")
	UBehaviorTree* GetBehaviourTree() { return BehaviourTreeAsset; }
	
	void CallGreeting();
};
