// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "OGTInteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OCTOGAMESTASK_API UOGTInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOGTInteractionComponent();

protected:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InteractionWidgetClass;
	
	TObjectPtr<UUserWidget> InteractionWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	TArray<AActor*> FoundCachedActors;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRange = 39.0;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Controller")
	APlayerController* GetPlayerController() const;

	void FindInteraction();
	bool IsInteractable(const AActor* InFoundActor);

	void CallInteract();
	bool CanInteract();
};
