// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WarfarePlayerController.generated.h"

class UWarfareInventoryComponent;
class AWarfareInventoryActor;
class AWarfareCharacter;

UCLASS()
class WARFARE_API AWarfarePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWarfarePlayerController();

	virtual void SetPawn(APawn* InPawn) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Player, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWarfareInventoryComponent> PlayerInventoryComponent;

public:
	void GiveInventory(const TArray<TSubclassOf<AWarfareInventoryActor>>& Inventory);

private:
	UPROPERTY()
	TObjectPtr<AWarfareCharacter> WarfareCharacter;
};
