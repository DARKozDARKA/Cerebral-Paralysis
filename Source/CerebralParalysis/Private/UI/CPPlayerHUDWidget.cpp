// Cerebral Paralysis. All right reserved. 


#include "UI/CPPlayerHUDWidget.h"

#include "Components/Public/CPHealth.h"

float UCPPlayerHUDWidget::GetHealthPercentage() const
{
	const auto HealthComponent = GetHealthComponent();
	
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

UCPHealth* UCPPlayerHUDWidget::GetHealthComponent() const
{
	APawn* Owner = GetOwningPlayerPawn();

	if (!Owner)
		return nullptr;
	
	UActorComponent* ComponentByClass = Owner->GetComponentByClass(UCPHealth::StaticClass());
	UActorComponent* ActorComponent = ComponentByClass;
	if (!ActorComponent)
		return nullptr;
	
	const auto Component = ActorComponent;
	const auto HealthComponent = Cast<UCPHealth>(Component);
	return HealthComponent;
}

bool UCPPlayerHUDWidget::IsPlayerAlive() const
{
	return GetHealthComponent() && !GetHealthComponent()->IsPlayerDead();
}

bool UCPPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

