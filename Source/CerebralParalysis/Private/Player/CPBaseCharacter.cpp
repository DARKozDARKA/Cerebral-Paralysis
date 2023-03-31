// Cerebral Paralysis. All right reserved. 


#include "Player/CPBaseCharacter.h"

#include "Components/Public/CPHealth.h"

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

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());
}


void ACPBaseCharacter::FunctionIg()
{
}

void ACPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	HealthComponent->HealthChangedDelegate.BindUObject(this, &ACPBaseCharacter::FunctionIg);
	
}

// Called every frame

void ACPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(MoveVector, SpeedAmount);

	float Health = HealthComponent->GetHealth();
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
	//UE_LOG(LogTemp, Display, TEXT("%.0f"), Health);

	HealthComponent->TakeDamage(0.1f);
}

float ACPBaseCharacter::GetMovementDirection() const
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const double AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return FMath::RadiansToDegrees(AngleBetween)  * FMath::Sign(CrossProduct.Z);
}

void ACPBaseCharacter::SetLookRotation(FVector_NetQuantize Vector)
{
	Vector.Z = GetActorLocation().Z;
	FVector FinalVector = Vector - GetActorLocation();
	FRotator newrot = FinalVector.Rotation();
	RootComponent->SetWorldRotation(newrot);
}

// Called to bind functionality to input

void ACPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Horizontal", this, &ACPBaseCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &ACPBaseCharacter::MoveVertical);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ACPBaseCharacter::Roll);

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