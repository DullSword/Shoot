// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootGameDataWidget.generated.h"

class AShootGameModeBase;
class AShootPlayerState;

/**
 *
 */
UCLASS()
class SHOOT_API UShootGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRound() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRound() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

private:
	AShootGameModeBase* GetGameMode() const;
	AShootPlayerState* GetPlayerState() const;
};
