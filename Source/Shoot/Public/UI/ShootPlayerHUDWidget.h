// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootCoreTypes.h"
#include "ShootPlayerHUDWidget.generated.h"

class UHealthComponent;
class UWeaponComponent;

/**
 *
 */
UCLASS()
class SHOOT_API UShootPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable)
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayerSpectating() const;

private:
	UHealthComponent* GetHealthComponent() const;
	UWeaponComponent* GetWeaponComponent() const;
};