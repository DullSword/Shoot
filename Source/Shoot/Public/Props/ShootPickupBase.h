// Shoot Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootPickupBase.generated.h"

class USphereComponent;

UCLASS()
class SHOOT_API AShootPickupBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShootPickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float RespawnTime = 5.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	USphereComponent* CollisionComponent;

	virtual bool GivePickupTo(APawn* PlayerPawn);

	void PickupWasTaken() const;
	void Respawn() const;
};
