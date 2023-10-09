// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootHealthBarWidget.generated.h"

class UProgressBar;

/**
 *
 */
UCLASS()
class SHOOT_API UShootHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealthProgress(float Percent);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float PercentVisibilityThreshold = 0.8f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor GoodColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;
};
