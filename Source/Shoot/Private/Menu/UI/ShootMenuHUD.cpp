// Shoot Game. All Rights Reserved.

#include "Menu/UI/ShootMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Menu/UI/ShootMenuWidget.h"

void AShootMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto MenuWidget = CreateWidget<UShootMenuWidget>(GetWorld(), MenuWidgetClass);
	if (!MenuWidget)
	{
		return;
	}

	MenuWidget->AddToViewport();
}
