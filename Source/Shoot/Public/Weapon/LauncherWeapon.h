// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShootWeapon.h"
#include "LauncherWeapon.generated.h"

class AShootProjectile;

/**
 *
 */
UCLASS()
class SHOOT_API ALauncherWeapon : public AShootWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenShoots = 1.f;

	virtual void MakeShoot() override;

private:
	FTimerHandle ShootTimer;

	bool CanFire = true;
};
