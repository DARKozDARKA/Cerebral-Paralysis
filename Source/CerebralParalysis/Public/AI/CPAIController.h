// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPAIPerceptionComponent.h"
#include "CPAIController.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API ACPAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACPAIController();

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCPAIPerceptionComponent* CPPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor();
};
