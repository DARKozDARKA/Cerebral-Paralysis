// Cerebral Paralysis. All right reserved. 


#include "AI/Tasks/CPNextLocationTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UCPNextLocationTask::UCPNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UCPNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Controller || !Blackboard)
		return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	
	if (!Pawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(Pawn);

	if (!NavSys)
		return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	FVector Location = Pawn->GetActorLocation();

	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (!CenterActor)
			return EBTNodeResult::Failed;
		
		Location = CenterActor->GetActorLocation();
	}

	const bool IsFound = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);

	if (!IsFound)
		return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	
	return EBTNodeResult::Succeeded;
}
