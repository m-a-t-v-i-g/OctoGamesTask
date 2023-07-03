// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Character/OGTAnimInstance.h"
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
	
	SetMovement();
	SetTurnPivot();
}

void UOGTAnimInstance::SetMovement()
{
	if (!MovementComponent) return;
	
	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();

	auto DotProductForward = FVector::DotProduct(Character->GetActorForwardVector(), Velocity.GetSafeNormal());
	auto DotProductRight = FVector::DotProduct(Character->GetActorRightVector(), Velocity.GetSafeNormal());
	
	auto CrossProduct = FVector::CrossProduct(Character->GetActorForwardVector(), Velocity.GetSafeNormal());

	Direction = UKismetMathLibrary::DegAcos(DotProductForward) * UKismetMathLibrary::SignOfFloat(CrossProduct.Z);

	auto CurrentAcceleration = MovementComponent->GetCurrentAcceleration();
	if (GroundSpeed > 3.0 && CurrentAcceleration != FVector(0.0))
	{
		ShouldMove = true;
		if (GroundSpeed < 165.0)
		{
			ShouldWalk = true;
		}
		else
		{
			ShouldWalk = false;
		}
	}
	else
	{
		ShouldMove = false;
	}

	if (DotProductForward >= 0.0)
	{
		MovementForward = EMovementForward::MovingF;
	}
	else if (DotProductForward <= -0.075)
	{
		MovementForward = EMovementForward::MovingB;
	}
}

void UOGTAnimInstance::SetTurnPivot()
{
	if (!TryGetPawnOwner()) return;
	
	FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(PreviousRotation, TryGetPawnOwner()->GetActorRotation());
	TurnPivot = UKismetMathLibrary::FInterpTo(TurnPivot, Delta.Yaw * (1.0 / DeltaTime) / 60.0, DeltaTime, TurnSmooth);
	PreviousRotation = TryGetPawnOwner()->GetActorRotation();
}
