// Test task by matvig. All rights reserved.

#include "Components/OGTAIPerceptionComponent.h"

#include "AIController.h"
#include "Game/OGTCharacter.h"
#include "Perception/AISense_Sight.h"

AActor* UOGTAIPerceptionComponent::GetClosestActor() const
{
	TArray<AActor*> PercievedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
	if (PercievedActors.Num() <= 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;
	
	AActor* Player = nullptr;
	for (auto PercievedActor : PercievedActors)
	{
		if (PercievedActor->GetClass()->IsChildOf(ACharacter::StaticClass()))
		{
			Player = PercievedActor;
			return Player;
		}
	}
	return Player;
}
