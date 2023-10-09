// Shoot Game. All Rights Reserved.

#include "UI/ShootHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UShootHealthBarWidget::SetHealthProgress(float Percent)
{
	if (!HealthProgressBar)
	{
		return;
	}

	const auto HealthBarVisibility = (Percent < PercentVisibilityThreshold && !FMath::IsNearlyZero(Percent)) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	HealthProgressBar->SetVisibility(HealthBarVisibility);
	HealthProgressBar->SetFillColorAndOpacity(Percent < PercentColorThreshold ? BadColor : GoodColor);
	HealthProgressBar->SetPercent(Percent);
}
