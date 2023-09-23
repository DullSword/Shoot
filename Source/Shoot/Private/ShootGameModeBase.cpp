// Shoot Game. All Rights Reserved.

#include "ShootGameModeBase.h"
#include "Player/ShootCharacter.h"
#include "Player/ShootPlayerController.h"
#include "UI/ShootHUD.h"
#include "AIController.h"
#include "ShootCoreTypes.h"

AShootGameModeBase::AShootGameModeBase()
{
	DefaultPawnClass = AShootCharacter::StaticClass();
	PlayerControllerClass = AShootPlayerController::StaticClass();
	HUDClass = AShootHUD::StaticClass();
}

void AShootGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();

	CurrentRound = 1;
	StartRound();
}

void AShootGameModeBase::SpawnBots()
{
	if (!GetWorld())
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);
		RestartPlayer(AIController);
	}
}

void AShootGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundSeconds;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShootGameModeBase::GameTimerUpdate, 1.f, true);
}

void AShootGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogTemp, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (++CurrentRound <= GameData.RoundsNum)
		{
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("======== GAME OVER ========"));
		}
	}
}

void AShootGameModeBase::ResetPlayers()
{
	if (!GetWorld())
	{
		return;
	}

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AShootGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset(); //为了RestartPlayerAtPlayerStart能进入`else if (GetDefaultPawnClassForController(NewPlayer) != nullptr)`这个分支，重新生成Pawn
	}
	RestartPlayer(Controller);
}

UClass* AShootGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
