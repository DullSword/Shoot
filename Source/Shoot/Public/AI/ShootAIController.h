// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShootAIController.generated.h"

class UShootAIPerceptionComponent;
class URespawnComponent;

/**
 *
 */
UCLASS()
class SHOOT_API AShootAIController : public AAIController
{
	GENERATED_BODY()

public:
	AShootAIController();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UShootAIPerceptionComponent* ShootPerceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URespawnComponent* RespawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;

private:
	AActor* GetFocusOnActor() const;
};
