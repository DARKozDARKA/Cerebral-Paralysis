// Cerebral Paralysis. All right reserved. 


#include "AI/Services/CPFireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CPWeaponComponent.h"

UCPFireService::UCPFireService()
{
	NodeName = "Fire";
}

void UCPFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	bool HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (!Controller)
		return;

	UCPWeaponComponent* WeaponComponent = Cast<UCPWeaponComponent>(
		Controller->GetPawn()->GetComponentByClass(UCPWeaponComponent::StaticClass()));

	if (!WeaponComponent)
		return;

	HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
	if (HasAim == false)
		UE_LOG(LogTemp, Warning, TEXT("HAS NO AIM"));

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
