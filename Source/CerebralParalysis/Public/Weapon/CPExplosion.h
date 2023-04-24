// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/CPWeaponFXComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CPExplosion.generated.h"

UCLASS()
class CEREBRALPARALYSIS_API ACPExplosion : public AActor
{
	GENERATED_BODY()
public:
	ACPExplosion();

	UFUNCTION()
	void SetDamage(float NewDamage, int MyTeam)
	{
		Damage = NewDamage;
		Team = MyTeam;
	}

protected:
	UPROPERTY(VisibleAnywhere, Category = "Explosion")
	USphereComponent* CollisionComponent;

	FTimerHandle TimerHandler;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void StopExplosion();

private:
	float Damage;
	bool IsDamaged = false;
	int Team;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float ExplosionTime = 0.1f;
};
