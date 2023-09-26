// Shoot Game. All Rights Reserved.


#include "ShootPlayerState.h"

void AShootPlayerState::LogInfo()
{
	UE_LOG(LogTemp, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
