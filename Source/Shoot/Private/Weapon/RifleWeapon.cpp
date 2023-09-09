// Shoot Game. All Rights Reserved.

#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/ShootWeaponVFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ARifleWeapon::ARifleWeapon()
{
	WeaponVFXComponent = CreateDefaultSubobject<UShootWeaponVFXComponent>(TEXT("WeaponVFXComponent"));
}

void ARifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponVFXComponent);
}

void ARifleWeapon::StartFire()
{
	Super::StartFire();

	InitMuzzleVFX();

	GetWorldTimerManager().SetTimer(ShootTimer, this, &ARifleWeapon::MakeShoot, TimeBetweenShoots, true);
	MakeShoot();
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(ShootTimer);

	SetMuzzleVFXVisibility(false);
}

void ARifleWeapon::MakeShoot()
{
	Super::MakeShoot();

	if (IsTotalAmmoEmpty())
	{
		StopFire();
		return;
	}

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

	DecreaseAmmo();

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceVFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);

		TraceVFXEnd = HitResult.ImpactPoint;
		WeaponVFXComponent->PlayImpactFX(HitResult);

		UE_LOG(LogTemp, Warning, TEXT("Bone name: %s"), *HitResult.BoneName.ToString());
	}

	SpawnTraceVFX(GetMuzzleTransform().GetLocation(), TraceVFXEnd);
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

void ARifleWeapon::InitMuzzleVFX()
{
	if (!MuzzleNiagaraComponent)
	{
		MuzzleNiagaraComponent = SpawnMuzzleVFX();
	}
	SetMuzzleVFXVisibility(true);
}

void ARifleWeapon::SetMuzzleVFXVisibility(bool Visible)
{
	if (!MuzzleNiagaraComponent)
	{
		return;
	}

	MuzzleNiagaraComponent->SetVisibility(Visible);
}

void ARifleWeapon::SpawnTraceVFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		TraceNiagaraSystem,
		TraceStart);

	if (!TraceNiagaraComponent)
	{
		return;
	}

	TraceNiagaraComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
}
