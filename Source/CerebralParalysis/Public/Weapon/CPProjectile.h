// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "CPExplosion.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CPProjectile.generated.h"

UCLASS()
class CEREBRALPARALYSIS_API ACPProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPProjectile();
	void SetShootDirection(const FVector& Vector){ShotDirection = Vector;}
	
	void SetTeam(int MyTeam){Team = MyTeam;}

protected:
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Explosion")
	UCPWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> TrailActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile" )
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile" )
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<ACPExplosion> ExplosionClass;

	UFUNCTION()
	virtual void BeginPlay() override;
	
private:	
	FVector ShotDirection;

	UPROPERTY()
	AActor* CurrentTrailActor;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float InLifespan = 5.0f;

	int Team;
	
	UFUNCTION()
	void OnProjectHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void TakeDamage(AActor* OtherActor);
};
