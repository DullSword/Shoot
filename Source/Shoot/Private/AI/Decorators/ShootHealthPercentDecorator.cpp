// Shoot Game. All Rights Reserved.

#include "AI/Decorators/ShootHealthPercentDecorator.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

bool UShootHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return false;
	}

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return false;
	}

	const auto HealthComponent = Cast<UHealthComponent>(Pawn->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent && HealthComponent->IsDead())
	{
		return false;
	}

	return HealthComponent->GetHealthPercent() <= MinHealthPercent;
}