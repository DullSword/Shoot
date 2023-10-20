// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootCoreTypes.h"
#include "ShootGameInstance.generated.h"

class USoundClass;

/**
 *
 */
UCLASS()
class SHOOT_API UShootGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevelData() const { return StartupLevelData; }
	void SetStartupLevelData(const FLevelData& Data) { StartupLevelData = Data; };

	FName GetMenuLevelName() { return MenuLevelName; }

	TArray<FLevelData> GetLevelsData() const { return LevelsData; }

	void ToggleVolume();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FLevelData> LevelsData;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundClass* MasterSoundClass;

private:
	FLevelData StartupLevelData;
};
