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

	if (IsFiring && CanFire)
		MakeShot();
}

void ACPBaseWeapon::StartFire()
{
	IsFiring = true;
}

void ACPBaseWeapon::StopFire()
{
	IsFiring = false;
}



void ACPBaseWeapon::MakeShot()
{
	if (!GetWorld())
		return;

	FVector TraceStart;
	FVector TraceEnd;
	CalculateTrace(TraceStart, TraceEnd);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);

	FHitResult HitResult;
	Raycast(TraceStart, TraceEnd, HitResult);

	if (HitResult.bBlockingHit)
		Damage(HitResult);

	CanFire = false;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ACPBaseWeapon::ReloadFire, FireReloadTime, false, FireReloadTime);
}



void ACPBaseWeapon::CalculateTrace(FVector& TraceStart, FVector& TraceEnd)
{
	const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform(MuzzleSocketName);
	TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
}

void ACPBaseWeapon::Raycast(FVector TraceStart, FVector TraceEnd, FHitResult& HitResult)
{
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ACPBaseWeapon::Damage(FHitResult HitResult)
{
	UCPHealth* Health= Cast<UCPHealth>(HitResult.GetActor()->GetComponentByClass(UCPHealth::StaticClass()));

	if (!Health)
		return;

	Health->TakeDamage(DamageAmount);
	
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
}

void ACPBaseWeapon::ReloadFire()
{
	CanFire = true;
}