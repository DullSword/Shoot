// Shoot Game. All Rights Reserved.

#include "AI/ShootAIController.h"
#include "AI/ShootAICharacter.h"
#include "Components/ShootAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/RespawnComponent.h"

AShootAIController::AShootAIController()
{
	ShootPerceptionComponent = CreateDefaultSubobject<UShootAIPerceptionComponent>(TEXT("ShootPerceptionComponent"));
	SetPerceptionComponent(*ShootPerceptionComponent);

	bWantsPlayerState = true; //生成PlayerState，为了ShootGameModeBase里ResetOnePlayer的Pawn的Reset能有效执行

	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));
}

void AShootAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

void AShootAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AShootAICharacter>(InPawn);
	if (!AICharacter)
	{
		return;
	}

	RunBehaviorTree(AICharacter->BehaviorTreeAsset);
}

AActor* AShootAIController::GetFocusOnActor() const
{
	const auto BlackBoardComponent = GetBlackboardComponent();
	if (!BlackBoardComponent)
	{
		return nullptr;
	}
	return Cast<AActor>(BlackBoardComponent->GetValueAsObject(FocusOnKeyName));
}
