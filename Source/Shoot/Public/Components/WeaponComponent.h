// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AShootWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AShootWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	void StartFire();
	void StopFire();

	void NextWeapon();
	void Reload();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponDatas;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

private:
	UPROPERTY()
	AShootWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AShootWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	void SpawnWeapon();
	void AttachWeaponToSocket(AShootWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimations();

	bool EquipAnimInProcess = false;
	bool CanFire() const;
	bool CanEquip() const;
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool ReloadAnimInProcess = false;
	bool CanReload() const;
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	template <typename T>
	T* FindFirstNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation)
		{
			return nullptr;
		}

		const auto& NotifyEvents = Animation->Notifies;
		for (const auto& NotifyEvent : NotifyEvents)
		{
			auto Notify = Cast<T>(NotifyEvent.Notify);
			if (Notify)
			{
				return Notify;
			}
		}

		return nullptr;
	}
};
