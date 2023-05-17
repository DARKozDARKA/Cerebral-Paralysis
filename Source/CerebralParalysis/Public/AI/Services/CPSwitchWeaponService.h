// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CPSwitchWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API UCPSwitchWeaponService : public UBTService
{
	GENERATED_BODY()

	UCPSwitchWeaponService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Probability;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FTimerHandle TimerHandle;

	void OnSwitch();
	
};
