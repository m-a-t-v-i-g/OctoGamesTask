// Test task by matvig. All rights reserved.

#include "Game/AI/Tasks/OGTPlayerGreetingBTTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/AI/OGTAICharacter.h"

UOGTPlayerGreetingBTTask::UOGTPlayerGreetingBTTask()
{
	NodeName = "Player greeting";
}

EBTNodeResult::Type UOGTPlayerGreetingBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Blackboard || !Controller) return EBTNodeResult::Failed;
	
	const auto Pawn = Cast<AOGTAICharacter>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	if (Blackboard->GetValueAsBool(GreetingKey.SelectedKeyName))
	{
		Pawn->CallGreeting();
		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Succeeded;
}

