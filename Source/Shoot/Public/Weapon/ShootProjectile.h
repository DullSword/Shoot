// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOT_API AShootProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShootProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float LifeSeconds = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool DoFullDamage = false;

private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;
};
