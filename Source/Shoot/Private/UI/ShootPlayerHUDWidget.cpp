// Shoot Game. All Rights Reserved.


#include "UI/ShootPlayerHUDWidget.h"
#include "components/HealthComponent.h"
#include "Components/WeaponComponent.h"

float UShootPlayerHUDWidget::GetHealthPercent() const {
	const auto Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return 0.f;
	}

	const auto Component = Pawn->GetComponentByClass(UHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UHealthComponent>(Component);
	if (!HealthComponent)
	{
		return 0.f;
	}

	return HealthComponent->GetHealthPercent();
}

bool UShootPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UShootPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

UWeaponComponent* UShootPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return nullptr;
	}

	const auto Component = Pawn->GetComponentByClass(UWeaponComponent::StaticClass());
	return Cast<UWeaponComponent>(Component);
}
