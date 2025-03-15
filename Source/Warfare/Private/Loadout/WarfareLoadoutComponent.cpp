// Fill out your copyright notice in the Description page of Project Settings.

#include "Loadout/WarfareLoadoutComponent.h"
#include "Loadout/WarfareLoadoutActor.h"
#include "Player/WarfareCharacter.h"
#include "Weapons/WarfareWeapon.h"
#include "Net/UnrealNetwork.h"

UWarfareLoadoutComponent::UWarfareLoadoutComponent()
{
	MaxLoadoutSize = 0;
}

void UWarfareLoadoutComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UWarfareLoadoutComponent, Loadout, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWarfareLoadoutComponent, Weapon, COND_Custom);
}

void UWarfareLoadoutComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (MaxLoadoutSize > 0)
	{
		Loadout.Reserve(MaxLoadoutSize);
	}
}

void UWarfareLoadoutComponent::BeginPlay()
{
	Super::BeginPlay();
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
	if (CharacterOwner->GetLocalRole() < ROLE_Authority)
	{
		return nullptr;
	}

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
	if (Loadout.Num() >= MaxLoadoutSize)
	{
		return;
	}

	if (CharacterOwner != nullptr && CharacterOwner->GetLocalRole() == ROLE_Authority)
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
	if (ActorToRemove != nullptr && CharacterOwner->GetLocalRole() == ROLE_Authority)
	{
		ActorToRemove->RemoveFromLoadout();
		Loadout.Remove(ActorToRemove);
	}
}

AWarfareLoadoutActor* UWarfareLoadoutComponent::FindLoadoutActorByClass(TSubclassOf<AWarfareLoadoutActor> ActorClass)
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

bool UWarfareLoadoutComponent::FindLoadoutActor(TSubclassOf<AWarfareLoadoutActor> ActorClass)
{
	for (AWarfareLoadoutActor* Actor : Loadout)
	{
		if (Actor->IsA(ActorClass))
		{
			return true;
		}
	}

	return false;
}

void UWarfareLoadoutComponent::DestroyLoadout()
{
	if (CharacterOwner->GetLocalRole() < ROLE_Authority)
	{
		return;
	}

	for (AWarfareLoadoutActor* Actor : Loadout)
	{
		if (Actor)
		{
			RemoveLoadoutActor(Actor);
			Actor->Destroy();
		}
	}
}

void UWarfareLoadoutComponent::SwitchWeapon(AWarfareWeapon* NewWeapon, AWarfareWeapon* LastWeapon /*= nullptr*/)
{
	AWarfareWeapon* LocalLastWeapon = nullptr;

	if (LastWeapon != nullptr)
	{
		LocalLastWeapon = nullptr;
	}
	else if (NewWeapon != Weapon)
	{
		LocalLastWeapon = Weapon;
	}

	// Unequip previous weapon
	if (LocalLastWeapon)
	{
		LocalLastWeapon->OnUnEquip();
	}

	Weapon = NewWeapon;

	// Equip new weapon
	if (NewWeapon)
	{
		NewWeapon->AddToLoadout(CharacterOwner);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void UWarfareLoadoutComponent::ServerSwitchWeapon_Implementation(AWarfareWeapon* NewWeapon)
{
	if (NewWeapon)
	{
		if (CharacterOwner->GetLocalRole() == ROLE_Authority)
		{
			SwitchWeapon(NewWeapon, Weapon);
		}
		else
		{
			ServerSwitchWeapon(NewWeapon);
		}
	}
}

bool UWarfareLoadoutComponent::ServerSwitchWeapon_Validate(AWarfareWeapon* NewWeapon)
{
	return true;
}

void UWarfareLoadoutComponent::OnRep_SwitchWeapon(AWarfareWeapon* LastWeapon)
{
	SwitchWeapon(Weapon, LastWeapon);
}

AWarfareWeapon* UWarfareLoadoutComponent::GetWeapon() const
{
	return Weapon;
}

void UWarfareLoadoutComponent::EquipWeapon()
{
	if (CharacterOwner->GetLocalRole() == ROLE_Authority)
	{
		if (Loadout.Num() > 0)
		{
			AWarfareWeapon* Weap = Cast<AWarfareWeapon>(Loadout[0]);
			SwitchWeapon(Weap);
		}
	}
}
