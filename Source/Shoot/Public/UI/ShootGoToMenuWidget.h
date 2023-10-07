// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootGoToMenuWidget.generated.h"

class UButton;

/**
 *
 */
UCLASS()
class SHOOT_API UShootGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* GoToMenuButton;

private:
	UFUNCTION()
	void OnGoToMenu();
};
