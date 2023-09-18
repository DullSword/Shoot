// Shoot Game. All Rights Reserved.

#include "AI/Tasks/ShootStopFireTask.h"
#include "AIController.h"
#include "Components/WeaponComponent.h"

UShootStopFireTask::UShootStopFireTask()
{
	NodeName = "Stop Fire";
}

EBTNodeResult::Type UShootStopFireTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto WeaponComponent = GetWeaponComponent(OwnerComp);
	if (!WeaponComponent)
	{
		return EBTNodeResult::Type::Failed;
	}

	WeaponComponent->StopFire();

	return EBTNodeResult::Type::Succeeded;
}

UWeaponComponent* UShootStopFireTask::GetWeaponComponent(UBehaviorTreeComponent& BTComponent) const
{
	const auto AIController = BTComponent.GetAIOwner();
	if (!AIController)
	{
		return nullptr;
	}

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}

	const auto WeaponComponent = Cast<UWeaponComponent>(Pawn->GetComponentByClass(UWeaponComponent::StaticClass()));
	return WeaponComponent;
}
