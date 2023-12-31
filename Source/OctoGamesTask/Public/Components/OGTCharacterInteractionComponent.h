// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OGTTypes.h"
#include "Components/ActorComponent.h"
#include "OGTCharacterInteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OCTOGAMESTASK_API UOGTCharacterInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOGTCharacterInteractionComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
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

	EInteractionType GetInteractionType();
	
	void CallInteract();
	bool CanInteract();
};
