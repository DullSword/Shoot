// Shoot Game. All Rights Reserved.

#include "UI/ShootGameDataWidget.h"
#include "ShootGameModeBase.h"
#include "ShootPlayerState.h"

int32 UShootGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetRoundCountDown() : 0;
}

int32 UShootGameDataWidget::GetCurrentRound() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 UShootGameDataWidget::GetTotalRound() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UShootGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

AShootGameModeBase* UShootGameDataWidget::GetGameMode() const
{
	if (!GetWorld())
	{
		return nullptr;
	}

	return Cast<AShootGameModeBase>(GetWorld()->GetAuthGameMode());
}

AShootPlayerState* UShootGameDataWidget::GetPlayerState() const
{
	return GetOwningPlayerState<AShootPlayerState>();
}
