// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootStopFireTask.generated.h"

class UWeaponComponent;

/**
 * 
 */
UCLASS()
class SHOOT_API UShootStopFireTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UShootStopFireTask();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UWeaponComponent* GetWeaponComponent(UBehaviorTreeComponent& BTComponent) const;
};
