// Shoot Game. All Rights Reserved.

#include "Components/WeaponComponent.h"
#include "Weapon/ShootWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/EquipFinishedAnimNotify.h"
#include "Animations/ReloadFinishedAnimNotify.h"

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

	CurrentWeaponIndex = 0;
	InitAnimations();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto weapon : Weapons)
	{
		weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		weapon->Destroy();
	}

	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())
	{
		return;
	}

	for (auto& WeaponData : WeaponDatas)
	{
		auto Weapon = GetWorld()->SpawnActor<AShootWeapon>(WeaponData.WeaponClass);
		if (!Weapon)
		{
			continue;
		}

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UWeaponComponent::AttachWeaponToSocket(AShootWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent)
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character)
	{
		return;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

	EquipAnimInProcess = true;
	PlayAnimMontage(EquipAnimMontage);

	const auto& CurrentWeaponData = WeaponDatas.FindByPredicate([&](const FWeaponData& Data) {
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
}

void UWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}
	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->StopFire();
}

void UWeaponComponent::NextWeapon()
{
	if (!CanEquip())
	{
		return;
	}
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::Reload()
{
	if (!CanReload())
	{
		return;
	}
	ReloadAnimInProcess = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character || !AnimMontage)
	{
		return;
	}

	Character->PlayAnimMontage(AnimMontage);
}

void UWeaponComponent::InitAnimations()
{
	const auto EquipFinishedNotify = FindFirstNotifyByClass<UEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
	}

	for (const auto& WeaponData : WeaponDatas)
	{
		const auto ReloadFinishedNotify = FindFirstNotifyByClass<UReloadFinishedAnimNotify>(WeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			continue;
		}
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
	}
}

bool UWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProcess && !ReloadAnimInProcess;
}

bool UWeaponComponent::CanEquip() const
{
	return !EquipAnimInProcess && !ReloadAnimInProcess;
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character || Character->GetMesh() != MeshComponent)
	{
		return;
	}

	EquipAnimInProcess = false;
}

bool UWeaponComponent::CanReload() const
{
	return CurrentWeapon && !ReloadAnimInProcess && !EquipAnimInProcess;
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character || Character->GetMesh() != MeshComponent)
	{
		return;
	}

	ReloadAnimInProcess = false;
}
