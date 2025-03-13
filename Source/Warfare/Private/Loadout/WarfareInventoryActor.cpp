// Fill out your copyright notice in the Description page of Project Settings.

#include "Loadout/WarfareInventoryActor.h"
#include "Player/WarfareCharacter.h"

AWarfareInventoryActor::AWarfareInventoryActor()
{
	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

void AWarfareInventoryActor::AddToInventory(AWarfareCharacter* NewOwner)
{
	SetInstigator(NewOwner);
	SetOwner(NewOwner);
	CharacterOwner = NewOwner;
	PrimaryActorTick.AddPrerequisite(CharacterOwner, CharacterOwner->PrimaryActorTick);
}

void AWarfareInventoryActor::RemoveFromInventory()
{
	if (CharacterOwner != nullptr)
	{
		PrimaryActorTick.RemovePrerequisite(CharacterOwner, CharacterOwner->PrimaryActorTick);
	}

	SetInstigator(nullptr);
	SetOwner(nullptr);
	CharacterOwner = nullptr;
}