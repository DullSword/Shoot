// Shoot Game. All Rights Reserved.

#include "AI/ShootAIController.h"
#include "AI/ShootAICharacter.h"
#include "Components/ShootAIPerceptionComponent.h"

AShootAIController::AShootAIController()
{
	ShootPerceptionComponent = CreateDefaultSubobject<UShootAIPerceptionComponent>(TEXT("ShootPerceptionComponent"));
	SetPerceptionComponent(*ShootPerceptionComponent);
}

void AShootAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* ClosestEnemy = ShootPerceptionComponent->GetClosestEnemy();
	SetFocus(ClosestEnemy);
}

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
