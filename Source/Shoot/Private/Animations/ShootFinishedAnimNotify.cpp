// Shoot Game. All Rights Reserved.


#include "Animations/ShootFinishedAnimNotify.h"

void UShootFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
