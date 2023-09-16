// Shoot Game. All Rights Reserved.

#include "AI/Services/ShootFireCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/WeaponComponent.h"
#include "Weapon/ShootWeapon.h"

UShootFireCheck::UShootFireCheck()
{
	NodeName = "Fire Check";
}

void UShootFireCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return;
	}
	const auto EnemyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName));
	if (!EnemyActor)
	{
		return;
	}

	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}
	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return;
	}
	const auto WeaponComponent = Cast<UWeaponComponent>(Pawn->GetComponentByClass(UWeaponComponent::StaticClass()));
	if (!WeaponComponent)
	{
		return;
	}
	const auto CurrentWeapon = WeaponComponent->GetCurrentWeapon();
	if (!CurrentWeapon)
	{
		return;
	}

	bool bInFireRange = CurrentWeapon->GetTraceMaxDistance() - FVector::Dist(Pawn->GetActorLocation(), EnemyActor->GetActorLocation()) > 0;
	BlackboardComponent->SetValueAsBool(InFireRangeKey.SelectedKeyName, bInFireRange);

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
