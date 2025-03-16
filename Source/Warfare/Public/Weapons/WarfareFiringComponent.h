// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WarfareFiringComponent.generated.h"

class AWarfarePlayerController;

USTRUCT(BlueprintType)
struct FFiringParameters
{
	GENERATED_USTRUCT_BODY()

	/** Base spread in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing: Accuracy")
	float Spread;

	/** ADS spread modifier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing: Accuracy")
	float ADSSpread;

	/** Firing spread, amount of spread to apply on continuous firing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing: Accuracy")
	float FiringSpread;

	/** Max firing spread, maximum spread amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing: Accuracy")
	float MaxFiringSpread;

	FFiringParameters()
	{
		Spread = 5.0f;
		ADSSpread = 0.25f;
		FiringSpread = 1.0f;
		MaxFiringSpread = 10.0f;
	}
};

USTRUCT(BlueprintType)
struct FHitscanParameters
{
	GENERATED_USTRUCT_BODY()

	/** Maximum range of hitscan tracer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitscan: Stats")
	float HitscanRange;

	/** Damage applied on hitscan hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitscan: Stats")
	float HitscanDamage;

	/** Damage type applied on hitscan hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitscan: Stats")
	TSubclassOf<UDamageType> DamageType;

	/** Client side hit verification, scale for bounding  box of hit actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitscan: Hit Verification")
	float ClientSideHitLeeway;

	/** Threshold for dot product between view direction and hit direction, used for hit verification */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitscan: Hit Verification")
	float AllowedViewDotHitDir;

	FHitscanParameters()
	{
		HitscanRange = 10000.0f;
		HitscanDamage = 10.0f;
		DamageType = UDamageType::StaticClass();
		ClientSideHitLeeway = 200.0f;
		AllowedViewDotHitDir = 0.8f;
	}
};

UCLASS(ClassGroup=(Weapon))
class WARFARE_API UWarfareFiringComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWarfareFiringComponent();

private:
	UPROPERTY()
	TObjectPtr<AWarfarePlayerController> PlayerController;

public:
	virtual void SetPlayerController(AWarfarePlayerController* NewController);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Firing")
	AWarfarePlayerController* GetPlayerController() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing: Stats")
	FFiringParameters FiringParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing: Hitscan")
	FHitscanParameters HitscanParams;

	UPROPERTY(BlueprintReadOnly, Category="Firing: Stats")
	float CurrentFiringSpread;

public:
	UFUNCTION(BlueprintCallable, Category="Firing: Hitscan")
	void FireHitscan();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Firing: Stats")
	float GetCurrentSpread() const;

private:
	UFUNCTION()
	FVector GetAdjustedAim() const;

	UFUNCTION()
	FVector GetFireStartLocation(const FVector& AimDir) const;

	FHitResult FiringTrace(const FVector& StartTrace, const FVector& EndTrace) const;
};
