// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPHealth.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CEREBRALPARALYSIS_API UCPHealth : public UActorComponent
{
	DECLARE_MULTICAST_DELEGATE(FOnHealthChanged);
	DECLARE_MULTICAST_DELEGATE(FOnDeath);

	GENERATED_BODY()
public:
	FOnHealthChanged HealthChangedDelegate;

	FOnDeath OnDeath;

	UCPHealth();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0"))
	float MaxHealth;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsPlayerDead() const { return Health <= 0; }

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return Health / MaxHealth; }


protected:
	float Health;
	virtual void BeginPlay() override;

private:
	void Die();
	bool IsDead = false;
};
