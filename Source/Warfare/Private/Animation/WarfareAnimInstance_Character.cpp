// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WarfareAnimInstance_Character.h"
#include "Player/WarfareCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UWarfareAnimInstance_Character::UWarfareAnimInstance_Character()
{
	
}

void UWarfareAnimInstance_Character::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (TryGetPawnOwner() != nullptr)
	{
		CharacterOwner = Cast<AWarfareCharacter>(TryGetPawnOwner());
	}
}

void UWarfareAnimInstance_Character::NativeUpdateAnimation(float DeltaTimeX)
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
