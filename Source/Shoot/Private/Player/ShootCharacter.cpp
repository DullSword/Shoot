// Shoot Game. All Rights Reserved.

#include "Player/ShootCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShootCharacter::AShootCharacter()
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
void AShootCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());

	check(CharacterMovementComponent);
	check(HealthTextComponent);
	check(HealthComponent);

	OnHealthChange(HealthComponent->GetHealth());
	HealthComponent->OnHealthChange.AddUObject(this, &AShootCharacter::OnHealthChange);
	HealthComponent->OnDead.AddUObject(this, &AShootCharacter::OnDead);

	LandedDelegate.AddDynamic(this, &AShootCharacter::TakeFallingDamage);
}

// Called every frame
void AShootCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShootCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AShootCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AShootCharacter::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AShootCharacter::Sprint);
		PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AShootCharacter::StopSprint);

		check(WeaponComponent);
		PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
		PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
		PlayerInputComponent->BindAction("NextWeapon", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
		PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
	}
}

void AShootCharacter::MoveForward(float Amount)
{
	if (Amount == 0.f)
	{
		return;
	}
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShootCharacter::MoveRight(float Amount)
{
	if (Amount == 0.f)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), Amount);
}

float AShootCharacter::GetMovementDirection() const
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

void AShootCharacter::Sprint()
{
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = 900.f;
	}
}

void AShootCharacter::StopSprint()
{
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = 600.f;
	}
}

void AShootCharacter::OnHealthChange(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void AShootCharacter::OnDead()
{
	CharacterMovementComponent->DisableMovement();
	PlayAnimMontage(DeadMontage);
	SetLifeSpan(LifeSpan);
	if (auto CharacterCapsuleComponent = GetCapsuleComponent(); CharacterCapsuleComponent)
	{
		CharacterCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}

	if (auto CharacterController = Cast<APlayerController>(Controller); CharacterController)
	{
		CharacterController->ChangeState(NAME_Spectating);
	}

	WeaponComponent->StopFire();
}

void AShootCharacter::TakeFallingDamage(const FHitResult& Hit)
{
	const auto FallingVelocity = -GetVelocity().Z;
	UE_LOG(LogTemp, Warning, TEXT("falling velocity :%f"), FallingVelocity);
	const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallingVelocity);
	TakeDamage(FallDamage, FDamageEvent{}, nullptr, nullptr);
}
