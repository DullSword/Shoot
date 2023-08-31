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

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

FTransform AShootWeapon::GetMuzzleTransform() const
{
	return WeaponMesh->GetSocketTransform(MuzzleSocketName);
}

void AShootWeapon::DecreaseAmmo()
{
	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsCurrentClipEmpty() && !IsTotalAmmoEmpty())
	{
		ChangeClip();
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

void AShootWeapon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	if (!CurrentAmmo.Infinite)
	{
		CurrentAmmo.Clips--;
	}
	UE_LOG(LogTemp, Display, TEXT("------ Change Clip ------"));
}

void AShootWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInfo);
}
