// Shoot Game. All Rights Reserved.

#include "AI/Services/ShootFindEnemyService.h"
#include "AIController.h"
#include "Components/ShootAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UShootFindEnemyService::UShootFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UShootFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackBoardComponent)
	{
		return;
	}

	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	const auto AIPerceptionComponent = Cast<UShootAIPerceptionComponent>(AIController->GetComponentByClass(UShootAIPerceptionComponent::StaticClass()));
	if (!AIPerceptionComponent)
	{
		return;
	}

	BlackBoardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName, AIPerceptionComponent->GetClosestEnemy());

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
