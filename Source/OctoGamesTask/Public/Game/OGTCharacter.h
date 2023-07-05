// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OGTCharacter.generated.h"

class UOGTStateComponent;
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
	
	UPROPERTY(BlueprintReadOnly)
	float DeltaSeconds = 0.0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UOGTStateComponent> StateComponent;
	
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

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	float FieldOfViewMin = 62.0;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	float FieldOfViewMax = 90.0;
	
	float FieldOfView = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	float CameraSensitivity = 0.35;

	TObjectPtr<AActor> TempTrigger;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Controller")
	APlayerController* GetPlayerController() { return Cast<APlayerController>(GetController()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Components")
	UOGTStateComponent* GetStateComponent() { return StateComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Components")
	UCameraComponent* GetCameraComponent() { return CameraComponent; }
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void AimPressed(const FInputActionValue& Value);
	void AimReleased(const FInputActionValue& Value);

	void UpdateFieldOfView();

	void FindTrigger();
	bool TriggerIsFound(AActor* InFoundActor);
};
