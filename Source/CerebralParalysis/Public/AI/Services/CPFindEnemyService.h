// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CPFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API UCPFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UCPFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
