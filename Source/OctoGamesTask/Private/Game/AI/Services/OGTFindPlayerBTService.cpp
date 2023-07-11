// Test task by matvig. All rights reserved.

#include "Game/AI/Services/OGTFindPlayerBTService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/OGTAIPerceptionComponent.h"
#include "GameFramework/Character.h"

UOGTFindPlayerBTService::UOGTFindPlayerBTService()
{
	NodeName = "Find player";
}

void UOGTFindPlayerBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		if (!Controller) return;

		const auto PerceptionComponent = Cast<UOGTAIPerceptionComponent>(Controller->GetComponentByClass(UOGTAIPerceptionComponent::StaticClass()));
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, PerceptionComponent->GetClosestActor());
			if (PerceptionComponent->GetClosestActor() != nullptr)
			{
				if (PerceptionComponent->GetClosestActor()->GetClass()->IsChildOf(ACharacter::StaticClass()))
				{
					Blackboard->SetValueAsBool(GreetingKey.SelectedKeyName, true);
					return;
				}
			}
			Blackboard->SetValueAsBool(GreetingKey.SelectedKeyName, false);
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
