// Shoot Game. All Rights Reserved.

#include "ShootGameModeBase.h"
#include "Player/ShootPlayerCharacter.h"
#include "Player/ShootPlayerController.h"
#include "UI/ShootHUD.h"
#include "AIController.h"
#include "ShootCoreTypes.h"
#include "Player/ShootCharacterBase.h"
#include "ShootPlayerState.h"
#include "Components/RespawnComponent.h"
#include "EngineUtils.h"
#include "Components/WeaponComponent.h"

AShootGameModeBase::AShootGameModeBase()
{
	DefaultPawnClass = AShootPlayerCharacter::StaticClass();
	PlayerControllerClass = AShootPlayerController::StaticClass();
	HUDClass = AShootHUD::StaticClass();
	PlayerStateClass = AShootPlayerState::StaticClass();
}

void AShootGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamInfos();

	CurrentRound = 1;
	StartRound();

	SetMatchState(EMatchState::MS_InProcess);
}

void AShootGameModeBase::SpawnBots()
{
	if (!GetWorld())
	{
		return;
	}

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass);
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
	// UE_LOG(LogTemp, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

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
			GameOver();
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
		Controller->GetPawn()->Reset(); // 为了RestartPlayerAtPlayerStart中的判断条件`NewPlayer->GetPawn() != nullptr`不成立，进入`else if (GetDefaultPawnClassForController(NewPlayer) != nullptr)`这个分支，重新生成Pawn
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AShootGameModeBase::CreateTeamInfos()
{
	if (!GetWorld())
	{
		return;
	}

	int32 TeamID = 1;
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

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? TEXT("Player") : TEXT("Bot"));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AShootGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogTemp, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void AShootGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller)
	{
		return;
	}

	const auto Character = Cast<AShootCharacterBase>(Controller->GetPawn());
	if (!Character)
	{
		return;
	}

	const auto PlayerState = Cast<AShootPlayerState>(Controller->PlayerState);
	if (!PlayerState)
	{
		return;
	}

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

UClass* AShootGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShootGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AShootPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AShootPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	if (RoundCountDown < GameData.MinSecondesForRespawn)
	{
		return;
	}

	StartRespawn(VictimController);
}

void AShootGameModeBase::LogPlayerInfo()
{
	if (!GetWorld())
	{
		return;
	}

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

		PlayerState->LogInfo();
	}
}

void AShootGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void AShootGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnComponent = Cast<URespawnComponent>(Controller->GetComponentByClass(URespawnComponent::StaticClass()));
	if (!RespawnComponent)
	{
		return;
	}

	RespawnComponent->Respawn(GameData.RespawnSeconds);
}

void AShootGameModeBase::GameOver()
{
	UE_LOG(LogTemp, Display, TEXT("======== GAME OVER ========"));
	LogPlayerInfo();

	for (const auto& Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(EMatchState::MS_GameOver);
}

void AShootGameModeBase::SetMatchState(EMatchState NewMatchState)
{
	if (MatchState == NewMatchState)
	{
		return;
	}

	MatchState = NewMatchState;

	OnMatchStateChanged.Broadcast(NewMatchState);
}

bool AShootGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto Ret = Super::SetPause(PC, CanUnpauseDelegate);
	if (Ret)
	{
		StopAllFire();
		SetMatchState(EMatchState::MS_Pause);
	}

	return Ret;
}

bool AShootGameModeBase::ClearPause()
{
	const auto Ret = Super::ClearPause();
	if (Ret)
	{
		SetMatchState(EMatchState::MS_InProcess);
	}

	return Ret;
}

void AShootGameModeBase::StopAllFire()
{
	for (const auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (!Pawn)
		{
			continue;
		}
		const auto WeaponComponent = Cast<UWeaponComponent>(Pawn->GetComponentByClass(UWeaponComponent::StaticClass()));
		if (!WeaponComponent)
		{
			continue;
		}
		WeaponComponent->StopFire();
	}
}
