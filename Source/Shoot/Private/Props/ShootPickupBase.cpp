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

}

// Called every frame
void AShootPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootPickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Destroy();
}

