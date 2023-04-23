// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/CPWeaponFXComponent.h"
#include "Weapon/CPBaseWeapon.h"
#include "CPRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API ACPRifleWeapon : public ACPBaseWeapon
{
	ACPRifleWeapon();
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UCPWeaponFXComponent* WeaponFXComponent;
	
private:
	virtual void TryFire() override;
	virtual void MakeShot() override;

	void CalculateTrace(FVector& TraceStart, FVector& TraceEnd);
	void Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult);
	void Damage(FHitResult HitResult);
	void ReloadFire();
	void SpawnTraceFX(FVector& TraceStart, FVector& TraceEnd);

	UPROPERTY(EditDefaultsOnly)
	double BulletSpread;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly)
	FString TraceTargetName = "TraceTarget";

	FTimerHandle FireTimerHandle;
};
