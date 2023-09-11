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
	AShootAICharacter();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
