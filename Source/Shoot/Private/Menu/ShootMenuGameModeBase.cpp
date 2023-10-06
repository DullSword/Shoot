// Shoot Game. All Rights Reserved.

#include "Menu/ShootMenuGameModeBase.h"
#include "Menu/ShootMenuPlayerController.h"
#include "Menu/UI/ShootMenuHUD.h"

AShootMenuGameModeBase::AShootMenuGameModeBase()
{
	PlayerControllerClass = AShootMenuPlayerController::StaticClass();
	HUDClass = AShootMenuHUD::StaticClass();
}
