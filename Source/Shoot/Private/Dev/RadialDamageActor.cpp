// Shoot Game. All Rights Reserved.

#include "Dev/RadialDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARadialDamageActor::ARadialDamageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ARadialDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARadialDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Color);
	UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}
