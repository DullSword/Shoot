// Shoot Game. All Rights Reserved.


#include "UI/ShootPlayerHUDWidget.h"
#include "components/HealthComponent.h"
#include "Components/WeaponComponent.h"

float UShootPlayerHUDWidget::GetHealthPercent() const {
	const auto HealthComponent = GetHealthComponent();
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

bool UShootPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	return HealthComponent && !HealthComponent->IsDead();
}

bool UShootPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

UHealthComponent* UShootPlayerHUDWidget::GetHealthComponent() const
{
	const auto Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return nullptr;
	}

	const auto Component = Pawn->GetComponentByClass(UHealthComponent::StaticClass());
	return Cast<UHealthComponent>(Component);
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
