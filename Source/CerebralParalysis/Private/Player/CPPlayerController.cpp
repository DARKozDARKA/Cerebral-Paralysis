// Cerebral Paralysis. All right reserved. 


#include "Player/CPPlayerController.h"

#include "CPGameModeBase.h"
#include "GameFramework/Character.h"
#include "Player/CPBaseCharacter.h"

void ACPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ACPPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ACharacter* Character2 = GetCharacter();
	
	if (Character2 == nullptr)
		return;
	
	FHitResult FHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, FHit);

	ACPBaseCharacter* Character3;
	Character3 = Cast<ACPBaseCharacter>(Character2);

	Character3->SetLookRotation(FHit.Location);

	
	
	
}
