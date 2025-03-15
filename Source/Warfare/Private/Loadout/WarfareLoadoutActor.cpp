// Fill out your copyright notice in the Description page of Project Settings.

#include "Loadout/WarfareLoadoutActor.h"
#include "Player/WarfareCharacter.h"

AWarfareLoadoutActor::AWarfareLoadoutActor()
{
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(GetRootComponent());
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh1P->SetHiddenInGame(true);
	Mesh1P->bReceivesDecals = false;
	Mesh1P->CastShadow = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh3P"));
	Mesh3P->SetupAttachment(Mesh1P);
	Mesh3P->SetHiddenInGame(true);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh3P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh1P->SetHiddenInGame(true);
	Mesh3P->bReceivesDecals = false;
	Mesh3P->CastShadow = true;
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	EquipStartedTime = 0.0f;
	EquipDuration = 0.0f;
	bIsHoldable = true;
	bIsEquipping = false;

	bReplicates = true;
	bOnlyRelevantToOwner = true;
	bNetUseOwnerRelevancy = true;
	PrimaryActorTick.bCanEverTick = true;
}

AWarfareCharacter* AWarfareLoadoutActor::GetCharacterOwner() const
{
	return CharacterOwner;
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

void AWarfareLoadoutActor::AttachToOwner()
{
	if (CharacterOwner)
	{
		Mesh1P->SetHiddenInGame(false);
		Mesh1P->AttachToComponent(CharacterOwner->GetArmsMesh(), FAttachmentTransformRules::KeepRelativeTransform, HandsAttachSocket);
	}
}

void AWarfareLoadoutActor::DetachFromOwner()
{
	Mesh1P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh1P->SetHiddenInGame(true);
}

void AWarfareLoadoutActor::OnEquip()
{
	AttachToOwner();
}

void AWarfareLoadoutActor::OnEquipped()
{
	DetachFromOwner();
}

void AWarfareLoadoutActor::OnUnEquip()
{

}

float AWarfareLoadoutActor::GetEquipStartedTime() const
{
	return EquipStartedTime;
}

float AWarfareLoadoutActor::GetEquipDuration() const
{
	return EquipDuration;
}

bool AWarfareLoadoutActor::IsEquipped() const
{
	return bIsEquipped;
}

bool AWarfareLoadoutActor::IsAttached() const
{
	return bIsEquipped || bIsEquipping;
}

void AWarfareLoadoutActor::PrimaryUse()
{
	
}

void AWarfareLoadoutActor::SecondaryUse()
{

}

void AWarfareLoadoutActor::SetState()
{
	
}

void AWarfareLoadoutActor::UpdateState()
{
	
}