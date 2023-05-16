// Cerebral Paralysis. All right reserved. 


#include "AI/Services/CPFindEnemyService.h"

#include "AIController.h"
#include "AI/CPAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCPFindEnemyService::UCPFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UCPFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard)
		return;

	const AAIController* Controller = OwnerComp.GetAIOwner();
	UCPAIPerceptionComponent* const PerceptionComponent = Cast<UCPAIPerceptionComponent>(
		Controller->GetComponentByClass(UCPAIPerceptionComponent::StaticClass()));

	if (!PerceptionComponent)
		return;

	Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetEnemy());
}
