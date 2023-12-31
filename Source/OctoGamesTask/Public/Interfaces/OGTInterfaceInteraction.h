// Test task by matvig. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OGTInterfaceInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UOGTInterfaceInteraction : public UInterface
{
	GENERATED_BODY()
};

class OCTOGAMESTASK_API IOGTInterfaceInteraction
{
	GENERATED_BODY()
protected:
	bool Interactable = false;
	
public:
	virtual void OnDetected(bool Switch);
	virtual void OnInteract();

	virtual bool IsInteractable();

};
