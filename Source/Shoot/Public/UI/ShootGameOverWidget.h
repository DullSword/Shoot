// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShootWidgetBase.h"
#include "ShootGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

/**
 *
 */
UCLASS()
class SHOOT_API UShootGameOverWidget : public UShootWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

private:
	void OnMatchStateChanged(EMatchState NewState);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();
};
