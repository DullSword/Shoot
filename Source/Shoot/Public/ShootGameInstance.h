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
	FName GetMenuLevelName() { return MenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;
};
