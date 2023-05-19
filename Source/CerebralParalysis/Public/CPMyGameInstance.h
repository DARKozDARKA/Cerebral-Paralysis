// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPMyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API UCPMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void OnStart() override;
	
};
