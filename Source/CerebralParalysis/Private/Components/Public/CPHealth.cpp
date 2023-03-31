// Cerebral Paralysis. All right reserved. 


#include "Components/Public/CPHealth.h"

UCPHealth::UCPHealth()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UCPHealth::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	UE_LOG(LogTemp, Error, TEXT("Begin"));
	
}

void UCPHealth::TakeDamage(float Amount)
{
	Health -= Amount;

	if (Health <= 0)
		Die();
}

void UCPHealth::Die()
{
	UE_LOG(LogTemp, Display, TEXT("Bro just died"));
	HealthChangedDelegate.Execute();
}



