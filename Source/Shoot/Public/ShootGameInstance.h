// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootGameInstance.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UShootGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FName GetStartupLevelName() { return StartupLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;
};
