// Cerebral Paralysis. All right reserved. 


#include "AI/CPAIController.h"
#include "AI/CPAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ACPAIController::ACPAIController()
{
	CPPerceptionComponent = CreateDefaultSubobject<UCPAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*CPPerceptionComponent);
	
}

void ACPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<ACPAICharacter>(InPawn);

	if (!AICharacter)
		return;

	RunBehaviorTree(AICharacter->BehaviorTreeAsset);
}

void ACPAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AActor* AimActor = GetFocusOnActor();

	SetFocus(AimActor);
}

AActor* ACPAIController::GetFocusOnActor()
{
	if (!GetBlackboardComponent())
		return nullptr;
	
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
