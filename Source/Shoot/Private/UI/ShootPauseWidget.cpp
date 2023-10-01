// Shoot Game. All Rights Reserved.

#include "UI/ShootPauseWidget.h"
#include "Components/Button.h"
#include "ShootGameModeBase.h"

bool UShootPauseWidget::Initialize()
{
	const bool InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UShootPauseWidget::ClearPause);
	}

	return InitStatus;
}

void UShootPauseWidget::ClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}

	GetWorld()->GetAuthGameMode()->ClearPause();
}
