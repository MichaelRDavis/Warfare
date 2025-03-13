// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/WarfareCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AWarfareCharacter::AWarfareCharacter()
{
	// Create a CammeraComponent
	FirstPersonCameraCommponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraCommponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraCommponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	FirstPersonCameraCommponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this character)
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterArmsMesh1P"));;
	ArmsMesh->SetupAttachment(FirstPersonCameraCommponent);
	ArmsMesh->SetOnlyOwnerSee(true);
	ArmsMesh->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	ArmsMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	ArmsMesh->bReceivesDecals = false;
	ArmsMesh->PrimaryComponentTick.AddPrerequisite(this, PrimaryActorTick);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bEnablePhysicsOnDedicatedServer = true;
	GetMesh()->bReceivesDecals = false;

	SetMinNetUpdateFrequency(100.0f);
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWarfareCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void AWarfareCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWarfareCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWarfareCharacter::Look);
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AWarfareCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AWarfareCharacter::StopJumping);
	}
}

void AWarfareCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add movement
		MoveForward(MovementVector.Y);
		MoveRight(MovementVector.X);
	}
}

void AWarfareCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWarfareCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator Rotation = GetControlRotation();
		FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in forward direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}

void AWarfareCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is right
		const FRotator Rotation = GetControlRotation();
		FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in right direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}
