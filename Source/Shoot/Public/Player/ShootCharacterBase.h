
// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootCharacterBase.generated.h"

class UCharacterMovementComponent;
class UHealthComponent;
class UTextRenderComponent;
class UAnimMontage;
class UWeaponComponent;

UCLASS()
class SHOOT_API AShootCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShootCharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection() const;

	void SetPlayerColor(FLinearColor Color);

protected:
	void OnHealthChange(float Health, float HealthDelta);
	virtual void OnDead();

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

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWeaponComponent* WeaponComponent;
};
