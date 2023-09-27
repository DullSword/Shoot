// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootSpectatorWidget.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UShootSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRespawnCountDownTime(int32& CountDownTime) const;
};
