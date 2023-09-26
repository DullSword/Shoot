// Shoot Game. All Rights Reserved.

#include "Player/ShootPlayerController.h"
#include "Components/RespawnComponent.h"

AShootPlayerController::AShootPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));
}
