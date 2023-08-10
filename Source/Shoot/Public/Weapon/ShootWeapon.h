// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootWeapon.generated.h"

UCLASS()
class SHOOT_API AShootWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShootWeapon();

	virtual void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere)
	float TraceMaxDistance = 1500.f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	void MakeShoot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	FVector GetMuzzleWorldLocation() const;
};
