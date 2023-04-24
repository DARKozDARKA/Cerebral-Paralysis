// Cerebral Paralysis. All right reserved. 


#include "UI/CPPlayerHUDWidget.h"

#include "Components/Public/CPHealth.h"


bool UCPPlayerHUDWidget::Initialize()
{
	HealthComponent = GetHealthComponent();

	if (HealthComponent)
		HealthComponent->HealthChangedDelegate.AddUObject(this, &UCPPlayerHUDWidget::OnHealthChanged);
	
	return Super::Initialize();
}


float UCPPlayerHUDWidget::GetHealthPercentage() const
{
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
	
	
	return Cast<UCPHealth>(ActorComponent);
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

void UCPPlayerHUDWidget::OnHealthChanged()
{
	UE_LOG(LogTemp, Display, TEXT("AAAAAAAAAAAAAA"));
	OnTakeDamage();
}
