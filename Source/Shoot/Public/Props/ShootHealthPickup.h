// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Props/ShootPickupBase.h"
#include "ShootHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API AShootHealthPickup : public AShootPickupBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (ClampMin = "1", ClampMax = "100"))
	float HealingAmount = 100.f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
