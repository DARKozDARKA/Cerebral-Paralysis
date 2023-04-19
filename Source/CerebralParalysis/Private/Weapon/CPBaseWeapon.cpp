// Cerebral Paralysis. All right reserved. 


#include "Weapon/CPBaseWeapon.h"

#include "Components/Public/CPHealth.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ACPBaseWeapon::ACPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SetRootComponent(WeaponMeshComponent);
}

void ACPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMeshComponent);
}

void ACPBaseWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TryFire();
}

void ACPBaseWeapon::StartFire()
{
	IsFiring = true;
}

void ACPBaseWeapon::StopFire()
{
	IsFiring = false;
}

void ACPBaseWeapon::MakeShot(){}

FTransform ACPBaseWeapon::GetMuzzleTransform() const
{
	return WeaponMeshComponent->GetSocketTransform(MuzzleSocketName);
}

void ACPBaseWeapon::TryFire(){}
