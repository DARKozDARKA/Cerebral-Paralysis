// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/CPBaseWeapon.h"
#include "CPWeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CEREBRALPARALYSIS_API UCPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPWeaponComponent();
	void StartFire();
	void StopFire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ACPBaseWeapon> Weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SocketName = "WeaponSocket";



private:
	void SpawnWeapon();

	UPROPERTY()
	ACPBaseWeapon* CurrentWeapon = nullptr;
};
