// Shoot Game. All Rights Reserved.

#include "UI/ShootPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UShootPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock)
	{
		return;
	}
	PlayerNameTextBlock->SetText(Text);
}

void UShootPlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock)
	{
		return;
	}

	KillsTextBlock->SetText(Text);
}

void UShootPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock)
	{
		return;
	}

	DeathsTextBlock->SetText(Text);
}

void UShootPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock)
	{
		return;
	}

	TeamTextBlock->SetText(Text);
}

void UShootPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage)
	{
		return;
	}
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UShootPlayerStatRowWidget::SetTeamColor(FLinearColor Color)
{
	if (!TeamImage)
	{
		return;
	}
	TeamImage->SetColorAndOpacity(Color);
}
