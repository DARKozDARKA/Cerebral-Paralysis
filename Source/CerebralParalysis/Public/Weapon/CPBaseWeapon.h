// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPBaseWeapon.generated.h"

UCLASS()
class CEREBRALPARALYSIS_API ACPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPBaseWeapon();
	virtual void Fire();
	void CalculateTrace(FVector& TraceStart, FVector& TraceEnd);
	void Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult);
	void Damage(FHitResult HitResult);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleFlashSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

private:
	void MakeShot();

};
