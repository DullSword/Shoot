// Shoot Game. All Rights Reserved.

#include "Player/ShootPlayerController.h"
#include "Components/RespawnComponent.h"
#include "ShootGameModeBase.h"

AShootPlayerController::AShootPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));
}

void AShootPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld())
	{
		return;
	}

	const auto GameMode = Cast<AShootGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}
	GameMode->OnMatchStateChanged.AddUObject(this, &AShootPlayerController::OnMatchStateChanged);
}

void AShootPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent)
	{
		return;
	}

	InputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &AShootPlayerController::OnPauseGame);
}

void AShootPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AShootPlayerController::OnMatchStateChanged(EMatchState NewState)
{
	if (NewState == EMatchState::MS_InProcess)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
