// Shoot Game. All Rights Reserved.

#include "UI/ShootHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "ShootGameModeBase.h"
#include "ShootCoreTypes.h"

void AShootHUD::DrawHUD()
{
	Super::DrawHUD();

	// DrawCrossHair();
}

void AShootHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
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
	UE_LOG(LogTemp, Warning, TEXT("NewMatchState: %s"), *UEnum::GetValueAsString(NewMatchState));
}
