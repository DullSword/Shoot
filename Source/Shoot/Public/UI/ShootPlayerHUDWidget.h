// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootCoreTypes.h"
#include "ShootPlayerHUDWidget.generated.h"

class UProgressBar;

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

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString FormatBullets(int32 BulletsNum) const;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor GoodColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);

	void OnNewPawn(APawn* NewPawn);

	void UpdateHealthBar();
};
