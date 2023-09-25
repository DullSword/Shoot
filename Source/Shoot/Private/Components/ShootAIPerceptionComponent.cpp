// Shoot Game. All Rights Reserved.

#include "Components/ShootAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AIController.h"
#include "Components/HealthComponent.h"
#include "ShootPlayerState.h"

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

	float ClosestDistance = MAX_FLT;
	AActor* ClosestActor = nullptr;

	for (const auto& PerceivedActor : PerceivedActors)
	{
		const auto PerceivePawn = Cast<APawn>(PerceivedActor);
		const auto bIsEnemy = PerceivePawn && IsEnemy(Controller, PerceivePawn->Controller);

		const auto HealthComponent = Cast<UHealthComponent>(PerceivedActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (!HealthComponent || HealthComponent->IsDead() || !bIsEnemy)
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

bool UShootAIPerceptionComponent::IsEnemy(AController* Controller, AController* OtherController) const
{
	if (!Controller || !OtherController || Controller == OtherController)
	{
		return false;
	}

	const auto PlayerState = Cast<AShootPlayerState>(Controller->PlayerState);
	const auto OtherPlayerState = Cast<AShootPlayerState>(OtherController->PlayerState);

	return PlayerState && OtherPlayerState && PlayerState->GetTeamID() != OtherPlayerState->GetTeamID();
}
