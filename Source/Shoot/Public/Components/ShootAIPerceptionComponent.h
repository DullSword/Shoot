// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ShootAIPerceptionComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UShootAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetClosestEnemy() const;

private:
	bool IsEnemy(AController* Controller, AController* OtherController) const;
};
