// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API ACPPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};
