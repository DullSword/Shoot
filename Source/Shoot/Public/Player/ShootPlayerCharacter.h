
// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOT_API AShootPlayerCharacter : public AShootCharacterBase
{
	GENERATED_BODY()

public:
	AShootPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void Sprint();
	void StopSprint();

	virtual void OnDead() override;
};
