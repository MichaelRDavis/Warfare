// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loadout/WarfareLoadoutActor.h"
#include "WarfareWeapon.generated.h"

class UWarfareFiringComponent;

UENUM(BlueprintType)
enum class EWeaponState : uint8 
{
	Idle,
	Firing,
	Equipping,
	Reloading
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Handgun,
	AssaultRifle
};

UCLASS()
class WARFARE_API AWarfareWeapon : public AWarfareLoadoutActor
{
	GENERATED_BODY()
	
public:
	AWarfareWeapon();

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWarfareFiringComponent> FiringComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadOnly, Category=Weapon)
	EWeaponState CurrentWeaponState;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Weapon)
	EWeaponType GetWeaponType() const;

	virtual void SetWeaponState(EWeaponState NewWeaponState);

	virtual void PrimaryUse();
	virtual void SecondaryUse();
	virtual void UpdateState();
};
