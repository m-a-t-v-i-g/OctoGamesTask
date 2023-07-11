// Test task by matvig. All rights reserved.

#include "Game/AI/OGTAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/OGTAIPerceptionComponent.h"
#include "Game/AI/OGTAICharacter.h"

AOGTAIController::AOGTAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UOGTAIPerceptionComponent>("AIPerceptionComp");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void AOGTAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetFocus(GetFocusOnActor());
}

void AOGTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto ControlledCharacter = Cast<AOGTAICharacter>(InPawn);
	if (ControlledCharacter)
	{
		RunBehaviorTree(ControlledCharacter->GetBehaviourTree());
	}
}

AActor* AOGTAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(PlayerActorKeyName));
}
