// Shoot Game. All Rights Reserved.

#include "AI/ShootAICharacter.h"
#include "AI/ShootAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AIWeaponComponent.h"
#include "BrainComponent.h"

AShootAICharacter::AShootAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAIWeaponComponent>(TEXT("WeaponComponent")))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AShootAIController::StaticClass();

	bUseControllerRotationYaw = false;

	const auto MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (!MovementComponent)
	{
		return;
	}
	MovementComponent->bUseControllerDesiredRotation = true;
}

void AShootAICharacter::OnDead()
{
	Super::OnDead();

	const auto AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		return;
	}

	const auto BrainComponent = AIController->GetBrainComponent();
	if (!BrainComponent)
	{
		return;
	}

	BrainComponent->Cleanup();
}
