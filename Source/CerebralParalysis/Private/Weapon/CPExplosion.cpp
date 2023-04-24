// Cerebral Paralysis. All right reserved. 

#include "Weapon/CPExplosion.h"

#include "Components/Public/CPHealth.h"

ACPExplosion::ACPExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SetRootComponent(CollisionComponent);
}

void ACPExplosion::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandler, this, &ACPExplosion::StopExplosion, 1, false, ExplosionTime);
}

void ACPExplosion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsDamaged)
		return;
	
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors, UCPHealth::StaticClass());

	for (AActor* Actor : Actors)
	{
		UActorComponent* HealthActor = Actor->GetComponentByClass(UCPHealth::StaticClass());

		if (HealthActor == nullptr)
			continue;;

		Cast<UCPHealth>(HealthActor)->TakeDamage(Damage, Team);
		IsDamaged = true;
	}
}

void ACPExplosion::StopExplosion()
{
	IsDamaged = true;
}

