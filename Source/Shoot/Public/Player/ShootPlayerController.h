// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootPlayerController.generated.h"

class URespawnComponent;

/**
 *
 */
UCLASS()
class SHOOT_API AShootPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShootPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URespawnComponent* RespawnComponent;
};
