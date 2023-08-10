// Shoot Game. All Rights Reserved.

#include "Weapon/ShootWeapon.h"
#include "DrawDebugHelpers.h"
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
}

void AShootWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));

	MakeShoot();
}

void AShootWeapon::MakeShoot()
{
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
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 2.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);

		UE_LOG(LogTemp, Warning, TEXT("Bone name: %s"), *HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.f, 0, 2.f);
	}
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

void AShootWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld())
	{
		return;
	}

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

FVector AShootWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}
