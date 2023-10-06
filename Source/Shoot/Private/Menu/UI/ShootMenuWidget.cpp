// Shoot Game. All Rights Reserved.

#include "Menu/UI/ShootMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UShootMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UShootMenuWidget::OnStartGame);
	}
}

void UShootMenuWidget::OnStartGame()
{
	const FName StartupLevelName = TEXT("TestLevel");
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
