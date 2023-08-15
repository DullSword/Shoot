// Shoot Game. All Rights Reserved.

#include "Weapon/LauncherWeapon.h"
#include "Weapon/ShootProjectile.h"

void ALauncherWeapon::StartFire()
{
	MakeShoot();
}

void ALauncherWeapon::MakeShoot()
{
	if (!GetWorld())
	{
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}

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
