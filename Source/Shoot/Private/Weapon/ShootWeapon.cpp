// Shoot Game. All Rights Reserved.

#include "Weapon/ShootWeapon.h"
#include "GameFramework/Character.h"

// Sets default values
AShootWeapon::AShootWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void AShootWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));

	CurrentAmmo = DefaultAmmo;
}

void AShootWeapon::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}

void AShootWeapon::StopFire()
{
}

void AShootWeapon::MakeShoot()
{
}

APlayerController* AShootWeapon::GetPlayerController() const
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return nullptr;
	}

	return Character->GetController<APlayerController>();
}

bool AShootWeapon::GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const
{
	const auto PlayerController = GetPlayerController();
	if (!PlayerController)
	{
		return false;
	}

	PlayerController->GetPlayerViewPoint(OutViewLocation, OutViewRotation);
	return true;
}

bool AShootWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector	 ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AShootWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if (!GetWorld())
	{
		return;
	}

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

FTransform AShootWeapon::GetMuzzleTransform() const
{
	return WeaponMesh->GetSocketTransform(MuzzleSocketName);
}

void AShootWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clip is empty"));
		return;
	}

	CurrentAmmo.Bullets--;

	if (IsCurrentClipEmpty() && !IsTotalAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool AShootWeapon::IsTotalAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && IsCurrentClipEmpty() && CurrentAmmo.Clips == 0;
}

bool AShootWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool AShootWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Bullets == DefaultAmmo.Bullets && CurrentAmmo.Clips == DefaultAmmo.Clips;
}

void AShootWeapon::ChangeClip()
{
	int32 amount = DefaultAmmo.Bullets;

	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No more clips"));
			return;
		}
		const int32 SpendedBullets = DefaultAmmo.Bullets - CurrentAmmo.Bullets;
		const int32 ReplacedBullets = FMath::Min(SpendedBullets, CurrentAmmo.Clips);
		CurrentAmmo.Clips -= ReplacedBullets;
		amount = CurrentAmmo.Bullets + ReplacedBullets;
	}
	CurrentAmmo.Bullets = amount;
	UE_LOG(LogTemp, Display, TEXT("------ Change Clip ------"));
}

bool AShootWeapon::TryToAddAmmo(int32 BulletAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull())
	{
		return false;
	}

	if (CurrentAmmo.Bullets + BulletAmount < DefaultAmmo.Bullets)
	{
		CurrentAmmo.Bullets += BulletAmount;
	}
	else
	{
		const int32 OverflowBullets = CurrentAmmo.Bullets + BulletAmount - DefaultAmmo.Bullets;
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + OverflowBullets, 0, DefaultAmmo.Clips);

		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}

void AShootWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInfo);
}

bool AShootWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && (CurrentAmmo.Infinite || CurrentAmmo.Clips > 0);
}
