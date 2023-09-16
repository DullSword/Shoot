// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WeaponComponent.h"
#include "AIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UAIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

	virtual void NextWeapon() override;
};
