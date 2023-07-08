// Test task by matvig. All rights reserved.

#include "Game/Interaction/OGTItem.h"

AOGTItem::AOGTItem()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComponent->SetupAttachment(SceneComponent);
	
	PrimaryActorTick.bCanEverTick = true;

}

void AOGTItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOGTItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOGTItem::OnDetected(bool Switch)
{
	if (!StaticMeshComponent) return;

	StaticMeshComponent->SetRenderCustomDepth(Switch);
	Interactable = true;
}

bool AOGTItem::IsInteractable()
{
	return Interactable;
}

void AOGTItem::OnInteract()
{
	CallInteract();
}

