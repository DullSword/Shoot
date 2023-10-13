// Shoot Game. All Rights Reserved.

#include "UI/ShootPlayerHUDWidget.h"
#include "components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "ShootUtils.h"
#include "Components/ProgressBar.h"

void UShootPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (const auto Controller = GetOwningPlayer(); Controller)
	{
		Controller->GetOnNewPawnNotifier().AddUObject(this, &UShootPlayerHUDWidget::OnNewPawn);
	}
	OnNewPawn(GetOwningPlayerPawn());
}

float UShootPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = ShootUtils::GetShootPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent)
	{
		return 0.f;
	}

	return HealthComponent->GetHealthPercent();
}

bool UShootPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = ShootUtils::GetShootPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UShootPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = ShootUtils::GetShootPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
	{
		return false;
	}

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UShootPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = ShootUtils::GetShootPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UShootPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

void UShootPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.f)
	{
		//OnTakeDamage();

		if (!IsAnimationPlaying(DamagedAnimation))
		{
			PlayAnimation(DamagedAnimation);
		}
	}

	UpdateHealthBar();
}

void UShootPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = ShootUtils::GetShootPlayerComponent<UHealthComponent>(NewPawn);
	if (HealthComponent)
	{
		HealthComponent->OnHealthChange.AddUObject(this, &UShootPlayerHUDWidget::OnHealthChanged);
	}

	UpdateHealthBar();

	Enter();
}

void UShootPlayerHUDWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() < PercentColorThreshold ? BadColor : GoodColor);
	}
}

FString UShootPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNum = MaxLen - BulletStr.Len();

	if (SymbolsNum > 0)
	{
		BulletStr = FString::ChrN(SymbolsNum, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}
