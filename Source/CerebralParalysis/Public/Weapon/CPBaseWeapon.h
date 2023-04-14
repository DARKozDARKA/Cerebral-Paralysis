// Cerebral Paralysis. All right reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPBaseWeapon.generated.h"

UCLASS()
class CEREBRALPARALYSIS_API ACPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPBaseWeapon();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMeshComponent;

public:	

};
