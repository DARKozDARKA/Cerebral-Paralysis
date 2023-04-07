// Cerebral Paralysis. All right reserved. 


#include "Dev/CPDevDamageActor.h"

#include "Components/Public/CPHealth.h"

// Sets default values
ACPDevDamageActor::ACPDevDamageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");

	SetRootComponent(GetRootComponent());
}

// Called when the game starts or when spawned
void ACPDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> Actors;
	TSubclassOf<AActor> subClass = UCPHealth::StaticClass();
	GetOverlappingActors(Actors, subClass);

	TArray<UPrimitiveComponent*> Components;
	GetOverlappingComponents(Components);

	for (AActor* Actor : Actors)
	{
		UActorComponent* HealthActor = Actor->GetComponentByClass(UCPHealth::StaticClass());

		if (HealthActor == nullptr)
			return;

		Cast<UCPHealth>(HealthActor)->TakeDamage(0.1f);
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
}
