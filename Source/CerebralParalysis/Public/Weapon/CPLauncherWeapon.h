// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "CPProjectile.h"
#include "Weapon/CPBaseWeapon.h"
#include "CPLauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API ACPLauncherWeapon : public ACPBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ACPProjectile> ProjectileClass;

	virtual void MakeShot() override;

private:
	void CalculateTrace(FVector& TraceStart, FVector& TraceEnd);
	void Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult);
	void Damage(FHitResult HitResult);
};
