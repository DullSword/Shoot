// Shoot Game. All Rights Reserved.

#include "AI/Tasks/ShootFireTask.h"
#include "AIController.h"
#include "Components/WeaponComponent.h"

UShootFireTask::UShootFireTask()
{
	NodeName = "Fire";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UShootFireTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto WeaponComponent = GetWeaponComponent(OwnerComp);
	if (!WeaponComponent)
	{
		return EBTNodeResult::Type::Failed;
	}

	WeaponComponent->StartFire();

	return EBTNodeResult::Type::Succeeded;
}

void UShootFireTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	const auto WeaponComponent = GetWeaponComponent(OwnerComp);
	if (!WeaponComponent)
	{
		return;
	}

	WeaponComponent->StopFire();
}

UWeaponComponent* UShootFireTask::GetWeaponComponent(UBehaviorTreeComponent& BTComponent) const
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
