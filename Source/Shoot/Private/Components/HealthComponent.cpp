// Shoot Game. All Rights Reserved.

#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"

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
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
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
		OnDead.Broadcast();
	}
	else if (auto World = GetWorld(); World && AutoHeal)
	{
		World->GetTimerManager().SetTimer(HealTimer, this, &UHealthComponent::Heal, HealRate, true, HealFirstDelay);
	}
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	OnHealthChange.Broadcast(Health);
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
