// Cerebral Paralysis. All right reserved. 


#include "Weapon/CPBaseWeapon.h"

ACPBaseWeapon::ACPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SetRootComponent(WeaponMeshComponent);
}

void ACPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
