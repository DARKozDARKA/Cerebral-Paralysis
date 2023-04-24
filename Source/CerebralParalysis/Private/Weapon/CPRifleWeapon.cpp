// Cerebral Paralysis. All right reserved. 

#include "Weapon/CPRifleWeapon.h"
#include "Components/Public/CPHealth.h"
#include "NiagaraComponent.h"

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
	FVector TraceFXEnd = TraceEnd;

	FHitResult HitResult;
	Raycast(TraceStart, TraceEnd, HitResult);

	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		Damage(HitResult);
	}
	
	WeaponFXComponent->PlayImpactFX(HitResult);
	CanFire = false;
	
	SpawnTraceFX(TraceStart, TraceFXEnd);
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ACPRifleWeapon::ReloadFire, FireReloadTime, false,
	                                FireReloadTime);
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
	UCPHealth* Health = Cast<UCPHealth>(HitResult.GetActor()->GetComponentByClass(UCPHealth::StaticClass()));

	if (!Health)
		return;

	int MyTeam;
	if (UActorComponent* MyHealth = GetOwner()->GetComponentByClass(UCPHealth::StaticClass()))
	{
		if (const UCPHealth* HealthComponent = Cast<UCPHealth>(MyHealth))
		{
			UE_LOG(LogTemp, Display, TEXT("GOT HEALTH RIFLE"));
			MyTeam = HealthComponent->Team; 
		}
			
	}
	
	Health->TakeDamage(DamageAmount, MyTeam);
}

void ACPRifleWeapon::ReloadFire()
{
	CanFire = true;
}

void ACPRifleWeapon::SpawnTraceFX(FVector& TraceStart, FVector& TraceEnd)
{
	UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), TraceFX, TraceStart);
	
	if (!TraceFXComponent)
		return;
	
	TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
}
