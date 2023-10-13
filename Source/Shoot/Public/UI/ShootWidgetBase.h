// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootWidgetBase.generated.h"

class USoundCue;

/**
 *
 */
UCLASS()
class SHOOT_API UShootWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void Enter();
	void Out();

protected:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* EnterAnimation;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* OutAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* OpenSound;

private:
	UFUNCTION()
	virtual void OnOutAnimationFinished();
};
