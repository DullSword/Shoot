// Shoot Game. All Rights Reserved.

#include "AI/Services/ShootFireService.h"
#include "AIController.h"
#include "Components/WeaponComponent.h"

UShootFireService::UShootFireService()
{
	NodeName = "Fire";
	//bNotifyCeaseRelevant = true;
}

void UShootFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto WeaponComponent = GetWeaponComponent(OwnerComp);
	if (!WeaponComponent)
	{
		return;
	}

	WeaponComponent->StartFire();

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

//void UShootFireService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	const auto WeaponComponent = GetWeaponComponent(OwnerComp);
//	if (!WeaponComponent)
//	{
//		return;
//	}
//
//	WeaponComponent->StopFire();
//}

UWeaponComponent* UShootFireService::GetWeaponComponent(UBehaviorTreeComponent& BTComponent) const
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
