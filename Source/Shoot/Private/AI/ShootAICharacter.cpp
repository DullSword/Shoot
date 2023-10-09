// Shoot Game. All Rights Reserved.

#include "AI/ShootAICharacter.h"
#include "AI/ShootAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthComponent.h"
#include "UI/ShootHealthBarWidget.h"

AShootAICharacter::AShootAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAIWeaponComponent>(TEXT("WeaponComponent")))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AShootAIController::StaticClass();

	bUseControllerRotationYaw = false;

	const auto MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (!MovementComponent)
	{
		return;
	}
	MovementComponent->bUseControllerDesiredRotation = true;

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComponent"));
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetRelativeLocation(FVector(0, 0, 110));
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AShootAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void AShootAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthWidgetVisibility();
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

void AShootAICharacter::OnHealthChange(float Health, float HealthDelta)
{
	Super::OnHealthChange(Health, HealthDelta);

	if (!HealthComponent || !HealthWidgetComponent)
	{
		return;
	}

	const auto HealthBarWidget = Cast<UShootHealthBarWidget>(HealthWidgetComponent->GetWidget());
	if (!HealthBarWidget)
	{
		return;
	}

	HealthBarWidget->SetHealthProgress(HealthComponent->GetHealthPercent());
}

void AShootAICharacter::UpdateHealthWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
	{
		return;
	}
	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Dist(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}