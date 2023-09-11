// Shoot Game. All Rights Reserved.

#include "AI/ShootAICharacter.h"
#include "AI/ShootAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AShootAICharacter::AShootAICharacter()
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
