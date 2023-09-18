// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "ShootEnvQueryContext_Enemy.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UShootEnvQueryContext_Enemy : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;

protected:
	FName EnemyActorKeyName = "EnemyActor";
};
