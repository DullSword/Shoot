// Shoot Game. All Rights Reserved.

#include "UI/ShootWidgetBase.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UShootWidgetBase::Enter()
{
	if (!IsAnimationPlaying(EnterAnimation))
	{
		PlayAnimation(EnterAnimation);
	}

	UGameplayStatics::PlaySound2D(this, OpenSound);
}

void UShootWidgetBase::Out()
{
	if (OutAnimation)
	{
		FWidgetAnimationDynamicEvent OutAnimationDynamicEvent;
		OutAnimationDynamicEvent.BindDynamic(this, &UShootWidgetBase::OnOutAnimationFinished);
		BindToAnimationFinished(OutAnimation, OutAnimationDynamicEvent);
	}

	if (!IsAnimationPlaying(OutAnimation))
	{
		PlayAnimation(OutAnimation);
	}
}

void UShootWidgetBase::OnOutAnimationFinished()
{
}
