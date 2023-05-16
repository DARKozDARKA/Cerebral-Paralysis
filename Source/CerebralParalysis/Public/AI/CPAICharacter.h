// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/CPBaseCharacter.h"
#include "CPAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API ACPAICharacter : public ACPBaseCharacter
{
	GENERATED_BODY()
public:
	ACPAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
};
