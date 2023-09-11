// Shoot Game. All Rights Reserved.

#include "AI/Tasks/ShootNextLocationTask.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UShootNextLocationTask::UShootNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UShootNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	if (!Controller || !BlackBoardComponent)
	{
		return EBTNodeResult::Type::Failed;
	}

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Type::Failed;
	}

	const auto NavigationSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavigationSys)
	{
		return EBTNodeResult::Type::Failed;
	}

	FNavLocation NavLocation;
	const auto	 Found = NavigationSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation);
	if (!Found)
	{
		return EBTNodeResult::Type::Failed;
	}

	BlackBoardComponent->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Type::Succeeded;
}
