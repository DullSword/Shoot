// Shoot Game. All Rights Reserved.

#include "UI/ShootSpectatorWidget.h"
#include "Components/RespawnComponent.h"

bool UShootSpectatorWidget::GetRespawnCountDownTime(int32& CountDownTime) const
{
	const auto Controller = GetOwningPlayer();
	if (!Controller)
	{
		return false;
	}
	const auto RespawnComponent = Cast<URespawnComponent>(Controller->GetComponentByClass(URespawnComponent::StaticClass()));
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
	{
		return false;
	}

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
