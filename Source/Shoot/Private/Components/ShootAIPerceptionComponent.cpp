// Shoot Game. All Rights Reserved.

#include "Components/ShootAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

AActor* UShootAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

	if (PerceivedActors.Num() == 0)
	{
		return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller)
	{
		return nullptr;
	}
	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}

	float	ClosestDistance = MAX_FLT;
	AActor* ClosestActor = nullptr;

	for (const auto& PerceivedActor : PerceivedActors)
	{
		const auto HealthComponent = Cast<UHealthComponent>(PerceivedActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (!HealthComponent || HealthComponent->IsDead())
		{
			continue;
		}

		const auto CurrentDistance = FVector::Dist(Pawn->GetActorLocation(), PerceivedActor->GetActorLocation());
		if (CurrentDistance < ClosestDistance)
		{
			ClosestDistance = CurrentDistance;
			ClosestActor = PerceivedActor;
		}
	}

	return ClosestActor;
}
