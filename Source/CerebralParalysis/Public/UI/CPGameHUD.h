// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPGameHUD.generated.h"

UCLASS()
class CEREBRALPARALYSIS_API ACPGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;
	
};
