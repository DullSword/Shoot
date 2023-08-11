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

	virtual void StartFire();
	virtual void StopFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere)
	float TraceMaxDistance = 1500.f;

	UPROPERTY(EditAnywhere)
	float DamageAmount = 10.f;

	void MakeDamage(FHitResult& HitResult);

	virtual void MakeShoot();

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	APlayerController* GetPlayerController() const;

	FVector GetMuzzleWorldLocation() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
};
