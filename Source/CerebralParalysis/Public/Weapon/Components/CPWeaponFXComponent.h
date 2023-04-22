// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/ActorComponent.h"
#include "CPWeaponFXComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CEREBRALPARALYSIS_API UCPWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPWeaponFXComponent();
	void PlayImpactFX(const FHitResult& Hit);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Effect;

		
};
