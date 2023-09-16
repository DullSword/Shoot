// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShootFireCheck.generated.h"

class UWeaponComponent;

/**
 *
 */
UCLASS()
class SHOOT_API UShootFireCheck : public UBTService
{
	GENERATED_BODY()

public:
	UShootFireCheck();

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector InFireRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
