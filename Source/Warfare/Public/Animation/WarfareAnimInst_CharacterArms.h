// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/WarfareAnimInstance_Character.h"
#include "WarfareAnimInst_CharacterArms.generated.h"

class AWarfareWeapon;

UENUM(BlueprintType)
enum class EWeaponAnimType : uint8
{
	Handgun,
	AssaultRifle
};

UCLASS()
class WARFARE_API UWarfareAnimInst_CharacterArms : public UWarfareAnimInstance_Character
{
	GENERATED_BODY()
	
public:
	typedef UWarfareAnimInstance_Character Super;

	UWarfareAnimInst_CharacterArms();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation: Weapon")
	TObjectPtr<AWarfareWeapon> Weapon;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Animation: Weapon")
	EWeaponAnimType WeaponAnimType;
};
