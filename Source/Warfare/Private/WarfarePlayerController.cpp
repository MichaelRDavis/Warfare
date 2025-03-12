// Fill out your copyright notice in the Description page of Project Settings.

#include "WarfarePlayerController.h"
#include "WarfareCharacter.h"
#include "WarfareInventoryComponent.h"
#include "WarfareInventoryActor.h"

AWarfarePlayerController::AWarfarePlayerController()
{
	PlayerInventoryComponent = CreateDefaultSubobject<UWarfareInventoryComponent>(TEXT("PlayerInventory"));
}

void AWarfarePlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);

	WarfareCharacter = Cast<AWarfareCharacter>(InPawn);
	PlayerInventoryComponent->SetCharacterOwner(WarfareCharacter);
}

void AWarfarePlayerController::GiveInventory(const TArray<TSubclassOf<AWarfareInventoryActor>>& Inventory)
{
	for (TSubclassOf<AWarfareInventoryActor> ActorClass : Inventory)
	{
		if (ActorClass != nullptr)
		{
			PlayerInventoryComponent->CreateInventoryActor(ActorClass);
		}
	}
}