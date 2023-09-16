// Shoot Game. All Rights Reserved.

#include "Components/AIWeaponComponent.h"
#include "Weapon/ShootWeapon.h"

void UAIWeaponComponent::StartFire()
{
	if (GetCurrentWeapon()->IsTotalAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		Super::StartFire();
	}
}

void UAIWeaponComponent::NextWeapon()
{
	if (!CanEquip())
	{
		return;
	}

	int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextWeaponIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextWeaponIndex]->IsTotalAmmoEmpty())
		{
			break;
		}

		NextWeaponIndex = (NextWeaponIndex + 1) % Weapons.Num();
	}

	if (NextWeaponIndex != CurrentWeaponIndex)
	{
		CurrentWeaponIndex = NextWeaponIndex;
		EquipWeapon(NextWeaponIndex);
	}
}
