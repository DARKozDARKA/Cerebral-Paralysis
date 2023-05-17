// Cerebral Paralysis. All right reserved. 


#include "AI/Services/CPSwitchWeaponService.h"
#include "AIController.h"
#include "Components/CPWeaponComponent.h"

UCPSwitchWeaponService::UCPSwitchWeaponService()
{
	NodeName = "Switch Weapon";
}

void UCPSwitchWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	
	if (!AIOwner)
		return;

	UCPWeaponComponent* WeaponComponent = Cast<UCPWeaponComponent>(
		AIOwner->GetPawn()->GetComponentByClass(UCPWeaponComponent::StaticClass()));

	if (!WeaponComponent)
		return;

	if (FMath::FRand() > Probability)
		return;
	
	WeaponComponent->NextWeapon();
}

