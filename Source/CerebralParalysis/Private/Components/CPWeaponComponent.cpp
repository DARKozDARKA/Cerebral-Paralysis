// Cerebral Paralysis. All right reserved. 

#include "Components/CPWeaponComponent.h"

#include "Animations/CPEquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"


UCPWeaponComponent::UCPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UCPWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void UCPWeaponComponent::SpawnWeapons()
{
	if (!GetWorld())
		return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ACPBaseWeapon>(WeaponClass);

		if (!Weapon)
			continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UCPWeaponComponent::EquipWeapon(int32 NewWeaponIndex)
{
	EquipAnimInProgress = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	StopFire();
	if (CurrentWeapon)
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);

	CurrentWeapon = Weapons[CurrentWeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), SocketName);
	PlayAnimMontage(EquipAnimMontage);
}


void UCPWeaponComponent::NextWeapon()
{
	if (CanEquip() == false)
		return;
	
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UCPWeaponComponent::AttachWeaponToSocket(ACPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& Name)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, Name);
}


void UCPWeaponComponent::StartFire()
{
	if (CanFire() == false)
		return;

	CurrentWeapon->StartFire();
}

void UCPWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFire();
}

void UCPWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	Character->PlayAnimMontage(Animation);
}

void UCPWeaponComponent::InitAnimations()
{
	if (!EquipAnimMontage)
		return;
	
	TArray<FAnimNotifyEvent> NotifyEvents = EquipAnimMontage->Notifies;

	for (FAnimNotifyEvent NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<UCPEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (!EquipFinishedNotify)
			continue;

		EquipFinishedNotify->OnNotified.AddUObject(this, &UCPWeaponComponent::OnEquipFinished);
	}
}

void UCPWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (Character->GetMesh() != MeshComponent)
		return;

	EquipAnimInProgress = false;
}

bool UCPWeaponComponent::CanFire() const
{
	return !EquipAnimInProgress;
}

bool UCPWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}
