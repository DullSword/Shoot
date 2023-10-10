// Shoot Game. All Rights Reserved.

#include "UI/ShootGameOverWidget.h"
#include "ShootGameModeBase.h"
#include "ShootCoreTypes.h"
#include "UI/ShootPlayerStatRowWidget.h"
#include "ShootPlayerState.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UShootGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto GameMode = Cast<AShootGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UShootGameOverWidget::OnMatchStateChanged);
		}
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UShootGameOverWidget::OnResetLevel);
	}
}

void UShootGameOverWidget::OnMatchStateChanged(EMatchState NewState)
{
	if (NewState == EMatchState::MS_GameOver)
	{
		UpdatePlayersStat();
	}
}

void UShootGameOverWidget::UpdatePlayersStat()
{
	if (!GetWorld() || !PlayerStatBox)
	{
		return;
	}

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
		{
			continue;
		}
		const auto PlayerState = Cast<AShootPlayerState>(Controller->PlayerState);
		if (!PlayerState)
		{
			continue;
		}

		const auto PlayerStatRowWidget = CreateWidget<UShootPlayerStatRowWidget>(this, PlayerStatRowWidgetClass);
		if (!PlayerStatRowWidget)
		{
			continue;
		}
		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKillsNum())));
		PlayerStatRowWidget->SetDeaths(FText::FromString(FString::FromInt(PlayerState->GetDeathsNum())));
		PlayerStatRowWidget->SetTeam(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}

void UShootGameOverWidget::OnResetLevel()
{
	auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
