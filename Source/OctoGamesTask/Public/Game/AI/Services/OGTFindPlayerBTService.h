// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "OGTFindPlayerBTService.generated.h"

UCLASS()
class OCTOGAMESTASK_API UOGTFindPlayerBTService : public UBTService
{
	GENERATED_BODY()
public:
	UOGTFindPlayerBTService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector GreetingKey;
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
