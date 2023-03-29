// Cerebral Paralysis. All right reserved. 


#include "CPGameModeBase.h"

#include "Player/CPBaseCharacter.h"
#include "Player/CPPlayerController.h"

ACPGameModeBase::ACPGameModeBase()
{
	DefaultPawnClass = ACPBaseCharacter::StaticClass();
	PlayerControllerClass = ACPPlayerController::StaticClass();
}
