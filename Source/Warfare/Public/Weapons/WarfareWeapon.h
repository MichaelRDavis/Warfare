// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loadout/WarfareLoadoutActor.h"
#include "WarfareWeapon.generated.h"

UCLASS()
class WARFARE_API AWarfareWeapon : public AWarfareLoadoutActor
{
	GENERATED_BODY()
	
public:
	AWarfareWeapon();

	virtual void PrimaryUse();
	virtual void SecondaryUse();
};
