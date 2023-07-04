// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/OGTHUD.h"
#include "Engine/Canvas.h"

void AOGTHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
}

void AOGTHUD::DrawCrosshair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

	const float HalfLineSize = 15.0;
	const float LineThickness = 2.0;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, CrosshairColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, CrosshairColor, LineThickness);
}
