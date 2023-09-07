// Shoot Game. All Rights Reserved.


#include "Props/ShootAmmoPickup.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "ShootUtils.h"

bool AShootAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = ShootUtils::GetShootPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}

	const auto WeaponComponent = ShootUtils::GetShootPlayerComponent<UWeaponComponent>(PlayerPawn);
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->TryToAddAmmo(WeaponType, BulletAmount);
}
