// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "CPBaseCharacter.generated.h"

class USpringArmComponent;

UCLASS()
class CEREBRALPARALYSIS_API ACPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPBaseCharacter();
	void SetLookRotation(FVector_NetQuantize Vector);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SpeedAmount = 300;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UPROPERTY()
	FVector MoveVector;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Roll();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveHorizontal(float Amount);
	void MoveVertical(float Amount);
};
