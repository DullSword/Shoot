// Shoot Game. All Rights Reserved.

#include "Player/ShootCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/ShootWeapon.h"

// Sets default values
AShootCharacterBase::AShootCharacterBase(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextComponent"));
	HealthTextComponent->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
}

// Called when the game starts or when spawned
void AShootCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());

	check(CharacterMovementComponent);
	check(HealthTextComponent);
	check(HealthComponent);
	check(GetMesh());

	OnHealthChange(HealthComponent->GetHealth(), 0.f);
	HealthComponent->OnHealthChange.AddUObject(this, &AShootCharacterBase::OnHealthChange);
	HealthComponent->OnDead.AddUObject(this, &AShootCharacterBase::OnDead);

	LandedDelegate.AddDynamic(this, &AShootCharacterBase::TakeFallingDamage);
}

// Called every frame
void AShootCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AShootCharacterBase::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
	{
		return 0.f;
	}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto Angle = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto Degress = FMath::RadiansToDegrees(Angle);
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return CrossProduct.IsZero() ? Degress : Degress * FMath::Sign(CrossProduct.Z);
}

void AShootCharacterBase::SetPlayerColor(FLinearColor Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst)
	{
		return;
	}

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void AShootCharacterBase::OnHealthChange(float Health, float HealthDelta)
{
	//HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void AShootCharacterBase::OnDead()
{
	CharacterMovementComponent->DisableMovement();
	// PlayAnimMontage(DeadMontage);
	SetLifeSpan(LifeSpan);
	if (auto CharacterCapsuleComponent = GetCapsuleComponent(); CharacterCapsuleComponent)
	{
		CharacterCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}

	WeaponComponent->StopFire();
	WeaponComponent->SetZoom(false);

	// Ragdoll
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void AShootCharacterBase::TakeFallingDamage(const FHitResult& Hit)
{
	const auto FallingVelocity = -GetVelocity().Z;
	UE_LOG(LogTemp, Warning, TEXT("falling velocity :%f"), FallingVelocity);
	const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallingVelocity);
	TakeDamage(FallDamage, FPointDamageEvent{}, nullptr, nullptr);
}
