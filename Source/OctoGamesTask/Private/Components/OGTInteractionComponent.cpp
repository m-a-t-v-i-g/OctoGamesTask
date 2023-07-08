// Test task by matvig. All rights reserved.

#include "Components/OGTInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OGTInterfaceInteraction.h"

UOGTInteractionComponent::UOGTInteractionComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WB_InteractionWidget(TEXT("/Game/UI/Player/WB_InteractionWidget"));
	InteractionWidgetClass = WB_InteractionWidget.Class;
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UOGTInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	auto CreateInteractionWidget = CreateWidget<UUserWidget>(GetPlayerController(), InteractionWidgetClass);
	if (CreateInteractionWidget)
	{
		InteractionWidget = CreateInteractionWidget;
	}

}

void UOGTInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FindInteraction();
}

APlayerController* UOGTInteractionComponent::GetPlayerController() const
{
	const auto CharacterOwner = Cast<ACharacter>(GetOwner())->GetController();
	if (!CharacterOwner) return nullptr;
	
	return Cast<APlayerController>(CharacterOwner);
}

void UOGTInteractionComponent::FindInteraction()
{
	TArray<AActor*> FoundActors;
	
	FVector ViewPoint;
	FRotator ViewRotation;

	if (!GetPlayerController()) return;
	GetPlayerController()->GetPlayerViewPoint(ViewPoint, ViewRotation);

	FHitResult HitResult;

	FVector StartPoint = ViewPoint;
	FVector EndPoint = StartPoint + ViewRotation.Vector() * (InteractionRange * 10.0);

	FCollisionQueryParams QueryParams;
		
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.bTraceComplex = true;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, QueryParams);
	if (bHit)
	{
		AActor* FoundActor = nullptr;

		FoundActor = HitResult.GetActor();
		FoundActors.AddUnique(FoundActor);
		
		for (auto EachActor : FoundActors)
		{
			if (IsInteractable(EachActor))
			{
				FoundCachedActors.AddUnique(EachActor);
				const auto FoundInteraction = Cast<IOGTInterfaceInteraction>(EachActor);
				if (FoundInteraction)
				{
					FoundInteraction->OnDetected(true);
					if (InteractionWidget && !InteractionWidget->IsInViewport())
					{
						InteractionWidget->AddToViewport();
					}
				}
			}
		}
	}
	for (int i = 0; i < FoundCachedActors.Num(); i++)
	{
		if (!FoundActors.Contains(FoundCachedActors[i]))
		{
			auto FoundInteraction = Cast<IOGTInterfaceInteraction>(FoundCachedActors[i]);
			if (FoundInteraction)
			{
				FoundInteraction->OnDetected(false);
				FoundCachedActors.RemoveAt(i);
				if (InteractionWidget && InteractionWidget->IsInViewport())
				{
					InteractionWidget->RemoveFromParent();
				}
			}
		}
	}
}


bool UOGTInteractionComponent::IsInteractable(const AActor* InFoundActor)
{
	if (InFoundActor->Implements<UOGTInterfaceInteraction>())
	{
		return true;
	}
	return false;
}

void UOGTInteractionComponent::CallInteract()
{
	if (CanInteract())
	{
		for (const auto TempCachedActor : FoundCachedActors)
		{
			const auto FoundInteraction = Cast<IOGTInterfaceInteraction>(TempCachedActor);
			if (FoundInteraction)
			{
				FoundInteraction->OnInteract();
			}
		}
	}
}

bool UOGTInteractionComponent::CanInteract()
{
	for (const auto TempCachedActor : FoundCachedActors)
	{
		if (TempCachedActor)
		{
			const auto FoundInteraction = Cast<IOGTInterfaceInteraction>(TempCachedActor);
			if (!FoundInteraction) return false;

			return IsValid(TempCachedActor) && IsInteractable(TempCachedActor) || FoundInteraction->IsInteractable();
		}
	}
	return false;
}
