// Test task by matvig. All rights reserved.

#include "Game/Interaction/OGTTrigger.h"
#include "Components/BoxComponent.h"

AOGTTrigger::AOGTTrigger()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComponent->SetupAttachment(SceneComponent);

	InteractionZone = CreateDefaultSubobject<UBoxComponent>("Interaction Zone");
	InteractionZone->SetupAttachment(SceneComponent);

	PrimaryActorTick.bCanEverTick = true;

}

void AOGTTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionZone->OnComponentBeginOverlap.AddDynamic(this, &AOGTTrigger::OnInteractionZone);
	InteractionZone->OnComponentEndOverlap.AddDynamic(this, &AOGTTrigger::OutInteractionZone);
}

void AOGTTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOGTTrigger::OnDetected(bool Switch)
{
	if (!StaticMeshComponent) return;

	StaticMeshComponent->SetRenderCustomDepth(Switch);
}

bool AOGTTrigger::IsInteractable()
{
	return Interactable;
}

void AOGTTrigger::OnInteract()
{
	CallInteract();
}

void AOGTTrigger::OnInteractionZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interactable = true;
}

void AOGTTrigger::OutInteractionZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Interactable = false;
}
