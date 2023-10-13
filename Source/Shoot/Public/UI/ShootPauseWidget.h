// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShootWidgetBase.h"
#include "ShootPauseWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SHOOT_API UShootPauseWidget : public UShootWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

private:
	UFUNCTION()
	void ClearPause();
};
