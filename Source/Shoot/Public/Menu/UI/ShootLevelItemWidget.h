// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootCoreTypes.h"
#include "ShootLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

/**
 *
 */
UCLASS()
class SHOOT_API UShootLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelectedSignature OnLevelSelected;

	FLevelData GetLevelData() const { return LevelData; }
	void SetLevelData(const FLevelData& Data);

	void SetSelected(bool bIsSelected);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* LevelThumb;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelItemClicked();

	UFUNCTION()
	void OnLevelItemHovered();

	UFUNCTION()
	void OnLevelItemUnHovered();
};
