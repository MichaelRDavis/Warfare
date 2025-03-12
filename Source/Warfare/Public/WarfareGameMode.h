// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WarfareGameMode.generated.h"

class AWarfareInventoryActor;

UCLASS()
class WARFARE_API AWarfareGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AWarfareGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category=Classes)
	TArray<TSubclassOf<AWarfareInventoryActor>> DefaultInventory;

	virtual void SetPlayerDefaults(APawn* PlayerPawn) override;
};
