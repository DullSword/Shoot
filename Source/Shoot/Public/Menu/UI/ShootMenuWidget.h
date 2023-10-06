// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootMenuWidget.generated.h"

class UButton;

/**
 *
 */
UCLASS()
class SHOOT_API UShootMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

private:
	UFUNCTION()
	void OnStartGame();
};
