// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShootCharacter.h"
#include "ShootAICharacter.generated.h"

class UBehaviorTree;

/**
 *
 */
UCLASS()
class SHOOT_API AShootAICharacter : public AShootCharacter
{
	GENERATED_BODY()

public:
	AShootAICharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDead() override;
};