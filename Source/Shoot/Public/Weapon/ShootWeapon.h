// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootCoreTypes.h"
#include "ShootWeapon.generated.h"

class UNiagaraComponent;
class USoundCue;

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

	bool IsTotalAmmoEmpty() const;
	bool TryToAddAmmo(int32 BulletAmount);

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }
	float GetTraceMaxDistance() const { return TraceMaxDistance; }

	virtual void SetZoom(bool bEnabled){};

	FOnClipEmptySignature OnClipEmpty;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere)
	float TraceMaxDistance = 1500.f;

	virtual void MakeShoot();

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	AController* GetController() const;

	FTransform GetMuzzleTransform() const;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FAmmoData DefaultAmmo{ 15, 10, false };

	void DecreaseAmmo();
	bool IsCurrentClipEmpty() const;
	bool IsAmmoFull() const;
	void LogAmmo();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FWeaponUIData UIData;

	// MuzzleVFX
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UNiagaraSystem* MuzzleVFX;

	UNiagaraComponent* SpawnMuzzleVFX();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* NoAmmoSound;

private:
	FAmmoData CurrentAmmo;
};
