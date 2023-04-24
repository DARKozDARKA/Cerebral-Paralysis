// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Public/CPHealth.h"
#include "CPPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CEREBRALPARALYSIS_API UCPPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	void OnHealthChanged();
	virtual bool Initialize() override;
	
private:
	UCPHealth* GetHealthComponent() const;


protected:
	UPROPERTY()
	UCPHealth* HealthComponent;
};
