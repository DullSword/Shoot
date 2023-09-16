// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootFireTask.generated.h"

class UWeaponComponent;

/**
 *
 */
UCLASS()
class SHOOT_API UShootFireTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UShootFireTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:
	UWeaponComponent* GetWeaponComponent(UBehaviorTreeComponent& BTComponent) const;
};
