// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootWeapon.generated.h"

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool Infinite;
};

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

UCLASS()
class SHOOT_API AShootWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShootWeapon();

	virtual void StartFire();
	virtual void StopFire();

	bool CanReload() const;
	void ChangeClip();

	FOnClipEmptySignature OnClipEmpty;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere)
	float TraceMaxDistance = 1500.f;

	virtual void MakeShoot();

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	APlayerController* GetPlayerController() const;

	FTransform GetMuzzleTransform() const;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo{ 15, 10, false };

	void DecreaseAmmo();
	bool IsTotalAmmoEmpty() const;
	bool IsCurrentClipEmpty() const;
	void LogAmmo();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	FAmmoData CurrentAmmo;
};
