// Shoot Game. All Rights Reserved.

#include "Props/ShootHealthPickup.h"
#include "Components/HealthComponent.h"
#include "ShootUtils.h"

bool AShootHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = ShootUtils::GetShootPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}

	return HealthComponent->TryToAddHealth(HealingAmount);
}
