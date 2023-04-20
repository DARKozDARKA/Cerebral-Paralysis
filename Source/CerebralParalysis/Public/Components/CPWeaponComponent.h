// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/CPBaseWeapon.h"
#include "CPWeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CEREBRALPARALYSIS_API UCPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCPWeaponComponent();
	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ACPBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* EquipAnimMontage;

private:
	void AttachWeaponToSocket(ACPBaseWeapon* Weapon, USceneComponent* Mesh, const FName& Name);
	void SpawnWeapons();
	void EquipWeapon(int CurrentWeaponIndex);
	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	UPROPERTY()
	ACPBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ACPBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	bool EquipAnimInProgress = false;
	bool CanFire() const;
	bool CanEquip() const;
};
