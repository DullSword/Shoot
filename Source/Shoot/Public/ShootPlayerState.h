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

private:
	int32 TeamID;
	FLinearColor TeamColor;
};
