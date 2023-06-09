// Cerebral Paralysis. All right reserved. 


#include "Components/Public/CPHealth.h"

UCPHealth::UCPHealth()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UCPHealth::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);
	
	Health = MaxHealth;
	UE_LOG(LogTemp, Error, TEXT("Begin"));
	
}

void UCPHealth::TakeDamage(float Amount, int EnemyTeam)
{
	if (IsDead)
		return;

	if (EnemyTeam == Team)
		return;
	
	Health -= Amount;

	if (Health <= 0)
		Die();

	HealthChangedDelegate.Broadcast();
}

void UCPHealth::Die()
{
	Health = 0;
	OnDeath.Broadcast();
	IsDead = true;
}



