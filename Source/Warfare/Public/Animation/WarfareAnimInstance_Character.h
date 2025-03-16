// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WarfareAnimInstance_Character.generated.h"

class AWarfareCharacter;
class AWarfarePlayerController;
class AWarfareWeapon;
enum class EWeaponType : uint8;

UCLASS()
class WARFARE_API UWarfareAnimInstance_Character : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UWarfareAnimInstance_Character();

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AWarfareCharacter> CharacterOwner;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AWarfarePlayerController> PlayerController;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Animation: Movement")
	bool bIsMoving;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Animation: Movement")
	bool bIsFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Animation: Movement")
	bool bIsCrouched;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Animation: Movement")
	float Speed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Animation: Weapon")
	EWeaponType WeaponType;
};
