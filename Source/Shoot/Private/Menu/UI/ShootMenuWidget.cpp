// Shoot Game. All Rights Reserved.

#include "Menu/UI/ShootMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShootGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/UI/ShootLevelItemWidget.h"
#include "Components/HorizontalBox.h"

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

	InitLevelItems();

	if (!IsAnimationPlaying(EnterAnimation))
	{
		PlayAnimation(EnterAnimation);
	}
}

void UShootMenuWidget::InitLevelItems()
{
	if (!LevelItemsBox)
	{
		return;
	}

	LevelItemsBox->ClearChildren();

	const auto GameInstance = GetShootGameInstance();
	if (!GameInstance)
	{
		return;
	}

	const auto LevelsData = GameInstance->GetLevelsData();
	if (LevelsData.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Levels data must not be empty!"));
		return;
	}

	for (const auto& LevelData : LevelsData)
	{
		const auto LevelItemWidget = CreateWidget<UShootLevelItemWidget>(this, LevelItemWidgetClass);
		if (!LevelItemWidget)
		{
			continue;
		}

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &UShootMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (GameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(LevelsData[0]);
	}
	else
	{
		OnLevelSelected(GameInstance->GetStartupLevel());
	}
}

void UShootMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	for (const auto LevelItemWidget : LevelItemWidgets)
	{
		if (!LevelItemWidget)
		{
			continue;
		}

		const auto bIsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
		LevelItemWidget->SetSelected(bIsSelected);
	}

	const auto GameInstance = GetShootGameInstance();
	if (!GameInstance)
	{
		return;
	}

	GameInstance->SetStartupLevel(Data);
}

void UShootMenuWidget::OnStartGame()
{
	const auto GameInstance = GetShootGameInstance();
	if (!GameInstance)
	{
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
}

void UShootMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

UShootGameInstance* UShootMenuWidget::GetShootGameInstance() const
{
	if (!GetWorld())
	{
		return nullptr;
	}

	return GetWorld()->GetGameInstance<UShootGameInstance>();
}
