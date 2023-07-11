// Test task by matvig. All rights reserved.

#include "Game/AI/OGTAICharacter.h"

AOGTAICharacter::AOGTAICharacter()
{
	Interactable = true;
	
	PrimaryActorTick.bCanEverTick = true;
}

void AOGTAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOGTAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOGTAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AOGTAICharacter::IsInteractable()
{
	return Interactable;
}

void AOGTAICharacter::OnInteract()
{
	CallInteract();
}

void AOGTAICharacter::CallGreeting()
{
	if (!GreetingMontage) return;

	PlayAnimMontage(GreetingMontage);
}

