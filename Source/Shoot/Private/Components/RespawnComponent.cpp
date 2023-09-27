// Shoot Game. All Rights Reserved.

#include "Components/RespawnComponent.h"
#include "ShootGameModeBase.h"

URespawnComponent::URespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URespawnComponent::Respawn(int32 RespawnSeconds)
{
	if (!GetWorld())
	{
		return;
	}

	RespawnCountDown = RespawnSeconds;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &URespawnComponent::RespawnTimerUpdate, 1.f, true);
}

void URespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld())
		{
			return;
		}
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AShootGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode)
		{
			return;
		}

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}

bool URespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}
