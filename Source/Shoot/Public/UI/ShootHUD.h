// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootCoreTypes.h"
#include "ShootHUD.generated.h"

class UShootWidgetBase;

/**
 *
 */
UCLASS()
class SHOOT_API AShootHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	void DrawCrossHair();

	UPROPERTY()
	TMap<EMatchState, UShootWidgetBase*> GameWidgets;

	UPROPERTY()
	UShootWidgetBase* CurrentWidget = nullptr;

	void OnMatchStateChanged(EMatchState NewMatchState);
};
