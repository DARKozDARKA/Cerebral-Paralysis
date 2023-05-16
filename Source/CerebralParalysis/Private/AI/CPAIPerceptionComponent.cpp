// Cerebral Paralysis. All right reserved. 


#include "AI/CPAIPerceptionComponent.h"

#include "AI/CPAIController.h"
#include "Components/Public/CPHealth.h"
#include "Perception/AISense_Sight.h"

AActor* UCPAIPerceptionComponent::GetEnemy()
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);

	if (PerceiveActors.Num() == 0)
		return nullptr;

	ACPAIController* const Controller = Cast<ACPAIController>(GetOwner());

	if (Controller == nullptr)
		return nullptr;

	const APawn* Pawn = Controller->GetPawn();

	if (Pawn == nullptr)
		return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestActor = nullptr;

	for (const auto PerceiveActor: PerceiveActors)
	{
		UCPHealth* const HealthComponent = Cast<UCPHealth>(PerceiveActor->GetComponentByClass(UCPHealth::StaticClass()));
		if (!HealthComponent || HealthComponent->IsPlayerDead())
			continue;

		const double CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (CurrentDistance < BestDistance)
		{
			BestDistance = CurrentDistance;
			BestActor = PerceiveActor;
		}
	}

	return BestActor;
}
