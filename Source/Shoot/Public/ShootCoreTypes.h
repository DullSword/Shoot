#pragma once

#include "ShootCoreTypes.generated.h"

class AShootWeapon;

// weapon
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AShootWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

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

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* CrossHairIcon;
};

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

// health
DECLARE_MULTICAST_DELEGATE(FOnDeadSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float)