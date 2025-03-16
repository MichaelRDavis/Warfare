// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/WarfarePlayerController.h"
#include "Player/WarfareCharacter.h"
#include "loadout/WarfareLoadoutComponent.h"
#include "Loadout/WarfareLoadoutActor.h"

AWarfarePlayerController::AWarfarePlayerController()
{
	PlayerLoadoutComponent = CreateDefaultSubobject<UWarfareLoadoutComponent>(TEXT("PlayerLoadout"));
	PlayerLoadoutComponent->SetIsReplicated(true);
	PlayerLoadoutComponent->MaxLoadoutSize = 6;
}

void AWarfarePlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);

	WarfareCharacter = Cast<AWarfareCharacter>(InPawn);
	PlayerLoadoutComponent->SetCharacterOwner(WarfareCharacter);
	PlayerLoadoutComponent->SetPlayerController(this);
}

void AWarfarePlayerController::GiveLoadout(const TArray<TSubclassOf<AWarfareLoadoutActor>>& Inventory)
{
	for (TSubclassOf<AWarfareLoadoutActor> ActorClass : Inventory)
	{
		if (ActorClass != nullptr)
		{
			PlayerLoadoutComponent->CreateLoadoutActor(ActorClass);
		}
	}

	PlayerLoadoutComponent->EquipWeapon();
}