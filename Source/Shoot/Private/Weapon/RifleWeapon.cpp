// Shoot Game. All Rights Reserved.

#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/ShootWeaponVFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

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

	InitFX();

	GetWorldTimerManager().SetTimer(ShootTimer, this, &ARifleWeapon::MakeShoot, TimeBetweenShoots, true);
	MakeShoot();
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(ShootTimer);

	SetFXActive(false);
}

void ARifleWeapon::MakeShoot()
{
	Super::MakeShoot();

	if (IsTotalAmmoEmpty())
	{
		UGameplayStatics::PlaySoundAtLocation(this, NoAmmoSound, GetActorLocation());
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

		// UE_LOG(LogTemp, Warning, TEXT("Bone name: %s"), *HitResult.BoneName.ToString());
	}

	SpawnTraceVFX(GetMuzzleTransform().GetLocation(), TraceVFXEnd);
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}

	TraceStart = ViewLocation;
	float ConeHalfAngleRad = FMath::DegreesToRadians(BulletSpread);
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

	FPointDamageEvent PointDamageEvent{};
	PointDamageEvent.HitInfo = HitResult;
	DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void ARifleWeapon::InitFX()
{
	if (!MuzzleNiagaraComponent)
	{
		MuzzleNiagaraComponent = SpawnMuzzleVFX();
	}

	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	SetFXActive(true);
}

void ARifleWeapon::SetFXActive(bool bIsActive)
{
	if (!MuzzleNiagaraComponent)
	{
		return;
	}

	MuzzleNiagaraComponent->SetVisibility(bIsActive);

	if (!FireAudioComponent)
	{
		return;
	}

	FireAudioComponent->SetPaused(!bIsActive);
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

void ARifleWeapon::SetZoom(bool bEnabled)
{
	const auto Controller = Cast<APlayerController>(GetController());

	if (!Controller || !Controller->PlayerCameraManager)
	{
		return;
	}

	if (bEnabled)
	{
		DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
	}

	Controller->PlayerCameraManager->SetFOV(bEnabled ? FOVZoomAngle : DefaultCameraFOV);
}
