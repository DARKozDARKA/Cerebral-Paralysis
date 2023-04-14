// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/Public/CPHealth.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/CPBaseWeapon.h"
#include "CPBaseCharacter.generated.h"

class USpringArmComponent;

UCLASS()
class CEREBRALPARALYSIS_API ACPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPBaseCharacter();
	void SetLookRotation(FVector_NetQuantize Vector);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCPHealth* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextRenderComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<ACPBaseWeapon> Weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Animations");
	UAnimMontage* DeathAnimationMontage;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SpeedAmount = 300;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UPROPERTY(EditAnywhere)
	FVector MoveVector;

	UFUNCTION()
	void SetHealth();
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Roll();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveHorizontal(float Amount);
	void MoveVertical(float Amount);
	void OnDeath();
	void SpawnWeapon();

	bool IsDead;
	FRotator LatestRotation;
};

