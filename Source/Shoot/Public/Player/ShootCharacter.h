
// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootCharacter.generated.h"

class UCharacterMovementComponent;
class UHealthComponent;
class UTextRenderComponent;
class UAnimMontage;

UCLASS()
class SHOOT_API AShootCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShootCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection() const;

protected:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void Sprint();
	void StopSprint();

	void OnHealthChange(float Health);
	void OnDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dead")
	UAnimMontage* DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dead")
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(600.f, 1200.f);

	UPROPERTY(EditAnywhere, Category = "Damage")
	FVector2D LandedDamage = FVector2D(0.f, 100.f);

	UFUNCTION()
	void TakeFallingDamage(const FHitResult& Hit);

private:
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* HealthTextComponent;
};
