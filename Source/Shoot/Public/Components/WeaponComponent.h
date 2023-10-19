// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootCoreTypes.h"
#include "WeaponComponent.generated.h"

class AShootWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	virtual void StartFire();
	void StopFire();

	virtual void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;
	const AShootWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	bool TryToAddAmmo(TSubclassOf<AShootWeapon> WeaponType, int32 BulletAmount);

	void Zoom();
	void SetZoom(bool bEnabled);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponDatas;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	TArray<AShootWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	// Zoom
	bool bZoom = false;

private:
	UPROPERTY()
	AShootWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	void SpawnWeapon();
	void AttachWeaponToSocket(AShootWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimations();

	bool EquipAnimInProcess = false;
	bool CanFire() const;
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool ReloadAnimInProcess = false;
	bool CanReload() const;
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	void OnClipEmpty();
	void ChangeClip();
};
