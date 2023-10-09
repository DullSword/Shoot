// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShootCharacterBase.h"
#include "ShootAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

/**
 *
 */
UCLASS()
class SHOOT_API AShootAICharacter : public AShootCharacterBase
{
	GENERATED_BODY()

public:
	AShootAICharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealthVisibilityDistance = 1000.f;

	virtual void BeginPlay() override;

	virtual void OnDead() override;
	virtual void OnHealthChange(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};
