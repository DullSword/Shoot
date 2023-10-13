// Shoot Game. All Rights Reserved.

#include "UI/ShootHUD.h"
#include "Engine/Canvas.h"
#include "UI/ShootWidgetBase.h"
#include "ShootGameModeBase.h"

void AShootHUD::DrawHUD()
{
	Super::DrawHUD();

	// DrawCrossHair();
}

void AShootHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EMatchState::MS_InProcess, CreateWidget<UShootWidgetBase>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EMatchState::MS_Pause, CreateWidget<UShootWidgetBase>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EMatchState::MS_GameOver, CreateWidget<UShootWidgetBase>(GetWorld(), GameOverWidgetClass));

	for (const auto& GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget)
		{
			continue;
		}

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (const auto World = GetWorld(); World)
	{
		const auto GameMode = Cast<AShootGameModeBase>(World->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AShootHUD::OnMatchStateChanged);
		}
	}
}

void AShootHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void AShootHUD::OnMatchStateChanged(EMatchState NewMatchState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(NewMatchState))
	{
		CurrentWidget = GameWidgets[NewMatchState];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Enter();
	}

	UE_LOG(LogTemp, Warning, TEXT("NewMatchState: %s"), *UEnum::GetValueAsString(NewMatchState));
}
