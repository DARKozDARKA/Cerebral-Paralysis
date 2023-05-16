// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "CPAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API UCPAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetEnemy();
};
