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

bool UShootPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return false;
	}

	const auto Component = Pawn->GetComponentByClass(UWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetWeaponUIData(UIData);
}
