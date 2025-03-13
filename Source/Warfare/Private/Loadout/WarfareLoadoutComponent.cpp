// Fill out your copyright notice in the Description page of Project Settings.

#include "Loadout/WarfareLoadoutComponent.h"
#include "Loadout/WarfareLoadoutActor.h"
#include "Player/WarfareCharacter.h"
#include "Net/UnrealNetwork.h"

UWarfareLoadoutComponent::UWarfareLoadoutComponent()
{
	MaxLoadoutSize = 0;

	SetIsReplicated(true);
}

void UWarfareLoadoutComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UWarfareLoadoutComponent, Loadout, COND_None);
}

void UWarfareLoadoutComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (MaxLoadoutSize > 0)
	{
		Loadout.Reserve(MaxLoadoutSize);
	}
}

AWarfareCharacter* UWarfareLoadoutComponent::GetCharacterOwner() const
{
	return CharacterOwner;
}

void UWarfareLoadoutComponent::SetCharacterOwner(AWarfareCharacter* NewOwner)
{
	CharacterOwner = NewOwner;
}

TArray<AWarfareLoadoutActor*> UWarfareLoadoutComponent::GetLoadout() const
{
	return Loadout;
}

AWarfareLoadoutActor* UWarfareLoadoutComponent::CreateLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass)
{
	AWarfareLoadoutActor* Actor = nullptr;

	if (CharacterOwner != nullptr)
	{
		if (ActorClass != nullptr)
		{
			Actor = GetWorld()->SpawnActor<AWarfareLoadoutActor>(ActorClass);
			if (Actor != nullptr)
			{
				AddLoadoutActor(Actor);
			}
		}

		return Actor;
	}

	return nullptr;
}

void UWarfareLoadoutComponent::AddLoadoutActor(AWarfareLoadoutActor* ActorToAdd)
{
	if (CharacterOwner != nullptr)
	{
		if (ActorToAdd != nullptr)
		{
			ActorToAdd->AddToLoadout(CharacterOwner);
			Loadout.Add(ActorToAdd);
		}
	}
}

void UWarfareLoadoutComponent::RemoveLoadoutActor(AWarfareLoadoutActor* ActorToRemove)
{
	if (ActorToRemove != nullptr)
	{
		ActorToRemove->RemoveFromLoadout();
		Loadout.Remove(ActorToRemove);
	}
}

AWarfareLoadoutActor* UWarfareLoadoutComponent::FindLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass)
{
	for (AWarfareLoadoutActor* Actor : Loadout)
	{
		if (Actor->IsA(ActorClass))
		{
			return Actor;
		}
	}

	return nullptr;
}
