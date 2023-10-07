// Shoot Game. All Rights Reserved.

#include "Menu/UI/ShootMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShootGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UShootMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UShootMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UShootMenuWidget::OnQuitGame);
	}
}

void UShootMenuWidget::OnStartGame()
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

	if (GameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}

void UShootMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
