// Shoot Game. All Rights Reserved.

#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"

void ARifleWeapon::StartFire()
{
	Super::StartFire();

	MakeShoot();
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ARifleWeapon::MakeShoot, TimeBetweenShoots, true);
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ARifleWeapon::MakeShoot()
{
	Super::MakeShoot();

	if (!GetWorld())
	{
		return;
	}

	FVector TraceStart;
	FVector TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleTransform().GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 2.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);

		UE_LOG(LogTemp, Warning, TEXT("Bone name: %s"), *HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleTransform().GetLocation(), TraceEnd, FColor::Red, false, 3.f, 0, 2.f);
	}
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector	 ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}

	TraceStart = ViewLocation;
	float		  ConeHalfAngleRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), ConeHalfAngleRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ARifleWeapon::MakeDamage(FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)
	{
		return;
	}
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}