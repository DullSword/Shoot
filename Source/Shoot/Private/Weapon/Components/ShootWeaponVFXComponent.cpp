// Shoot Game. All Rights Reserved.

#include "Weapon/Components/ShootWeaponVFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

UShootWeaponVFXComponent::UShootWeaponVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShootWeaponVFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		if (const auto PhysMaterialPtr = Hit.PhysMaterial.Get(); ImpactDataMap.Contains(PhysMaterialPtr))
		{
			ImpactData = ImpactDataMap[PhysMaterialPtr];
		}
	}

	// Niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ImpactData.NiagaraSystem,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	// decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		ImpactData.DecalData.Material,
		ImpactData.DecalData.Size,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeSpan, ImpactData.DecalData.FadeOutTime);
	}
}
