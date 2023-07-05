// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Interaction/OGTTrigger.h"

AOGTTrigger::AOGTTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AOGTTrigger::BeginPlay()
{
	Super::BeginPlay();
	
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

