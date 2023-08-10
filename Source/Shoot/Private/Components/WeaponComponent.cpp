// Shoot Game. All Rights Reserved.

#include "Components/WeaponComponent.h"
#include "Weapon/ShootWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	if (!GetWorld())
	{
		return;
	}

	CurrentWeapon = GetWorld()->SpawnActor<AShootWeapon>(WeaponClass);

	if (!CurrentWeapon)
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachSocketName);

	CurrentWeapon->SetOwner(Character);
}

void UWeaponComponent::Fire()
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->Fire();
}