// Shoot Game. All Rights Reserved.

#include "AI/EQS/ShootEnvQueryContext_Enemy.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UShootEnvQueryContext_Enemy::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	if (!QueryOwner)
	{
		return;
	}
	const auto BlackboardComponent = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!BlackboardComponent)
	{
		return;
	}
	const auto EnemyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKeyName));
	if (!EnemyActor)
	{
		return;
	}
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, EnemyActor);
}
