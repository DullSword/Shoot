// Shoot Game. All Rights Reserved.

#include "Player/ShootPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

AShootPlayerCharacter::AShootPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CameraCollisionComponent"));
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CameraCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AShootPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent)

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AShootPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AShootPlayerCharacter::OnCameraCollisionEndOverlap);
}

void AShootPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void AShootPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void AShootPlayerCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());

	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for (const auto& MeshChild : MeshChildren)
	{
		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
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

		/*DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
		PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &UWeaponComponent::Zoom, true);
		PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &UWeaponComponent::Zoom, false);*/
		PlayerInputComponent->BindAction("Zoom", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::Zoom);
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
