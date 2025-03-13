// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarfareLoadoutActor.generated.h"

class AWarfareCharacter;

UCLASS(Abstract, Blueprintable, Notplaceable)
class WARFARE_API AWarfareLoadoutActor : public AActor
{
	GENERATED_BODY()
	
public:
	AWarfareLoadoutActor();

protected:
	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<AWarfareCharacter> CharacterOwner;

public:
	/** Called when this loadout actor has been added to loadout */
	virtual void AddToLoadout(AWarfareCharacter* NewOwner);

	/** Called when this loadout actor has been removed from loadout */
	virtual void RemoveFromLoadout();
};
