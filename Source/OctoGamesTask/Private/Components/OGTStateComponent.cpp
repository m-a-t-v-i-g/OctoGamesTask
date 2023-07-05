// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/OGTStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UOGTStateComponent::UOGTStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UOGTStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UOGTStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AimTick(DeltaTime);
}

void UOGTStateComponent::SetCharacterState(ECharacterState InCharacterState)
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

void UOGTStateComponent::AimTick(float DeltaTime)
{
	if (GetOwnerController())
	{
		FVector ViewPoint;
		FRotator ViewRotation;
		
		GetOwnerController()->GetPlayerViewPoint(ViewPoint, ViewRotation);

		FHitResult HitResult;

		FVector StartPoint = ViewPoint;
		FVector EndPoint = StartPoint + ViewRotation.Vector() * 10000.0;

		FCollisionQueryParams QueryParams;
		
		QueryParams.AddIgnoredActor(GetOwner());
		QueryParams.bTraceComplex = true;
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, QueryParams);
		if (bHit)
		{
			DrawDebugLine(GetWorld(), GetOwnerCharacter()->GetMesh()->GetSocketLocation(SocketName), HitResult.ImpactPoint, FColor::Red,
						  false, -1.0, 0, 2.5);
			AimOffset = UKismetMathLibrary::FindLookAtRotation(GetOwnerCharacter()->GetMesh()->GetSocketLocation(SocketName), HitResult.ImpactPoint);
		}
	}
}
