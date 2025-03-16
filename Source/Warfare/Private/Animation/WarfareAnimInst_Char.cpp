// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WarfareAnimInst_Char.h"
#include "Player/WarfareCharacter.h"
#include "Player/WarfarePlayerController.h"
#include "Loadout/WarfareLoadoutComponent.h"
#include "Weapons/WarfareWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"

UWarfareAnimInst_Char::UWarfareAnimInst_Char()
{
	Speed = 0.0f;
	bIsMoving = false;
	bIsFalling = false;
	bIsCrouched = false;
}

void UWarfareAnimInst_Char::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (TryGetPawnOwner() != nullptr)
	{
		CharacterOwner = Cast<AWarfareCharacter>(TryGetPawnOwner());
		PlayerController = Cast<AWarfarePlayerController>(TryGetPawnOwner()->GetController());
	}
}

void UWarfareAnimInst_Char::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (CharacterOwner != nullptr)
	{
		bIsFalling = CharacterOwner->GetCharacterMovement()->IsFalling();
		Speed = CharacterOwner->GetVelocity().Length();
		if (Speed > 0.0f)
		{
			bIsMoving = true;
		}
		else
		{
			bIsMoving = false;
		}

		bIsCrouched = CharacterOwner->GetCharacterMovement()->IsCrouching();
	}
}

void UWarfareAnimInst_Char::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (PlayerController != nullptr)
	{
		UWarfareLoadoutComponent* Loadout = PlayerController->GetPlayerLoadoutComponent();
		if (Loadout->GetWeapon() != nullptr)
		{
			WeaponType = Loadout->GetWeapon()->GetWeaponType();
		}
	}
}