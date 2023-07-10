// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OGTInteractionWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UTextBlock;

UCLASS()
class OCTOGAMESTASK_API UOGTInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InteractionCanvas;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> InteractionBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionText;
};
