// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OGTTypes.h"
#include "Animation/AnimInstance.h"
#include "OGTAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class OCTOGAMESTASK_API UOGTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime = 0.0;
	
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	TObjectPtr<ACharacter> Character;
	
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ECharacterState CharacterState = ECharacterState::NotAiming;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector Velocity = FVector(0.0);
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float Direction = 0.0;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float GroundSpeed = 0.0;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	EMovementDir MovementDir;
	
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool ShouldMove = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool ShouldWalk = false;

	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool IsFalling = false;

	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool SoftLanding = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool MediumLanding = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	bool HardLanding = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Turn")
	float TurnPivot = 0.0;

	UPROPERTY(BlueprintReadWrite, Category = "Turn")
	float TurnSmooth = 0.0;

	UPROPERTY(BlueprintReadWrite, Category = "Turn")
	float LeanSmooth = 10.0;
	
	UPROPERTY(BlueprintReadWrite, Category = "Rotation")
	FRotator PreviousRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Rotation")
	float YawDelta = 0.0;

	UPROPERTY(BlueprintReadWrite, Category = "Aim")
	FVector2D AimOffset = FVector2D(0.0);

	UPROPERTY(BlueprintReadWrite, Category = "Aim")
	float AimSmooth = 0.0;
	
public:
	void SetCharacterState();
	
	void SetAimOffset();
	
	void SetMovement();
	void SetMovementDirection(float InDotProduct);

	void SetFallingType();
	
	void SetTurn();
	void SetLean();
	
	bool IsMoving();
	bool IsWalking();

};
