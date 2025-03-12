// Fill out your copyright notice in the Description page of Project Settings.

#include "WarfareInventoryComponent.h"
#include "WarfareInventoryActor.h"
#include "WarfareCharacter.h"
#include "Net/UnrealNetwork.h"

UWarfareInventoryComponent::UWarfareInventoryComponent()
{
	MaxInventorySize = 0;

	SetIsReplicated(true);
}

void UWarfareInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UWarfareInventoryComponent, Inventory, COND_None);
}

void UWarfareInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (MaxInventorySize > 0)
	{
		Inventory.Reserve(MaxInventorySize);
	}
}

AWarfareCharacter* UWarfareInventoryComponent::GetCharacterOwner() const
{
	return CharacterOwner;
}

void UWarfareInventoryComponent::SetCharacterOwner(AWarfareCharacter* NewOwner)
{
	CharacterOwner = NewOwner;
}

TArray<AWarfareInventoryActor*> UWarfareInventoryComponent::GetInventory() const
{
	return Inventory;
}

AWarfareInventoryActor* UWarfareInventoryComponent::CreateInventoryActor(TSubclassOf<AWarfareInventoryActor> ActorClass)
{
	AWarfareInventoryActor* Actor = nullptr;

	if (CharacterOwner != nullptr)
	{
		if (ActorClass != nullptr)
		{
			Actor = GetWorld()->SpawnActor<AWarfareInventoryActor>(ActorClass);
			if (Actor != nullptr)
			{
				AddInventoryActor(Actor);
			}
		}

		return Actor;
	}

	return nullptr;
}

void UWarfareInventoryComponent::AddInventoryActor(AWarfareInventoryActor* ActorToAdd)
{
	if (CharacterOwner != nullptr)
	{
		if (ActorToAdd != nullptr)
		{
			ActorToAdd->AddToInventory(CharacterOwner);
			Inventory.Add(ActorToAdd);
		}
	}
}

void UWarfareInventoryComponent::RemoveInventoryActor(AWarfareInventoryActor* ActorToRemove)
{
	if (ActorToRemove != nullptr)
	{
		ActorToRemove->RemoveFromInventory();
		Inventory.Remove(ActorToRemove);
	}
}

AWarfareInventoryActor* UWarfareInventoryComponent::FindInventoryActor(TSubclassOf<AWarfareInventoryActor> ActorClass)
{
	for (AWarfareInventoryActor* Actor : Inventory)
	{
		if (Actor->IsA(ActorClass))
		{
			return Actor;
		}
	}

	return nullptr;
}
