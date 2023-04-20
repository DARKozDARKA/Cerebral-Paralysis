// Cerebral Paralysis. All right reserved. 


#include "Player/CPBaseCharacter.h"

#include "Components/Public/CPHealth.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACPBaseCharacter::ACPBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	HealthComponent = CreateDefaultSubobject<UCPHealth>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UCPWeaponComponent>("WeaponComponent");

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());
}


void ACPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	HealthComponent->HealthChangedDelegate.BindUObject(this, &ACPBaseCharacter::SetHealth);
	HealthComponent->OnDeath.AddUObject(this, &ACPBaseCharacter::OnDeath);
	SetHealth();
}

void ACPBaseCharacter::SetHealth()
{
	float Health = HealthComponent->GetHealth();
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called every frame

void ACPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(MoveVector, SpeedAmount);
}

float ACPBaseCharacter::GetMovementDirection() const
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const double AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void ACPBaseCharacter::SetLookRotation(FVector_NetQuantize Vector)
{
	if (IsDead)
	{
		RootComponent->SetWorldRotation(LatestRotation);
		return;
	}

	Vector.Z = GetActorLocation().Z;
	FVector FinalVector = Vector - GetActorLocation();
	FRotator NewRotation = FinalVector.Rotation();
	LatestRotation = NewRotation;
	RootComponent->SetWorldRotation(NewRotation);
}

// Called to bind functionality to input

void ACPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(WeaponComponent);
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Horizontal", this, &ACPBaseCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &ACPBaseCharacter::MoveVertical);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ACPBaseCharacter::Roll);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UCPWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UCPWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UCPWeaponComponent::NextWeapon);
}

void ACPBaseCharacter::Roll()
{
	Jump();
}

void ACPBaseCharacter::MoveHorizontal(float Amount)
{
	MoveVector.Y = Amount;
}

void ACPBaseCharacter::MoveVertical(float Amount)
{
	MoveVector.X = Amount;
}

void ACPBaseCharacter::OnDeath()
{
	IsDead = true;
	PlayAnimMontage(DeathAnimationMontage);

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}


