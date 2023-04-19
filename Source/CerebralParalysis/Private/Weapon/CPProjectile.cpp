// Cerebral Paralysis. All right reserved. 


#include "Weapon/CPProjectile.h"

#include "Components/Public/CPHealth.h"

ACPProjectile::ACPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), false);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponenent");
}

void ACPProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileMovementComponent);
	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &ACPProjectile::OnProjectHit);
}

void ACPProjectile::OnProjectHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())
		return;
	
	TakeDamage(OtherActor);
	
	Destroy();
}

void ACPProjectile::TakeDamage(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	
	UActorComponent* HealthActor = OtherActor->GetComponentByClass(UCPHealth::StaticClass());
	if (HealthActor == nullptr)
		return;
	Cast<UCPHealth>(HealthActor)->TakeDamage(DamageAmount);

}
