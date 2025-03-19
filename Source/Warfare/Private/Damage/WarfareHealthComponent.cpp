// Fill out your copyright notice in the Description page of Project Settings.

#include "Damage/WarfareHealthComponent.h"
#include "Net/UnrealNetwork.h"

UWarfareHealthComponent::UWarfareHealthComponent()
{
	Health = 0.0f;
	MaxHealth = 100.0f;
	LastTakeHitTimeTimeout = 0.0f;
	bIsDestroyed = false;

	SetIsReplicatedByDefault(true);
}

void UWarfareHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UWarfareHealthComponent, TakeHitInfo, COND_Custom);
	DOREPLIFETIME_CONDITION(UWarfareHealthComponent, Health, COND_None);
}

void UWarfareHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		if (Health == 0)
		{
			Health = MaxHealth;
		}

		if (GetOwner())
		{
			GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UWarfareHealthComponent::TakeDamage);
		}
	}
}

void UWarfareHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return;
	}

	if (Damage > 0.0f)
	{
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = DamageType->GetClass();

		Health -= Damage;
		if (Health <= 0.0f)
		{
			Destroy();
		}
		else
		{
			TakeHit(Damage, DamageEvent, EventInstigator->GetPawn() ? EventInstigator->GetPawn() : nullptr, DamageCauser, false);
		}
	}
}

void UWarfareHealthComponent::Destroy()
{
	if (bIsDestroyed || GetOwner()->IsPendingKillPending() || GetOwnerRole() != ROLE_Authority)
	{
		return; 
	}
	else
	{
		Health = FMath::Min(0.0f, Health);
	}
}

void UWarfareHealthComponent::TakeHit(float Damage, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bDestroyed)
{
	const float TimeoutTime = GetWorld()->GetTimeSeconds() + 0.5f;

	FDamageEvent const& LastDamageEvent = TakeHitInfo.GetDamageEvent();
	if ((PawnInstigator == TakeHitInfo.PawnInstigator.Get()) && (LastDamageEvent.DamageTypeClass == TakeHitInfo.DamageType) && (LastTakeHitTimeTimeout == TimeoutTime))
	{
		if (bIsDestroyed && TakeHitInfo.bPendingDestroy)
		{
			return;
		}

		Damage += TakeHitInfo.Damage;
	}

	TakeHitInfo.Damage = Damage;
	TakeHitInfo.PawnInstigator = PawnInstigator;
	TakeHitInfo.DamageCauser = DamageCauser;
	TakeHitInfo.SetDamageEvent(DamageEvent);
	TakeHitInfo.bPendingDestroy = bDestroyed;
	TakeHitInfo.AddHit();

	LastTakeHitTimeTimeout = TimeoutTime;
}

void UWarfareHealthComponent::OnRep_TakeHit()
{
	if (TakeHitInfo.bPendingDestroy)
	{

	}
	else
	{

	}
}

FTakeHitInfo::FTakeHitInfo()
{
	Damage = 0.0f;
	DamageType = nullptr;
	PawnInstigator = nullptr;
	DamageCauser = nullptr;
	DamageEventID = 0;
	bPendingDestroy = false;
	HitCounter = 0;
}

FDamageEvent& FTakeHitInfo::GetDamageEvent()
{
	switch (DamageEventID)
	{
	case FPointDamageEvent::ClassID:
		if (PointDamageEvent.DamageTypeClass == nullptr)
		{
			PointDamageEvent.DamageTypeClass = DamageType ? DamageType.Get() : UDamageType::StaticClass();
		}
		return PointDamageEvent;

	case FRadialDamageEvent::ClassID:
		if (RadialDamageEvent.DamageTypeClass == nullptr)
		{
			RadialDamageEvent.DamageTypeClass = DamageType ? DamageType.Get() : UDamageType::StaticClass();
		}
		return RadialDamageEvent;

	default:
		if (GeneralDamageEvent.DamageTypeClass == nullptr)
		{
			GeneralDamageEvent.DamageTypeClass = DamageType ? DamageType.Get() : UDamageType::StaticClass();
		}
		return GeneralDamageEvent;
	}
}

void FTakeHitInfo::SetDamageEvent(const FDamageEvent& DamageEvent)
{
	DamageEventID = DamageEvent.GetTypeID();
	switch (DamageEventID)
	{
	case FPointDamageEvent::ClassID:
		PointDamageEvent = *((FPointDamageEvent const*)(&DamageEvent));
		break;
	case FRadialDamageEvent::ClassID:
		RadialDamageEvent = *((FRadialDamageEvent const*)(&DamageEvent));
		break;
	default:
		GeneralDamageEvent = DamageEvent;
	}

	DamageType = DamageEvent.DamageTypeClass;
}

void FTakeHitInfo::AddHit()
{
	HitCounter++;
}
