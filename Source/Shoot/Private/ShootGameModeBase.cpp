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
}

void AShootGameModeBase::SpawnBots()
{
	if (!GetWorld())
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);
		RestartPlayer(AIController);
	}
}

UClass* AShootGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
