// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarfareInventoryActor.generated.h"

class AWarfareCharacter;

UCLASS(Abstract, Blueprintable, Notplaceable)
class WARFARE_API AWarfareInventoryActor : public AActor
{
	GENERATED_BODY()
	
public:
	AWarfareInventoryActor();

protected:
	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<AWarfareCharacter> CharacterOwner;

public:
	/** Called when this inventory actor has been added to inventory */
	virtual void AddToInventory(AWarfareCharacter* NewOwner);

	/** Called when this inventory actor has been removed from inventory */
	virtual void RemoveFromInventory();
};
