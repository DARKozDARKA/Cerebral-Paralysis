// Cerebral Paralysis. All right reserved. 


#include "Weapon/CPLauncherWeapon.h"
#include "Kismet/GameplayStatics.h"

void ACPLauncherWeapon::StartFire()
{
	Super::StartFire();

	MakeShot();
}

void ACPLauncherWeapon::MakeShot()
{
	Super::MakeShot();

	FVector Direction;
	GetFireDirection(Direction);

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleTransform().GetLocation());
	ACPProjectile* Projectile = GetWorld()->SpawnActorDeferred<ACPProjectile>(ProjectileClass, SpawnTransform);

	if (!Projectile)
		return;
	
	Projectile->SetShootDirection(Direction);
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);
}

void ACPLauncherWeapon::CalculateTrace(FVector& TraceStart, FVector& TraceEnd)
{
	FTransform SocketTransform = GetMuzzleTransform();
	TraceStart = SocketTransform.GetLocation();
	
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();

	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
}

void ACPLauncherWeapon::Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult)
{
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ACPLauncherWeapon::GetFireDirection(FVector& Direction)
{
	FVector TraceStart;
	FVector TraceEnd;
	CalculateTrace(TraceStart, TraceEnd);
	
	FHitResult HitResult;
	Raycast(TraceStart, TraceEnd, HitResult);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	Direction = (EndPoint - GetMuzzleTransform().GetLocation()).GetSafeNormal();
}
