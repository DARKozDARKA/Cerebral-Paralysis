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
	
	virtual void StartFire();
	virtual void StopFire();
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleFlashSocket";
	
	UPROPERTY(EditDefaultsOnly)
	float FireReloadTime;

	bool IsFiring;
	bool CanFire = true;
	
	virtual void MakeShot();
	
	FTransform GetMuzzleTransform() const;

private:
	virtual void TryFire();
	virtual void Tick(float DeltaSeconds) override;
};
