// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShootFindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class SHOOT_API UShootFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UShootFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
