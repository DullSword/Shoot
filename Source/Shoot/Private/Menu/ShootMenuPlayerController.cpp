// Shoot Game. All Rights Reserved.

#include "Menu/ShootMenuPlayerController.h"

void AShootMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}
