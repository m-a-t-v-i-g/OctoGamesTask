// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "OGTPlayerGreetingBTTask.generated.h"

UCLASS()
class OCTOGAMESTASK_API UOGTPlayerGreetingBTTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UOGTPlayerGreetingBTTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector GreetingKey;
	
};
