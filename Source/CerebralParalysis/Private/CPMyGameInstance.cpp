// Cerebral Paralysis. All right reserved. 


#include "CPMyGameInstance.h"

void UCPMyGameInstance::OnStart()
{
	Super::OnStart();

	SET_WARN_COLOR(COLOR_CYAN)
	UE_LOG(LogTemp, Error, TEXT("STARTED"));
}
