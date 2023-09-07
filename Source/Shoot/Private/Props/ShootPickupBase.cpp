// Shoot Game. All Rights Reserved.

#include "Props/ShootPickupBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AShootPickupBase::AShootPickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(50.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void AShootPickupBase::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
}

// Called every frame
void AShootPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShootPickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (Pawn && GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

bool AShootPickupBase::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AShootPickupBase::PickupWasTaken() const
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AShootPickupBase::Respawn, RespawnTime);
}

void AShootPickupBase::Respawn() const
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}
