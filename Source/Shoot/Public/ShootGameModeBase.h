// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API AShootGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	int32 GetCurrentRound() const { return CurrentRound; }
	int32 GetRoundCountDown() const { return RoundCountDown; }
	FGameData GetGameData() const { return GameData; }

	void RespawnRequest(AController* Controller);

	FOnMatchStateChangedSignature OnMatchStateChanged;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	void SpawnBots();

	int32 CurrentRound = 0;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;
	void StartRound();
	void GameTimerUpdate();
	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamInfos();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();

	EMatchState MatchState = EMatchState::MS_WaitingToStart;

	void SetMatchState(EMatchState NewMatchState);
};
