// Cerebral Paralysis. All right reserved. 

#include "Weapon/CPRifleWeapon.h"
#include "Components/Public/CPHealth.h"

ACPRifleWeapon::ACPRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UCPWeaponFXComponent>("WeaponFXComponent");
}


void ACPRifleWeapon::TryFire()
{
	if (IsFiring && CanFire)
		MakeShot();
}

void ACPRifleWeapon::MakeShot()
{
	if (!GetWorld())
		return;

	FVector TraceStart;
	FVector TraceEnd;
	CalculateTrace(TraceStart, TraceEnd);
	
	FHitResult HitResult;
	Raycast(TraceStart, TraceEnd, HitResult);

	if (HitResult.bBlockingHit)
		Damage(HitResult);

	WeaponFXComponent->PlayImpactFX(HitResult);
	
	CanFire = false;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ACPRifleWeapon::ReloadFire, FireReloadTime, false, FireReloadTime);
}



void ACPRifleWeapon::CalculateTrace(FVector& TraceStart, FVector& TraceEnd)
{
	FTransform SocketTransform = GetMuzzleTransform();
	TraceStart = SocketTransform.GetLocation();

	double HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(SocketTransform.GetRotation().GetForwardVector(), HalfRad);

	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
}

void ACPRifleWeapon::Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult)
{
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ACPRifleWeapon::Damage(FHitResult HitResult)
{
	UCPHealth* Health= Cast<UCPHealth>(HitResult.GetActor()->GetComponentByClass(UCPHealth::StaticClass()));

	if (!Health)
		return;

	Health->TakeDamage(DamageAmount);
}

void ACPRifleWeapon::ReloadFire()
{
	CanFire = true;
}