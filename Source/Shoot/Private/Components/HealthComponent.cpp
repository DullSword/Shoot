// Shoot Game. All Rights Reserved.

#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "ShootGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		// ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UHealthComponent::OnTakeRadialDamage);
	}
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Display, TEXT("AnyDamage: %f"), Damage);
}

void UHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	const float FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	//UE_LOG(LogTemp, Display, TEXT("PointDamage: %f, FinalDamge: %f, BoneName: %s"), Damage, FinalDamage, *BoneName.ToString());
	ApplyDamage(FinalDamage, InstigatedBy);
}

void UHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Display, TEXT("RadialDamage: %f"), Damage);
	ApplyDamage(Damage, InstigatedBy);
}

void UHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	/*if (DamageType)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageType: %s"), *DamageType->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);*/

	if (Damage <= 0.f || IsDead())
	{
		return;
	}

	if (auto World = GetWorld(); World)
	{
		World->GetTimerManager().ClearTimer(HealTimer);
	}

	SetHealth(Health - Damage);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDead.Broadcast();
	}
	else if (auto World = GetWorld(); World && AutoHeal)
	{
		World->GetTimerManager().SetTimer(HealTimer, this, &UHealthComponent::Heal, HealRate, true, HealFirstDelay);
	}

	StartCameraShake();
}

float UHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName))
	{
		return 1.f;
	}

	const auto PhysicalMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!PhysicalMaterial || !DamageModifiers.Contains(PhysicalMaterial))
	{
		return 1.f;
	}

	return DamageModifiers[PhysicalMaterial];
}

void UHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChange.Broadcast(Health, HealthDelta);
}

void UHealthComponent::Heal()
{
	SetHealth(Health + HealAmount);

	if (auto World = GetWorld(); World && IsHealthFull())
	{
		World->GetTimerManager().ClearTimer(HealTimer);
	}
}

bool UHealthComponent::TryToAddHealth(float HealingAmount)
{
	if (IsDead() || IsHealthFull())
	{
		return false;
	}

	SetHealth(Health + HealingAmount);
	return true;
}

void UHealthComponent::StartCameraShake()
{
	if (IsDead())
	{
		return;
	}

	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return;
	}

	const auto Controller = Pawn->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager)
	{
		return;
	}

	Controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);
}

void UHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld())
	{
		return;
	}

	const auto GameMode = Cast<AShootGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}

	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return;
	}

	GameMode->Killed(KillerController, Pawn->GetController());
}