// Test task by matvig. All rights reserved.

#include "Components/OGTCharacterStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UOGTCharacterStateComponent::UOGTCharacterStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UOGTCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UOGTCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AimTick(DeltaTime);
}

void UOGTCharacterStateComponent::SetCharacterState(ECharacterState InCharacterState)
{
	CharacterState = InCharacterState;
	switch (CharacterState)
	{
	case ECharacterState::Aiming:
		GetOwnerCharacter()->GetCharacterMovement()->MaxWalkSpeed = 150.0;
		break;
	case ECharacterState::NotAiming:
		GetOwnerCharacter()->GetCharacterMovement()->MaxWalkSpeed = 340.0;
		break;
	default:
		break;
	}
}

void UOGTCharacterStateComponent::AimTick(float DeltaTime)
{
	if (GetOwnerController())
	{
		FVector ViewPoint;
		FRotator ViewRotation;

		GetOwnerController()->GetPlayerViewPoint(ViewPoint, ViewRotation);
	
		auto CrossProduct = FVector::CrossProduct(GetOwnerCharacter()->GetActorRotation().Vector(), ViewRotation.Vector());

		AimOffset = FRotator(UKismetMathLibrary::RadiansToDegrees(CrossProduct.Z) * UE_HALF_PI,
		                     UKismetMathLibrary::RadiansToDegrees(ViewRotation.Vector().Z * UE_HALF_PI), 0.0);
	}
}
