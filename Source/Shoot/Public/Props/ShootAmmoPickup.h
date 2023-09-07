// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Props/ShootPickupBase.h"
#include "ShootAmmoPickup.generated.h"

class AShootWeapon;

/**
 *
 */
UCLASS()
class SHOOT_API AShootAmmoPickup : public AShootPickupBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (ClampMin = "1", ClampMax = "10"))
	int32 BulletAmount = 10;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	TSubclassOf<AShootWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
