// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/OGTAnimInstance.h"
#include "Components/OGTStateComponent.h"
#include "Game/OGTCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOGTAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (GetOwningActor())
	{
		Character = Cast<ACharacter>(GetOwningActor());
		if (!Character) return;
		
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UOGTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	DeltaTime = DeltaSeconds;

	if (!Character) return;

	SetCharacterState();
	
	SetAimOffset();
	
	SetMovement();

	SetFallingType();
	
	SetTurn();
	SetLean();

	PreviousRotation = TryGetPawnOwner()->GetActorRotation();
}

void UOGTAnimInstance::SetCharacterState()
{
	auto GetStateComponent = Character->FindComponentByClass<UOGTStateComponent>();
	if (!GetStateComponent) return;

	CharacterState = GetStateComponent->GetCharacterState();
}

void UOGTAnimInstance::SetAimOffset()
{
	auto GetStateComponent = Character->FindComponentByClass<UOGTStateComponent>();
	if (!GetStateComponent) return;

	FRotator GetAimOffset = GetStateComponent->GetAimOffset();
	
	float TargetX = GetAimOffset.Pitch;
	float TargetY = GetAimOffset.Yaw;

	AimOffset = UKismetMathLibrary::Vector2DInterpTo(AimOffset, FVector2D(TargetX, TargetY), DeltaTime, AimSmooth);
}

void UOGTAnimInstance::SetMovement()
{
	if (!MovementComponent) return;
	
	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();

	auto DotProduct = FVector::DotProduct(Character->GetActorForwardVector(), Velocity.GetSafeNormal());
	auto CrossProduct = FVector::CrossProduct(Character->GetActorForwardVector(), Velocity.GetSafeNormal());

	IsFalling = MovementComponent->IsFalling();

	Direction = UKismetMathLibrary::DegAcos(DotProduct) * UKismetMathLibrary::SignOfFloat(CrossProduct.Z);
	
	ShouldMove = IsMoving();
	ShouldWalk = IsWalking();

	SetMovementDirection(DotProduct);
}

void UOGTAnimInstance::SetMovementDirection(float InDotProduct)
{
	if (!IsMoving()) return;
	
	if (InDotProduct >= 0.0)
	{
		MovementDir = EMovementDir::MovingF;
	}
	else if (InDotProduct <= -0.065)
	{
		MovementDir = EMovementDir::MovingB;
	}
}

void UOGTAnimInstance::SetFallingType()
{
	if (!Character || !MovementComponent) return;

	auto OGTCharacter = Cast<AOGTCharacter>(Character);
	if (!OGTCharacter) return;
	
	SoftLanding = OGTCharacter->SoftLanding;
	MediumLanding = OGTCharacter->MediumLanding;
	HardLanding = OGTCharacter->HardLanding;
}

void UOGTAnimInstance::SetTurn()
{
	if (!TryGetPawnOwner()) return;
	
	FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(PreviousRotation, TryGetPawnOwner()->GetActorRotation());
	TurnPivot = UKismetMathLibrary::FInterpTo(TurnPivot, Delta.Yaw * (1.0 / DeltaTime) / 60.0, DeltaTime, TurnSmooth);
}

void UOGTAnimInstance::SetLean()
{
	if (!TryGetPawnOwner()) return;
	
	FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(TryGetPawnOwner()->GetActorRotation(), PreviousRotation);
	YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, Delta.Yaw / DeltaTime / 10.0, DeltaTime, LeanSmooth);
}

bool UOGTAnimInstance::IsMoving()
{
	return GroundSpeed > 3.0 && MovementComponent->GetCurrentAcceleration() != FVector(0.0);
}

bool UOGTAnimInstance::IsWalking()
{
	return IsMoving() && GroundSpeed < 165.0;
}

