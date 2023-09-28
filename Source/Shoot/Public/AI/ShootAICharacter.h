// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShootCharacterBase.h"
#include "ShootAICharacter.generated.h"

class UBehaviorTree;

/**
 *
 */
UCLASS()
class SHOOT_API AShootAICharacter : public AShootCharacterBase
{
	GENERATED_BODY()

public:
	AShootAICharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDead() override;
};
