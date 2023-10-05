// Shoot Game. All Rights Reserved.

#include "UI/ShootPauseWidget.h"
#include "Components/Button.h"
#include "ShootGameModeBase.h"

void UShootPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UShootPauseWidget::ClearPause);
	}
}

void UShootPauseWidget::ClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}

	GetWorld()->GetAuthGameMode()->ClearPause();
}
