// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShootFireService.generated.h"

class UWeaponComponent;

/**
 *
 */
UCLASS()
class SHOOT_API UShootFireService : public UBTService
{
	GENERATED_BODY()

public:
	UShootFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UWeaponComponent* GetWeaponComponent(UBehaviorTreeComponent& BTComponent) const;
};
