// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OGTCharacter.generated.h"

class UOGTCharacterStateComponent;
class UOGTCharacterInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class OCTOGAMESTASK_API AOGTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOGTCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	
	UPROPERTY(BlueprintReadOnly)
	float DeltaSeconds = 0.0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UOGTCharacterStateComponent> CharacterState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UOGTCharacterInteractionComponent> CharacterInteraction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	TObjectPtr<UUserWidget> PauseMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DanceMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> InteractionItemMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> InteractionTriggerMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> SoftLandMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> HardLandMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	float FieldOfViewMin = 60.0;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	float FieldOfViewMax = 90.0;
	
	float FieldOfView = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	float CameraSensitivity = 0.35;
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool SoftLanding = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool MediumLanding = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool HardLanding = false;
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Controller")
	APlayerController* GetPlayerController() const { return Cast<APlayerController>(Controller); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Components")
	UOGTCharacterStateComponent* GetStateComponent() const { return CharacterState; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Components")
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void AimPressed(const FInputActionValue& Value);
	void AimReleased(const FInputActionValue& Value);

	void SetFieldOfView() const;

	void CallInteract();

	void CallPause();
	
	void SetFallingType();

};
