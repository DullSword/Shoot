// Shoot Game. All Rights Reserved.

#include "Props/ShootPickupBase.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

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

	GenerateRotationYaw();
}

// Called every frame
void AShootPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

	for (const auto OverlapPawn : OverlappingPawns)
	{
		if (GivePickupTo(OverlapPawn))
		{
			PickupWasTaken();
			break;
		}
	}
}

void AShootPickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (Pawn)
	{
		if (GivePickupTo(Pawn))
		{
			PickupWasTaken();
		}
		else
		{
			OverlappingPawns.Add(Pawn);
		}
	}
}

void AShootPickupBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (Pawn)
	{
		OverlappingPawns.Remove(Pawn);
	}
}

bool AShootPickupBase::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AShootPickupBase::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AShootPickupBase::Respawn, RespawnTime);
	UGameplayStatics::PlaySoundAtLocation(this, PickupTakenSound, GetActorLocation());
}

void AShootPickupBase::Respawn()
{
	GenerateRotationYaw();

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}

	FTimerHandle ResumeCollisionResponseTimerHandle;
	GetWorldTimerManager().SetTimer(
		ResumeCollisionResponseTimerHandle,
		[this]() {
			CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		},
		.3f,
		false);
}

void AShootPickupBase::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.f : -1.f;
	RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}

bool AShootPickupBase::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}
