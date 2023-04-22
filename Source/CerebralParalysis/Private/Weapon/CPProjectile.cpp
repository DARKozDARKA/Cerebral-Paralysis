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

	WeaponFXComponent = CreateDefaultSubobject<UCPWeaponFXComponent>("WeaponFXComponent");
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
	WeaponFXComponent->PlayImpactFX(Hit);

	
	Destroy();
}

void ACPProjectile::TakeDamage(AActor* OtherActor)
{
	ACPExplosion* Explosion = GetWorld()->SpawnActorDeferred<ACPExplosion>(ExplosionClass, GetActorTransform());

	if (!Explosion)
		return;
	
	Explosion->SetDamage(DamageAmount);
	Explosion->SetOwner(GetOwner());
	Explosion->FinishSpawning(GetActorTransform());

}
