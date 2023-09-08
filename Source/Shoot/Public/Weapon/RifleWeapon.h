// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ShootWeapon.h"
#include "RifleWeapon.generated.h"

class UShootWeaponVFXComponent;

/**
 *
 */
UCLASS()
class SHOOT_API ARifleWeapon : public AShootWeapon
{
	GENERATED_BODY()

public:
	ARifleWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenShoots = 0.2f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 10.f;

	virtual void MakeShoot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShootTimer;

	void MakeDamage(FHitResult& HitResult);

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UShootWeaponVFXComponent* WeaponVFXComponent;
};
