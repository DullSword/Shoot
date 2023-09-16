// Shoot Game. All Rights Reserved.

#include "Weapon/LauncherWeapon.h"
#include "Weapon/ShootProjectile.h"

void ALauncherWeapon::StartFire()
{
	Super::StartFire();

	MakeShoot();
}

void ALauncherWeapon::MakeShoot()
{
	if (!CanFire)
	{
		return;
	}
	else
	{
		CanFire = false;
		GetWorldTimerManager().SetTimer(
			ShootTimer,
			[this]() { CanFire = true; },
			TimeBetweenShoots,
			false);
	}

	if (IsTotalAmmoEmpty() || !GetWorld())
	{
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}

	DecreaseAmmo();

	// Muzzle VFX
	SpawnMuzzleVFX();

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleTransform().GetLocation()).GetSafeNormal();

	const FTransform  SpawnTransform{ GetMuzzleTransform() };
	AShootProjectile* Projectile = GetWorld()->SpawnActorDeferred<AShootProjectile>(ProjectileClass, SpawnTransform);

	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
}
