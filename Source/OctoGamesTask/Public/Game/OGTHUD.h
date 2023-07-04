// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OGTHUD.generated.h"

UCLASS()
class OCTOGAMESTASK_API AOGTHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	FLinearColor CrosshairColor;
	
public:
	void DrawCrosshair();
};
