// Shoot Game. All Rights Reserved.

#include "AI/ShootAIController.h"
#include "AI/ShootAICharacter.h"

void AShootAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AShootAICharacter>(InPawn);
	if (!AICharacter)
	{
		return;
	}

	RunBehaviorTree(AICharacter->BehaviorTreeAsset);
}
