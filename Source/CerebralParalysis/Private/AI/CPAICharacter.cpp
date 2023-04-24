// Cerebral Paralysis. All right reserved. 


#include "AI/CPAICharacter.h"

#include "AI/CPAIController.h"

ACPAICharacter::ACPAICharacter(const FObjectInitializer& ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACPAIController::StaticClass();
}
