// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootCoreTypes.h"
#include "ShootGameInstance.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UShootGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; };

	FName GetMenuLevelName() { return MenuLevelName; }

	TArray<FLevelData> GetLevelsData() const { return LevelsData; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FLevelData> LevelsData;

private:
	FLevelData StartupLevel;
};
