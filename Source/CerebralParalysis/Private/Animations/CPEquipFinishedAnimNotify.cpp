// Cerebral Paralysis. All right reserved. 


#include "Animations/CPEquipFinishedAnimNotify.h"

void UCPEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
