// Test task by matvig. All rights reserved.

#include "Components/OGTCharacterInteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Interfaces/OGTInterfaceInteraction.h"

UOGTCharacterInteractionComponent::UOGTCharacterInteractionComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WB_InteractionWidget(TEXT("/Game/UI/Player/WB_InteractionWidget"));
	InteractionWidgetClass = WB_InteractionWidget.Class;
	
	PrimaryComponentTick.bCanEverTick = true;
}

void UOGTCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	auto CreateInteractionWidget = CreateWidget<UUserWidget>(GetPlayerController(), InteractionWidgetClass);
	if (CreateInteractionWidget)
	{
		InteractionWidget = CreateInteractionWidget;
	}
}

void UOGTCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindInteraction();
}

APlayerController* UOGTCharacterInteractionComponent::GetPlayerController() const
{
	const auto CharacterOwner = Cast<ACharacter>(GetOwner())->GetController();
	if (!CharacterOwner) return nullptr;
	
	return Cast<APlayerController>(CharacterOwner);
}

void UOGTCharacterInteractionComponent::FindInteraction()
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
		AActor* FoundActor = HitResult.GetActor();
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
					if (!InteractionWidget->IsInViewport())
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
			}
			if (InteractionWidget->IsInViewport())
			{
				InteractionWidget->RemoveFromParent();
			}
		}
	}
}

bool UOGTCharacterInteractionComponent::IsInteractable(const AActor* InFoundActor)
{
	if (InFoundActor->Implements<UOGTInterfaceInteraction>())
	{
		return true;
	}
	return false;
}

void UOGTCharacterInteractionComponent::CallInteract()
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

bool UOGTCharacterInteractionComponent::CanInteract()
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

