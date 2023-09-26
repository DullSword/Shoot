// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootPlayerState.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API AShootPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetTeamID(int32 ID) { TeamID = ID; }
	int32 GetTeamID() { return TeamID; }

	void SetTeamColor(FLinearColor Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() { return TeamColor; }

	void AddKill() { ++KillsNum; }
	int32 GetKillsNum() { return KillsNum; }

	void AddDeath() { ++DeathsNum; }
	int32 GetDeathsNum() const { return DeathsNum; }

	void LogInfo();

private:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathsNum = 0;
};
