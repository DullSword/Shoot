// Shoot Game. All Rights Reserved.

#include "UI/ShootGoToMenuWidget.h"
#include "Components/Button.h"
#include "ShootGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UShootGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UShootGoToMenuWidget::OnGoToMenu);
	}
}

void UShootGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld())
	{
		return;
	}

	const auto GameInstance = GetWorld()->GetGameInstance<UShootGameInstance>();
	if (!GameInstance)
	{
		return;
	}

	if (GameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}
