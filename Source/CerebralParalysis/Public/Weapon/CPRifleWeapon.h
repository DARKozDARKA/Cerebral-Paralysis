// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CPBaseWeapon.h"
#include "CPRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API ACPRifleWeapon : public ACPBaseWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500;

	
private:
	virtual void TryFire() override;
	virtual void MakeShot() override;

	void CalculateTrace(FVector& TraceStart, FVector& TraceEnd);
	void Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult);
	void Damage(FHitResult HitResult);
	void ReloadFire();

	UPROPERTY(EditDefaultsOnly)
	double BulletSpread;

	FTimerHandle FireTimerHandle;
};
