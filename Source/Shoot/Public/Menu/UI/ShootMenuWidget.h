// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShootWidgetBase.h"
#include "ShootMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USoundCue;

/**
 *
 */
UCLASS()
class SHOOT_API UShootMenuWidget : public UShootWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* StartGameSound;

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TArray<UShootLevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	UShootGameInstance* GetShootGameInstance() const;

	virtual void OnOutAnimationFinished() override;
};
