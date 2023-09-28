// Shoot Game. All Rights Reserved.

#include "Player/ShootPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AShootPlayerCharacter::AShootPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AShootPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AShootPlayerCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AShootPlayerCharacter::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AShootPlayerCharacter::Jump);
		PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AShootPlayerCharacter::Sprint);
		PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AShootPlayerCharacter::StopSprint);

		check(WeaponComponent);
		PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
		PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
		PlayerInputComponent->BindAction("NextWeapon", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
		PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
	}
}

void AShootPlayerCharacter::MoveForward(float Amount)
{
	if (Amount == 0.f)
	{
		return;
	}
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShootPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.f)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShootPlayerCharacter::Sprint()
{
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = 900.f;
	}
}

void AShootPlayerCharacter::StopSprint()
{
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = 600.f;
	}
}

void AShootPlayerCharacter::OnDead()
{
	Super::OnDead();

	if (auto CharacterController = Cast<APlayerController>(Controller); CharacterController)
	{
		CharacterController->ChangeState(NAME_Spectating);
	}
}