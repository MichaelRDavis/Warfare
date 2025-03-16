// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/WarfarePlayerController.h"
#include "Player/WarfareCharacter.h"
#include "loadout/WarfareLoadoutComponent.h"
#include "Loadout/WarfareLoadoutActor.h"
#include "Weapons/WarfareWeapon.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AWarfarePlayerController::AWarfarePlayerController()
{
	PlayerLoadoutComponent = CreateDefaultSubobject<UWarfareLoadoutComponent>(TEXT("PlayerLoadout"));
	PlayerLoadoutComponent->SetIsReplicated(true);
	PlayerLoadoutComponent->MaxLoadoutSize = 6;
}

void AWarfarePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}
}

void AWarfarePlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);

	WarfareCharacter = Cast<AWarfareCharacter>(InPawn);
	PlayerLoadoutComponent->SetCharacterOwner(WarfareCharacter);
	PlayerLoadoutComponent->SetPlayerController(this);
	PlayerLoadoutComponent->InitLoadout();
}

void AWarfarePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWarfarePlayerController::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWarfarePlayerController::Look);
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AWarfarePlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AWarfarePlayerController::StopJumping);
		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWarfarePlayerController::OnStartFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AWarfarePlayerController::OnStopFire);
	}
}

void AWarfarePlayerController::GiveLoadout(const TArray<TSubclassOf<AWarfareLoadoutActor>>& Inventory)
{
	for (TSubclassOf<AWarfareLoadoutActor> ActorClass : Inventory)
	{
		if (ActorClass != nullptr)
		{
			PlayerLoadoutComponent->CreateLoadoutActor(ActorClass);
		}
	}

	PlayerLoadoutComponent->EquipWeapon();
}

void AWarfarePlayerController::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (WarfareCharacter != nullptr)
	{
		// Add movement
		WarfareCharacter->MoveForward(MovementVector.Y);
		WarfareCharacter->MoveRight(MovementVector.X);
	}
}

void AWarfarePlayerController::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AWarfarePlayerController::Jump()
{
	if (WarfareCharacter != nullptr)
	{
		WarfareCharacter->Jump();
	}
}

void AWarfarePlayerController::StopJumping()
{
	if (WarfareCharacter != nullptr)
	{
		WarfareCharacter->StopJumping();
	}
}

void AWarfarePlayerController::OnStartFire()
{
	if (PlayerLoadoutComponent->GetWeapon() != nullptr)
	{
		PlayerLoadoutComponent->GetWeapon()->StartFire();
	}
}

void AWarfarePlayerController::OnStopFire()
{
	if (PlayerLoadoutComponent->GetWeapon() != nullptr)
	{
		PlayerLoadoutComponent->GetWeapon()->StopFire();
	}
}