// Cerebral Paralysis. All right reserved. 


#include "Components/CPWeaponComponent.h"

#include "GameFramework/Character.h"


UCPWeaponComponent::UCPWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts

void UCPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}


void UCPWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
		return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;
	
	CurrentWeapon = GetWorld()->SpawnActor<ACPBaseWeapon>(Weapon);

	if (!CurrentWeapon)
		return;
	
	const FAttachmentTransformRules* AttachmentRules = new FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), *AttachmentRules, SocketName);
}

void UCPWeaponComponent::Fire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->Fire();
}