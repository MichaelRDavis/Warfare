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

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon: Stats")
	float FireRate;
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

public:
	FORCEINLINE UWarfareFiringComponent* GetFiringComponent() const { return FiringComponent; }

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadOnly, Category=Weapon)
	EWeaponState CurrentWeaponState;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Weapon)
	EWeaponType GetWeaponType() const;

	virtual void SetWeaponState(EWeaponState NewWeaponState);

	// AWarfareLoadoutActor interface
	virtual void PrimaryUse();
	virtual void SecondaryUse();
	virtual void UpdateState();
	// End of AWarfareLoadoutActor interface

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	FWeaponStats WeaponStats;

	UPROPERTY()
	float FireInterval;

	UPROPERTY()
	float LastFireTime;

	UPROPERTY()
	bool bWantsToFire;

	UPROPERTY()
	bool bIsFiring;

private:
	FTimerHandle FiringTimer;

public:
	/** Weapon specific fire implementation */
	UFUNCTION(BlueprintCallable, Category=Weapon)
	virtual void Fire();

	/** Start weapon fire */
	UFUNCTION(BlueprintCallable, Category=Weapon)
	virtual void StartFire();

	/** Stop weapon fire */
	UFUNCTION(BlueprintCallable, Category=Weapon)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category=Weapon)
	virtual void BeginFiring();

	UFUNCTION(BlueprintCallable, Category=Weapon)
	virtual void EndFiring();

	/** Check if weapon can fire */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Weapon)
	bool CanFire() const;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();
	void ServerFire_Implementation();
	bool ServerFire_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartFire();
	void ServerStartFire_Implementation();
	bool ServerStartFire_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStopFire();	
	void ServerStopFire_Implementation();
	bool ServerStopFire_Validate();
};
