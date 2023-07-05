// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OGTTypes.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "OGTStateComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OCTOGAMESTASK_API UOGTStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOGTStateComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	ECharacterState CharacterState = ECharacterState::NotAiming;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aim")
	FName SocketName = "head";

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aim")
	FRotator AimOffset;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Controller")
	APlayerController* GetOwnerController()
	{
		auto Owner = Cast<ACharacter>(GetOwner());
		return IsValid(Owner) ? Cast<APlayerController>(Owner->GetController()) : nullptr;
	}
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Controller")
	ACharacter* GetOwnerCharacter()
	{
		auto Owner = Cast<ACharacter>(GetOwner());
		return IsValid(Owner) ? Owner : nullptr;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	ECharacterState GetCharacterState() { return CharacterState; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aim")
	FRotator GetAimOffset() { return AimOffset; }

	void SetCharacterState(ECharacterState InCharacterState);
	
	void AimTick(float DeltaTime);
};
