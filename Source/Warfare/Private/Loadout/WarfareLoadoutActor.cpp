// Fill out your copyright notice in the Description page of Project Settings.

#include "Loadout/WarfareLoadoutActor.h"
#include "Player/WarfareCharacter.h"

AWarfareLoadoutActor::AWarfareLoadoutActor()
{
	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

void AWarfareLoadoutActor::AddToLoadout(AWarfareCharacter* NewOwner)
{
	SetInstigator(NewOwner);
	SetOwner(NewOwner);
	CharacterOwner = NewOwner;
	PrimaryActorTick.AddPrerequisite(CharacterOwner, CharacterOwner->PrimaryActorTick);
}

void AWarfareLoadoutActor::RemoveFromLoadout()
{
	if (CharacterOwner != nullptr)
	{
		PrimaryActorTick.RemovePrerequisite(CharacterOwner, CharacterOwner->PrimaryActorTick);
	}

	SetInstigator(nullptr);
	SetOwner(nullptr);
	CharacterOwner = nullptr;
}